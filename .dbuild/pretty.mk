PRETTY 		= $(BASE).dbuild/pretty/pretty.py
PRETTIFY	= $(BASE).dbuild/pretty/prettify.py
PCP			= $(BASE).dbuild/pretty/prettycp.py --dbuild "CP"
PMD			= $(BASE).dbuild/pretty/prettymd.py
PRM			= $(PRETTIFY) --dbuild "RM"
PCHMOD		= $(BASE).dbuild/pretty/prettychmod.py
PRETTYSAMBA	= $(BASE).dbuild/pretty/prettysamba.py
PRETTYLINUX = $(BASE).dbuild/pretty/prettylinux.py
PRETTY_SUBKBUILD = $(PRETTYLINUX)
PRETTY_SUBGENERIC = $(BASE).dbuild/pretty/prettygeneric.py
PTODO		= $(BASE).dbuild/pretty/todo.py

PRETTYPOST	= $(PRETTY) "POST" $(@:%.post=%)
PRETTYPREP	= $(PRETTY) "PREP" $(@:%.pre=%)

ifeq ($(DBUILD_VERBOSE_CMD), 1)
#PRETTY=@ #
endif

#
#	PRM (Pretty Remove) flags
#
PRM_PIPE=
PRM_FLAGS=-rf

ifeq ($(DBUILD_VERBOSE_CMD), 0)
PRM_PIPE=| $(PRM) $(MODULE_NAME)
PRM_FLAGS=-rvf
endif

#
#	PCP Flags
#
PCP_PIPE=
PCP_FLAGS=-r

ifeq ($(DBUILD_VERBOSE_CMD), 0)
PCP_PIPE=| $(PCP) $(MODULE_NAME)
PCP_FLAGS=-vr
endif

#
# 	PMD Flags
#
PMD_FLAGS=-p
PMD_PIPE=

ifeq ($(DBUILD_VERBOSE_CMD), 0)
PMD_FLAGS=-pv
PMD_PIPE=| $(PMD) $(MODULE_NAME)
endif
