/**
 *	BitThunder SLAB Allocator for Kernel Memory.
 *
 *	@author	James Walmsley	<james@fullfat-fs.co.uk>
 *	@author Clifford Wolf	<clifford@clifford.at>
 *
 *	This allocator uses a generic SLAB based approach. It is based on
 *	a really neat (perfect) idea that Clifford recommended. (Thanks).
 *
 *	All operations complete in O(1), unless they hit the page-allocator,
 * 	in which case the allocation complexity is inherited from the page-allocator.
 *	
 **/

#include <bitthunder.h>
#include <collections/bt_list.h>
#include <mm/bt_mm.h>
#include <mm/bt_page.h>


#define BT_CACHE_FLAGS_OBJECT		0x00000001	///< Unset if standard allocation cache.
#define BT_CACHE_FLAGS_UNALIGNED	0x00000002

#define BT_CACHE_GENERIC_MIN		16
#define BT_CACHE_GENERIC_MAX		8192

struct block;

struct block_free {
	struct	block_free *next;
};

typedef struct _BT_CACHE {
	struct bt_list_head		blocks;				///< List of blocks asociated with this cache.
	BT_u32					ulObjectSize;
	struct block_free  	   *free;
	BT_u32					allocated;
} BT_CACHE;


struct block {
	struct bt_list_head 	list;			///< This is an item in a list of blocks.
	BT_u32					ulSize;
};

static BT_CACHE g_oDefault[10];		///< Array of primary caches, starting at 16bytes, upto 8192 bytes


static void init_attach_block(BT_CACHE *pCache, struct block *pBlock, BT_u32 ulSize) {
	BT_u32 i;
	BT_u32 total_objects = (ulSize - sizeof(struct block)) / pCache->ulObjectSize;

	pBlock->ulSize = ulSize;

	struct block_free *free = (struct block_free *) (pBlock+1);
	for(i = 0; i < total_objects; i++) {
		free->next = (struct block_free *) (((BT_u8 *) free) + pCache->ulObjectSize);
		free = (struct block_free *) (((BT_u8 *) free) + pCache->ulObjectSize);
	}

	free = (struct block_free *) (((BT_u8 *) free) - pCache->ulObjectSize);	// Reverse to correct the end of block.
	free->next = pCache->free;
	pCache->free = (struct block_free *) (pBlock+1);

	bt_list_add(&pBlock->list, &pCache->blocks);
}

static BT_ERROR extend_cache(BT_CACHE *pCache) {

	BT_u32 ulSize = BT_PAGE_ALIGN((pCache->ulObjectSize + sizeof(struct block)));

	void *p = (void *) bt_page_alloc(ulSize);
	if(!p) {
		return BT_ERR_NO_MEMORY;
	}

	struct block *pBlock = (struct block *) bt_phys_to_virt(p);
	init_attach_block(pCache, pBlock, ulSize);

	return BT_ERR_NONE;
}


static BT_ERROR init_cache(BT_CACHE *pCache, BT_u32 ulObjectSize) {
	BT_LIST_INIT_HEAD(&pCache->blocks);
	pCache->ulObjectSize = ulObjectSize;
	pCache->free = NULL;
	pCache->allocated = 0;

	extend_cache(pCache);

	return BT_ERR_NONE;
}

/*BT_CACHE *BT_kCreateCache(BT_u32 ulObjectSize, BT_u32 ulFlags) {

}

BT_ERROR BT_kDestroyCache(BT_CACHE *pCache) {

}*/

static BT_CACHE *BT_GetSuitableCache(BT_u32 ulSize) {

	if(ulSize <= BT_CACHE_GENERIC_MIN) {
		return &g_oDefault[0];
	}

	if(ulSize > BT_CACHE_GENERIC_MAX) {
		return NULL;
	}

	BT_u32 highest_bit = BT_CLZ(ulSize);
	if(ulSize & ((0x80000000 >> highest_bit)-1)) {	// Use size to get the index.
		highest_bit -= 1;
	}


	BT_u32 idx = BT_CLZ(BT_CACHE_GENERIC_MIN) - highest_bit;

	return &g_oDefault[idx];
}

static struct block_free *pop_free(BT_CACHE *pCache) {
	if(pCache->free) {
		struct block_free *p = pCache->free;
		pCache->free = pCache->free->next;
		pCache->allocated += 1;
		return p;
	}

	return NULL;
}

static void push_free(BT_CACHE *pCache, struct block_free *p) {
	p->next = pCache->free;	
	pCache->free = p;
	pCache->allocated -= 1;
}

static void *BT_CacheAlloc(BT_CACHE *pCache) {

	struct block_free *p = pop_free(pCache);
	if(!p) {
		extend_cache(pCache);
		p = pop_free(pCache);
		if(!p) {
			return NULL;
		}
	}

	return (void *) p;
}

static BT_ERROR BT_CacheFree(BT_CACHE *pCache, void *p) {
	struct block_free *free = (struct block_free *) p;
	push_free(pCache, free);
	return BT_ERR_NONE;
}

void *BT_kMalloc(BT_u32 ulSize) {

	void *p;

	BT_CACHE *pCache = BT_GetSuitableCache(ulSize+sizeof(BT_CACHE *));
	if(pCache) {
		p = BT_CacheAlloc(pCache);
	} else {
		p = (void *) bt_phys_to_virt(bt_page_alloc(ulSize+sizeof(BT_CACHE *)));
		if(!p) {
			return NULL;
		}
	}

	BT_CACHE **tag = (BT_CACHE **) p;
    *tag = pCache;

	/*
	 *	Before the allocated memory we place a pointer to the pCache.
	 *	This will be 0 in the case of a page allocation!
	 */

	return ((void *) (tag + 1));
}

void BT_kFree(void *p) {
	BT_CACHE **tag = (BT_CACHE **) p;
	tag -= 1;

	BT_CACHE *pCache = *tag;
	if(pCache) {
		BT_CacheFree(pCache, tag);
	} else {
		bt_page_free((BT_PHYS_ADDR) bt_virt_to_phys(tag));
	}
}

void bt_initialise_slab() {

	BT_u32 i = BT_CACHE_GENERIC_MIN;
	while(i <= BT_CACHE_GENERIC_MAX) {
		BT_CACHE *pCache = BT_GetSuitableCache(i);
		if(!pCache) {
			break;
		}
		init_cache(pCache, i);
		i = i << 1;
	}
}
