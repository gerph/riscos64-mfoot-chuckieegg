# Makefile for building bin for aarch64

USE_FUNC_SIGNATURE ?= 1

DIS = ~/projects/RO/pyromaniac/utils/riscos-dumpi --arm64
CROSS_ROOT = ${shell echo $$CROSS_ROOT}

DEFAULT_GOAL = chuckie64,ff8

CFLAGS = -O1 -nostdlib -ffreestanding -march=armv8-a+nofp -DMODE_256

ifeq (${USE_FUNC_SIGNATURE},1)
CFLAGS += -fpatchable-function-entry=20,20
endif

all: ${DEFAULT_GOAL}

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:20240529-0dade71 > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.bin *,ff8 *.map

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
.PHONY: ${MAKECMDGOALS}
${MAKECMDGOALS}: dockcross-linux-arm64
	cd .. ; aarch64/dockcross-linux-arm64 bash -c "cd aarch64 && make ${MAKECMDGOALS}"
else
.PHONY: ${DEFAULT_GOAL}
${DEFAULT_GOAL}: dockcross-linux-arm64
	cd .. ; aarch64/dockcross-linux-arm64 bash -c "cd aarch64 && make ${DEFAULT_GOAL}"
endif

else

OBJS       = main.o \
			 execute.o \
			 library.o \
			 r6502main.o \
			 i_sprite.o \
			 i_screeninfo.o \
			 exit.o \
			 malloc.o \
			 clib.o \
			 clib-kernel.o

%.o: %.c
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

chuckie64.bin: start.o swis.o link.lnk ${OBJS}
	aarch64-unknown-linux-gnu-ld start.o swis.o ${OBJS} -T link.lnk -o $@

chuckie64.map: start.o swis.o link.lnk ${OBJS}
	aarch64-unknown-linux-gnu-ld start.o swis.o ${OBJS} -T link.lnk -Map $@ -o /dev/null

ifeq (${USE_FUNC_SIGNATURE},1)
chuckie64,ff8: chuckie64.bin chuckie64.map
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text chuckie64.bin $@
	python riscos_symbols.py chuckie64.map chuckie64,ff8
else
chuckie64,ff8: chuckie64.bin
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text chuckie64.bin $@
endif

start.o: start.s
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

endif
