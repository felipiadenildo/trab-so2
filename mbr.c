

#include <mbr.h>

/* A string consisting of the CRLF sequence.
   Used by the function-like macro printnl. */

char nl[] = {'\r', '\n', 0x0};


/* Prints the null-terminated string buffer.  */

void __attribute__((fastcall, naked))  print (const char* buffer)
{
__asm__ volatile
(                                                                          
 "        mov   $0x0e, %%ah           ;" /* Video BIOS service: teletype mode */
 "        mov   $0x0, %%si            ;" 
 "loop%=:                             ;"                                    
 "        mov   (%%bx, %%si), %%al    ;"
 "        cmp   $0x0, %%al            ;" /* Repeat until end of string (0x0). */
 "        je    end%=                 ;"                                    
 "        int   $0x10                 ;" /* Call video BIOS service.          */
 "        add   $0x1, %%si            ;"                                    
 "        jmp   loop%=                ;"                                    
 "end%=:                              ;"
 "        ret                         ;" /* Return from this function.         */

:                        
: "b" (buffer)      /* Var. buffer put in bx, referenced as str .*/
: "ax", "cx", "si"        /* Additional clobbered registers         .  */
 );
}

/* Clear the screen and set video colors. */

void __attribute__((naked, fastcall)) clear (void)
{

  __asm__ volatile
    (
     " mov $0x0600, %%ax                 ;" /* Video BIOS service: Scroll up. */
     " mov $0x0d, %%bh                   ;" /* Attribute (back/foreground.    */
     " mov $0x0, %%cx                    ;" /* Upper-left corner.             */
     " mov $0x184f, %%dx                 ;" /* Upper-right corner.            */
     " int $0x10                         ;" /* Call video BIOS service.       */

     " mov $0x01, %%ah                   ;" 
     " mov $0x07, %%cx                   ;" 
     " int $0x10                         ;" 

     " mov $0x00, %%bh                   ;" 
     " mov $0x00, %%dh                   ;"
     " mov $0x00, %%dl                   ;" 
     " mov $0x02, %%ah                   ;"
     " int $0x10                         ;"

     " ret                                " /* Return from function. */
     ::: "ax", "bx", "cx", "dx"		    /* Additional clobbered registers.*/
     );

}

/* Read string from terminal into buffer. 

   Note: this function does not check for buffer overrun.
         Buffer size is BUFFER_MAX_LENGTH.

	 Good opportunity for contributing.

   Ok, now it is not possible a buffer bigger then 5

*/

void __attribute__((fastcall, naked)) read (char *buffer)
{ 
    __asm__ volatile
    (     
     
     "   mov $0x0, %%si               ;" /* Iteration index for (%bx, %si).  */
     "   mov $0x0, %%cl               ;" /* Buffer size is BUFFER_MAX_LENGTH.*/
     "loop%=:                         ;"
     "   movw $0X0, %%ax              ;" /* Choose blocking read operation.  */
     "   int $0x16                    ;" /* Call BIOS keyboard read service. */
     "   movb %%al, %%es:(%%bx, %%si) ;" /* Fill in buffer pointed by %bx.   */
     "   inc %%si                     ;"
     "   inc %%cl                     ;"

     "   cmp $0xd, %%al               ;" /* Reiterate if not ascii 13 (CR)   */
    
     "   mov $0x0e, %%ah              ;" /* Echo character on the terminal.  */
     "   int $0x10                    ;"
     "   jne backspace                ;"
     "   jmp cont                     ;"
    
     "backspace:                      ;"
     "   cmp $0x08, %%al              ;"
     "   jne space                    ;"
     "   mov $0x0, %%al               ;"
     "   mov $0x0e, %%ah              ;"
     "   int $0x10                    ;"
     "   mov %%bh, %%al               ;"
     "   mov $0x0, %%bh               ;"
     "   mov $0x03, %%ah              ;"
     "   int $0x10                    ;"
     "   dec %%dl                     ;"
     "   mov $0x02, %%ah              ;"
     "   int $0x10                    ;"
     "   mov %%dl, %%cl               ;"
     "   mov $0x0, %%ch               ;"
     "   mov %%cx, %%si               ;"
     "   mov %%al, %%bh               ;"
     "   jmp loop%=                   ;"

     "space:                          ;"
     "   cmp $0x20, %%al              ;"
     "   jne lp                       ;"
     "   jmp cont                     ;"

     "lp:                             ;"
     "   cmp $0x4, %%cl               ;" /* Check buffer size                */ 
     "   je cont                      ;"
     "   jmp loop%=                   ;"

     "cont:                           ;"
     "   mov $0x0e, %%ah              ;" /* Echo a newline.                  */
     "   mov $0x0a, %%al              ;"
     "   int $0x10                    ;"

     "   movb $0x0, -1(%%bx, %%si)    ;" /* Add buffer a string delimiter.   */
     "   ret                           " /* Return from function             */
     
     :
     : "b" (buffer) 	          /* Ask gcc to store buffer in %bx          */
     : "ax", "cx", "si", "dx" 	  /* Aditional clobbered registers.          */
     );
}


// Try show hours 
void __attribute__((naked)) date (void)
{
  __asm__ volatile
    (     
     " mov $0x0, %%ah                 ;"
     " int $0x1a                      ;" 
     " mov %%dx, %%ax                 ;"
     " mov $0x0, %%dx                 ;"
     " mov $0x1007, %%cx              ;"
     " div %%cx                       ;"
     " mov $0x0e, %%ah                ;"
     " int $0x10                      ;"
     " ret                             "
     ::: "ax", "bx", "cx" 
     );

}

/* Compare two strings up to position BUFFER_MAX_LENGTH-1. */
int __attribute__((fastcall, naked)) compare (char *s1, char *s2)
{
  __asm__ volatile
    (
      "    mov %[len], %%cx   ;"
      "    mov $0x1, %%ax     ;"
      "    cld                ;"
      "    repe  cmpsb        ;"
      "    jecxz  equal       ;"             
      "    mov $0x0, %%ax     ;"
      "equal:                 ;"
      "    ret                ;"
      :
      : [len] "n" (BUFFER_MAX_LENGTH-1), /* [len] is a constant.   */
	"S" (s1),		/* Ask gcc to store s1 in %si      */
	"D" (s2)		/* Ask gcc to store s2 is %di      */
      : "ax", "cx", "dx"	/* Additional clobbered registers. */
     );

  return 0;                /* Bogus return to fulfill funtion's prototype.*/
}

