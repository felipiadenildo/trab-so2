
OUTPUT_FORMAT(binary)		/* Output flat binary (no structure)          */
SECTIONS
{
        . = 0x7C00;		/* Line counter is now 0x7c00.                */
	
        .text :			/* Ouput file has only one (implied) section. */
	{
	  *(.text)              /* Copy input section .text to the oputput.   */
	  *(.data)		/* Copy input section .data to the output.    */
	  *(.bss)		/* Copy input section .bss to the output.     */
	  *(.rodata)		/* Copy input section .rodata to the output.  */
}	
        . = 0x7c00 + 510;	/* Advance 510 bytes.                         */
        .signature : 		/* Add a signadure section with this content. */
	{
	    BYTE(0x55)
            BYTE(0xAA)
        }
	__END_STACK__ = 10000;	 /* End of the 64K block.        */
}
STARTUP(rt0.o)			 /* Prepend the start file.      */

