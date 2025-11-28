# Makefile for Chuckie
#

COMPONENT  = Chuckie
TYPE       = aif
INCLUDES   = 
LIBS       = ${CLIB}
CDEFINES   = -DMODE_256
OBJS       = o.main \
			 o.execute \
			 o.library \
			 o.r6502main \
			 o.i_sprite \
			 o.i_screeninfo \
			 o.exit \
			 o.malloc

ifeq (${BUILD64},1)
else
OBJS += o.r6502code
endif

include LibraryCommand

#---------------------------------------------------------------------------
# Dynamic dependencies:
