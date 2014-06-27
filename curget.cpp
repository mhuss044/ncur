// do some curses stuff 

#include <ncurses.h>
#include <math.h>
#include <stdlib.h>

typedef struct _plyr
{
	float px, py;
	_plyr()
	{
		px = 0.0;
		py = 0.0;
	}
}plyr;

int main(void)
{
	int c = 'g',
	// Draw ring vars 
	int winX, winY, cx, cy, ang = 0, r = 0, inc = 1;
	char inp;
	bool gu = true;
	// Game
	float obstac[9] = {0,0,0,0,0,0,0,0,0};	// Topleft, scale, pos from cntr
	// Player
	plyr npl;

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
	cbreak();	// no wait for 'EOF' or carriage return
	timeout(1);	// nonblocking

	clear();	// clear scr
	while(inp !='q')
	{
		inp = getch();
		gu = !gu;
		cx = 0;
		cy = 0;
		r = 0;

		// Go fast effect?
		inp == 'w' ? inc = 1 : inc = rand()%6+3;
		// Move to next ring pos, draw it
		while(winX*2 > (winX+cx) && winY*2 > (winY+cy))
		{
			gu = !gu;
			ang = 0;

			// Draw Ring
			while(ang <= 360)
			{
				// Get x,y of next ring coord
				cx = r*cos(float(ang*(0.01745329251)));	
				cy = r*sin(float(ang*(0.01745329251)));

					if(gu)
					{
						move(winY+cy,winX+cx);	// moves the cursor to rowth row and colth column 
				//		addch('O');
						addch(ACS_BULLET);
					}
					else
					{
						move(winY+cy,winX+cx);	// moves the cursor to rowth row and colth column 
//						addch('X');
//						addch(ACS_BLOCK);
						addch(ACS_DIAMOND); 
					}
					ang += 1;
			}
			r += inc;	// Get next radius
		}
		// Done drawing bkg

		// Move player
		switch(inp)
		{
			case 'a':
				npl.px -= 2;
				break;
			case 'd':
				npl.px += 2;
				break;
			case 's':
				break;
		}

		// Draw player
		for(int y = 0; y < 5; y++)
		{
			move(winY+npl.py-y,winX+npl.px);
			addch('*');
			for(int x = 1; x < y; y++)
			{
				move(winY+npl.py-y,winX+npl.px);
				addch('*');
			}
		}
		refresh();		// out
	}

	endwin();	/* End curses mode */
	return 0;
}
