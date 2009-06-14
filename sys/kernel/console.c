/*
 * These functions handle text output to the standard 80x25 console.
 */

#include <string.h>


char* const videomem = (char*)0xB8000;
const char CON_COLS = 80;
const char CON_ROWS = 25;

/*
 * Save where the imaginary cursor is
 */
short *cursorpos = (short*)0xB8000;



/*
 * Clear the console
 */
void con_clear()
{
	memset(videomem, 0, CON_ROWS*CON_COLS*2);
}

/*
 * Scroll the console
 */
void con_scroll(int offset)
{
	memcpy(videomem, videomem + (offset*CON_COLS*2), (CON_ROWS - offset) * CON_COLS * 2);

	memset(videomem + (CON_ROWS-offset)*CON_COLS*2, 0, offset*CON_COLS*2);
}

/*
 * Print a single character
 */
void con_printchar(char c, char row, char col)
{
	if(row >= CON_ROWS || col >= CON_COLS)
		return;

	videomem[row*CON_ROWS + col] = c;
}

/*
 * Print a string at the current cursor position
 */
void con_puts(const char *str)
{
	while(*str)
	{
		if(cursorpos > (short*) videomem + CON_ROWS*CON_COLS*2)
		{
			// Reset cursorpos and scroll
			cursorpos -= CON_COLS*2;
			con_scroll(1);

			return;
		}

		*cursorpos = (((*str)) | 0x0F00);
		str++;
		cursorpos++;
	}
}


