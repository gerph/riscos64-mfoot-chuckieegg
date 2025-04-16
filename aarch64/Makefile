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

RISCOS64_TOOLS_VERSION = 0.12

TARGET ?= chuckie64

USE_FUNC_SIGNATURE ?= 1

CROSS_ROOT = ${shell echo $$CROSS_ROOT}

ALL_TARGETS = chuckie64


# Remove the flags that might make code think it's compiling for linux system.
CFLAGS = -U__linux -U__linux__ -U__unix__ -U__unix -Ulinux -Uunix -U__gnu_linux__

# Add the definitions to indicate that we're compiling for RISC OS
CFLAGS += -D__riscos -D__riscos64

# Allow us to build without assuming the standard library is present
CFLAGS += -nostdlib -ffreestanding -march=armv8-a
#CFLAGS += -nostdlib -ffreestanding -march=armv8-a+nofp

# Add the exports directory to those things we'll build with
CFLAGS += -I${CLIBDIR} -I${CLIBDIR}/C -I${CLIBDIR}/Lib/ -I${CLIBDIR}/Lib/CLib/

# Options to allow function signatures to appear RISC OS-like
ifeq (${USE_FUNC_SIGNATURE},1)
CFLAGS += -fpatchable-function-entry=20,20
endif

# Optimisation options
CFLAGS += -O1

# Options for this build
CFLAGS += -I/ro64 -DMODE_256 -DSET_CHANNELS

# Assembler flags
AFLAGS = -march=armv8-a

# Flags for the linker
LDFLAGS = -T link.lnk -e _aif64_entry

targetted:
	make ${TARGET},ff8 TARGET=${TARGET}

all:
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:latest > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.a *.bin *,ff8 *.map


CRT_OBJS = 	${CLIBDIR}/libcrt.a

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container

CLIBDIR = ${PWD}/riscos64

riscos64_clib: ${CLIBDIR}/kernel.h
${CLIBDIR}/kernel.h: riscos64-clib.zip
	mkdir -p ${CLIBDIR} && cd ${CLIBDIR} && unzip -o ${PWD}/riscos64-clib.zip

riscos64-clib.zip:
	wget -O $@ https://github.com/gerph/riscos64-simple-binaries/releases/download/v${RISCOS64_TOOLS_VERSION}/RISCOS64-CLib-${RISCOS64_TOOLS_VERSION}.zip

ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
.PHONY: ${MAKECMDGOALS} riscos64_clib
${MAKECMDGOALS}: dockcross-linux-arm64 ${CRT_OBJS}
	cd .. ; aarch64/dockcross-linux-arm64 --args "-v ${CLIBDIR}:/ro64/clib" --  bash -c "cd aarch64 && make ${MAKECMDGOALS} TARGET=${TARGET}"
else
.PHONY: ${DEFAULT_GOAL} riscos64_clib
${DEFAULT_GOAL}: dockcross-linux-arm64
	cd .. ; aarch64/dockcross-linux-arm64 -- bash -c "cd aarch64 && make TARGET=${TARGET}"
endif

${CLIBDIR}/libcrt.a: riscos64_clib

else
# We are within the docker container

CLIBDIR = /ro64/clib


CC = aarch64-unknown-linux-gnu-gcc
AS = aarch64-unknown-linux-gnu-as
LD = aarch64-unknown-linux-gnu-ld
OBJCOPY = aarch64-unknown-linux-gnu-objcopy

OBJS       = main.o \
			 execute.o \
			 library.o \
			 r6502main.o \
			 malloc.o \
			 i_sprite.o \
			 i_screeninfo.o \
			 exit.o \

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $?

%.o: %.s
	${AS} ${AFLAGS} -o $@ $?

${TARGET}.bin: link.lnk ${OBJS} ${CRT_OBJS}
	${LD} ${OBJS} ${CRT_OBJS} ${LDFLAGS} -o $@

${TARGET}.map: link.lnk ${OBJS} ${CRT_OBJS}
	${LD} ${OBJS} ${CRT_OBJS} ${LDFLAGS} -Map $@ -o /dev/null

ifeq (${USE_FUNC_SIGNATURE},1)
${TARGET},ff8: ${TARGET}.bin ${TARGET}.map
	${OBJCOPY} -O binary -j .text ${TARGET}.bin $@
	python riscos_symbols.py ${TARGET}.map ${TARGET},ff8
else
${TARGET},ff8: ${TARGET}.bin
	${OBJCOPY} -O binary -j .text ${TARGET}.bin $@
endif

endif
