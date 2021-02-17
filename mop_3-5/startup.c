/*
 * 	startup.c
 *
 */
 
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

__attribute__((naked))
void graphic_initialize(void)
{
    __asm volatile(" .HWORD 0xdff0\n");
    __asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void)
{
    __asm volatile(" .HWORD 0xdff1\n");
    __asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_set(int x, int y)
{
    __asm volatile(" .HWORD 0xdff2\n");
    __asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y)
{
    __asm volatile(" .HWORD 0xdff3\n");
    __asm volatile(" BX LR\n");
}