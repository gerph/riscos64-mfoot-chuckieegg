#include <stdint.h>
#include "kernel.h"

#define OS_Module (0x1e)
#define OS_WriteC (0x0)
#define OS_WriteI (0x100)
#define OS_Byte (0x6)
#define OS_ScreenMode (0x65)
#define OS_Plot (0x45)
#define OS_WriteN (0x46)
#define OS_ReadLine (0xE)
#define OS_Word (7)
#define Sound_Control (0x40189)
#define OS_SpriteOp (0x2E)
#define ColourTrans_GenerateTable (0x40763)
#define ColourTrans_SetGCOL (0x40743)
#define OS_ReadVduVariables (0x31)
#define OS_ReadModeVariable (0x35)
#define OS_ReadMonotonicTime (0x42)

#define bbcvdu(c) os_writec(c)

void os_writec(char c);
char os_readc(void);
void os_screenmode(int reason, uint32_t modespec);
void colourtrans_setgcol(uint32_t palentry, uint32_t flags, uint32_t gcol);
void draw_fill(int32_t *path, uint32_t style, int32_t *matrix, int32_t flatness);
void os_setcolour(uint32_t flags, uint32_t gcol);
int os_inkey(int32_t value);
void os_write0(const char *str);
void os_newline(void);

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
int os_byte_out1(int r0, int r1, int r2);

/* Using OS_WriteI makes no select really in AArch64 */
#define os_cls() os_writec(12)

#define _FLAGS     0x10 /*use with _RETURN() or _OUT()*/
#define _IN(i)     (1U << (i))
#define _INR(i,j)  (~0 << (i) ^ ~0 << (j) + 1)
#define _OUT(i)    ((i) != _FLAGS? 1U << 31 - (i): 1U << 21)
#define _OUTR(i,j) (~0U >> (i) ^ ~0U >> (j) + 1)

_kernel_oserror *_swix (int swi_no, unsigned int, ...);
