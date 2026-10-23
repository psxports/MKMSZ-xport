#include "xport.h"
#include "psx.h"

extern void mkm_main_80020474(void);

void mkm_bootstrap(uint32 caller_ra)
{
    uint32 clear_address = 0x800D7B40;
    uint32 stack_top;
    uint32 reserved_stack;
    uint32 heap_size;

    FUNCTION_MARKER(0x80090E70, "SLUS_004.76");

    do
    {
        w_u32(clear_address, 0);
        clear_address += 4;
    } while (clear_address < 0x80130FF8);

    stack_top = r_u32(0x80090F20);
    reserved_stack = r_u32(0x800BF358);
    heap_size = stack_top - reserved_stack - 0x130FF8;
    w_u32(0x800D7C48, caller_ra);
    InitHeap(0x80130FFC, heap_size);
    (void)r_u32(0x800D7C48);
    mkm_main_80020474();
    trap(1);
}
