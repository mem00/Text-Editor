#include <cstdlib>
#include <ncurses.h>
#include <iostream>
using namespace std;
// Hassan Kedir Lab07 CSCI 1730 Spring 17
int main(const int argc, const char * argv []) {

	if (argc<2) // number of arguments must equal 2, if not the program exits.
		{ cout << "No file specified." << endl; return EXIT_SUCCESS;}

	// opening file for read only
	FILE *file = fopen(argv[1], "r");

	// if opening file failed, displays error message.
	if (file==0){ perror(argv[0]); }

	int y, x;
	initscr();	// initializes stdscr
	cbreak();	// return input one char at a time instead of a waiting for a termination character

	getmaxyx(stdscr, y, x);	// get max line and width of stdscr

	WINDOW *pad = newpad(y, x);


	// printing file characters to pad
	int txtc;
    while((txtc = fgetc(file)) != EOF)
    {
    	wprintw(pad, "%c", txtc);
    }
    fclose(file);


	move(0,0);
	scrollok(pad, TRUE);
	keypad(pad, TRUE);	// enable function keys (e.g. arrows)
	prefresh(pad, 0, 0, 0, 0, y, x);

    // scrolling pad
	int line;
    while (true){
    	int ch = wgetch(pad);
    	if (ch==KEY_DOWN){
    		line++;
			prefresh(pad, line, 0, 0, 0, y, x);
    	}
    	else if (ch==KEY_UP){
			if (line!=0){ line--; }
			prefresh(pad, line, 0, 0, 0, y, x);
		}
    	else{
    		break;
    	}
    }	// end loop for scrolling with arrow keys




    endwin();





  return EXIT_SUCCESS;
} // main
