#ifndef _BT_VERSION_H_
#define _BT_VERSION_H_

#define BT_V_STRINGIFY(x)	#x
#define BT_V(x)				BT_V_STRINGIFY(x)

#define BT_VERSION_MAJOR	0
#define BT_VERSION_MINOR	8
#define BT_VERSION_REVISION	0
#ifndef BT_VERSION_SUFFIX
#define BT_VERSION_SUFFIX	"pre"
#endif

#define BT_VERSION_NAME		"2-acetoxybenzoic acid"
#define BT_VERSION_STRING	"BitThunder v"BT_V(BT_VERSION_MAJOR)"."BT_V(BT_VERSION_MINOR)"."BT_V(BT_VERSION_REVISION)"-"BT_VERSION_SUFFIX

#endif
