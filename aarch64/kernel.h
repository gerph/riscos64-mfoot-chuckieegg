#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

typedef struct _kernel_oserror_s {
    uint32_t errnum;
    char errmess[252];
} _kernel_oserror;

typedef struct _kernel_swi_regs {
    int32_t r[10];
} _kernel_swi_regs;

_kernel_oserror *_kernel_swi(int swinum, _kernel_swi_regs *in, _kernel_swi_regs *out);

_kernel_oserror *_kernel_oscli(const char *cli);
#define _kernel_oscli(cli) /* nothing */

#endif

