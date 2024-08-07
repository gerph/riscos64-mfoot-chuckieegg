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
			 o.r6502code \
			 o.i_sprite \
			 o.i_screeninfo \
			 o.exit \
			 o.malloc

include LibraryCommand

#---------------------------------------------------------------------------
# Dynamic dependencies:
