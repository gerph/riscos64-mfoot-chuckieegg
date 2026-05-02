# Makefile for building bin for aarch64
#
# Code compiles with:
#
#	__riscos
#	__riscos64
#   __aarch64__
#
# Norcroft defines not set:
#	__acorn
#	__arm

TARGET ?= chuckie64

# Version of the C library to use to build
CLIB_VERSION = 0.25
CLIB_URL = https://github.com/gerph/riscos64-simple-binaries/releases/download/v${CLIB_VERSION}/RISCOS64-CLib-${CLIB_VERSION}.zip

ALL_TARGETS = chuckie64


targetted:
	make ${TARGET},ff8 TARGET=${TARGET}

all:
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

clean:
	-rm -rf *.o *.a *.bin *,ff8 *.map tools clib

.PHONY: tools

tools: clib/libcrt.a
	mkdir -p tools
	clib/bin/robuild64 install tools

TOOLS ?= tools
CLIBDIR = ${TOOLS}/riscos64_resources

clib/clib-${CLIB_VERSION}.zip:
	mkdir -p clib
	wget -O clib/clib-${CLIB_VERSION}.zip "${CLIB_URL}"

clib/libcrt.a: clib/clib-${CLIB_VERSION}.zip
	cd clib && unzip -o clib-${CLIB_VERSION}.zip && touch libcrt.a


# C flags for this project
CFLAGS += -I. -DMODE_256 -DSET_CHANNELS

# Assembler flags
AFLAGS = -march=armv8-a

CC = RISCOS64_RELDIRS=1 ${TOOLS}/riscos64-cc ${CFLAGS}
AS = RISCOS64_RELDIRS=1 ${TOOLS}/riscos64-as ${AFLAGS}
LD = RISCOS64_RELDIRS=1 ${TOOLS}/riscos64-link
AR = RISCOS64_RELDIRS=1 ${TOOLS}/riscos64-libfile
CXX = ${CC}



OBJS       = main.o \
			 execute.o \
			 library.o \
			 r6502main.o \
			 malloc.o \
			 i_sprite.o \
			 i_screeninfo.o \
			 exit.o \

%.o: %.c
	${CC} -c -o $@ $?

%.o: %.s
	${AS} -o $@ $?

${TARGET},ff8: ${OBJS}
	${LD} -aif ${OBJS} -lcrt -o $@
