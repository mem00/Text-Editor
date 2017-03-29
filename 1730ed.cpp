#include <cstdlib>
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <iterator>

using namespace std;
// Hassan Kedir P2 CSCI 1730 Spring 17


//void drawMenu(unsigned int);
//void openMenu();

WINDOW * setSS(WINDOW *);
WINDOW * edScr;
vector<string> * getfData();
void wfData();

vector<string> * fData;

FILE * fptr;
bool fSaved, mOpen;

char * fName;


int main(const int argc, const char * argv []) {
	// Handles cases when argument count is invalid.
	if (argc>2){ cout << "ERROR: Invalid number of arguments. Only one file name should given after ./1730ed" << endl; return EXIT_FAILURE;}

	// Attempts to open file if file only one name is given. Creates a new file if file doesn't exist.
	else if (argc==2){
		fName = argv[1];
		fptr = fopen(argv[1], "rw+");
		// If error occurs when trying to open file or create file
		if (fptr == nullptr){
			perror("Opening File");
			return EXIT_FAILURE;
		}
		else {
			fData = getfData();
		}
	}

	// Handles case when no file name is given. Opens a new untitled document.
	else{
		fName = "untitled.txt";
		fptr = nullptr;
	}


	int ssRows, ssCols;

	initscr();
	cbreak();	// return input one char at a time instead of a waiting for a termination character
	getmaxyx(stdscr, ssRows, ssCols);	// get max line and width of stdscr
	WINDOW * edScr = setSS(stdscr);

	getch();

	endwin();





//	do{
//		int ch = getch();
//    	switch(ch){
//
//    	case KEY_F(1):
//
//    	case KEY_UP:
//
//		case KEY_DOWN:
//
//		case KEY_RIGHT:
//
//		case KEY_LEFT:
//    	}	// end ch switch
//
//    } while (true);



}// END MAIN





//void drawMenu(unsigned int menuItem){
//
//	int c;
//	char menu[4][] = {
//			"OPEN",
//			"SAVE",
//			"SAVE AS",
//			"EXIT"
//	   };
//	clear();
//	addstr("MENU");
//
//	for(c=0; c<4; c++){
//		if( c==menuItem){ attron(A_REVERSE); }
//		mvaddstr(3+(c*2),20,menu[c]);
//		attroff(A_REVERSE);
//	}
//
//}	// end drawMenu
//
//void openMenu(WINDOW * mainWin){
//	  int mRows, mCols;
//	  getmaxyx(mainWin, mRows, mCols);
//	  WINDOW * menu = newwin(0,0,0,0);
//	  keypad(menu, TRUE);
//	  drawMenu(0);
//	  noecho();
//
//
//}	// end openMenu

WINDOW * setSS(WINDOW * stdscr){
	int ssRows, ssCols;
	getmaxyx(stdscr, ssRows, ssCols);	// get max line and width of stdscr

	// Print F1:Menu
	attrset(A_BOLD);
	move(0,0);
	addstr("F1: MENU");

	// Print Program Title
	move(0,(ssCols/2)-8);
	addstr("CSCI 1730 Editor!");

	// Print File Name
	move(ssRows-1, 0);
	addstr(fName.c_str());
	attroff(A_BOLD);

	// Draw editing area & with border
	WINDOW * edScrBorder = derwin(stdscr, ssRows-2, ssCols, 1, 0);
	box(edScrBorder, 0, 0);
	WINDOW * edScr = derwin(edScrBorder, ssRows-4, ssCols-2,1,1);

	refresh();
	return edScr;
}	// end setSS


vector<string> * getfData(){
	vector<string> * fData = new vector<string>;

	if (fptr == nullptr){
//		fData->push_back("");
		return fData;
	}

	string ln("");
	char c;
	while((c = fgetc(fptr)) != EOF) {
		// Read characters into the string ln until \n is reached.
		if(c != '\n') {
		  if(c != '\t'){
			  ln+= c;
		  }else{ln+= "	"; } // inserts tab
		}
		// Once \n is reached, pushes ln to vector
		else{
		  ln+= c;
		  fData->push_back(ln);
		  ln = "";
		}
	}	// end loop for converting file data into vector

	return fData;
}	// end getfData

void wfData(){
	// Handles case when no open file is associated with data by creating new file.
    if(fptr == nullptr){
    	fptr = fopen(fName, "rw+");
    }
    for(vector<string>::iterator i = fData->begin(); i != fData->end(); i++){
      fprintf(fptr, (*i).c_str());
    }
}	// end wfData

void wedScr(){









}





