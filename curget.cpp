// do some curses stuff 
#include <ncurses.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
	int c, winX, winY, cx, cy, ang = 0, r = 0, inc = 1;
	bool gu = true;

	initscr();		/* Start curses mode */
	raw();			/* Line buffering disabled */
	keypad(stdscr, TRUE);	/* We get F1, F2 etc.. */
	noecho();		/* Don't echo() while we do getch */

	getmaxyx(stdscr,winY,winX);// Get window info
	winX = winX/2;
	winY = winY/2;

//	printw("Type any character to see it in bold\n");
//	c = getch();		// If raw() hadn't been called
		       		// we have to press enter before it
				// gets to the program 
	if(c == KEY_F(2))			// Without keypad enabled this will 
		printw("F2 Key pressed");	// not get to us either 
						// Without noecho() some ugly escape
						// charachters might have been printed
						// on screen 
	else
	{ 
//		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", c);
		attroff(A_BOLD);
	}

/*	move(0,0);	// moves the cursor to rowth row and colth column 
	addch('O');
				move(20,20);	// moves the cursor to rowth row and colth column 
			addch('T');
				move(40,40);	// moves the cursor to rowth row and colth column 
			addch('Y');
*/	
	refresh();	/* Print it on to the real screen */


		
	//attron(A_BOLD);
	while(1)
	{
		gu = !gu;
		cx = 0;
		cy = 0;
		r = 0;

		while(winX*2 > (winX+cx) && winY*2 > (winY+cy))
		{
			gu = !gu;
			ang = 0;

			while(ang <= 360)
			{
				cx = r*cos(float(ang*(0.01745329251)));	
				cy = r*sin(float(ang*(0.01745329251)));

//				if(winX*2 > (winX+cx) && winY*2 > (winY+cy))
//				{
					if(gu)
					{
						move(winY+cy,winX+cx);	// moves the cursor to rowth row and colth column 
						addch('O');
					}
					else
					{
						move(winY+cy,winX+cx);	// moves the cursor to rowth row and colth column 
						addch('X');
					}
					ang += 1;
					refresh();		// out
//				}
					
			}
			r += rand()%5+1;
		}
		inc = rand()%10+1;
	}


	getch();	/* Wait for user input */
	endwin();	/* End curses mode */
			
	return 0;
}
