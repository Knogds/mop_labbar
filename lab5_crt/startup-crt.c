/*
 * 	startup-crt.c
 *  includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
 *  template functions for stdio: 
 */
#include	<errno.h>
#include 	<sys/stat.h>
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<unistd.h>
#include    <libMD407.h>

__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=__stack_top\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL _crt_init\n");			/* init C-runtime library */
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(" BL _crt_deinit\n");			/* deinit C-runtime library */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

int main(void)
{
    /* Eriks test code
     * https://chalmers.instructure.com/courses/12474/discussion_topics/59092 */

     printf("Testing if stdout works on console. Check.\n");
     printf("Testing if stdin works on console. Type something:\n");

     char * input_text = (char *) malloc(64);
     
     int i = 0; 
     while(1)
     {
        if(_read(STDIN, &input_text[i], 1)) {
            _write(STDOUT, &input_text[i], 1);
            if(input_text[i] == '\n') {
                input_text[i+1] = '\0';
                break;
            }
            i++;
        }
     }
     
     printf("What you typed should be on the ASCII display.\n");
     _write( ASCIIDISPLAY, input_text, strlen(input_text));
     free(input_text); 
     printf("Now press keys on the keypad and they should be repeated here.\n");
  
     char c;
     while( 1 )
     {
        if( _read( KEYPAD, &c, 1))
        {
            c += '0';
            _write( STDOUT, &c, 1);
        }
     }     
    
    return 0;
}

