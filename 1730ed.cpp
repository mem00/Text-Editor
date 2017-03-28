#include <cstdlib>
#include <ncurses.h>
#include <iostream>
#include <menu.h>

using namespace std;
char *choices[] = {
  "Open",
  "Save",
  "Save As"
  "Exit"
};

int main(const int argc, const char * argv[]) {
  ITEM **my_items;
  MENU *my_menu;
  WINDOW *my_menu_win;
  int n_choices;
  int c;

  File * file = fopen(argv[1], "r");
  if(file == 0) { perror(argv[0]); }

  int y, x;
  initscr();
  cbreak();

  getmaxyx(stdscr, y, x);
  Window * pad = newpad(y, x);

  int txtx;

  while((txtx = fgetc(file) != EOF)
  {
    wprintw(pad, "%c", txtc);
  }//while                                                                                                                                  

  fclose(file);

  move(0,0);
  scrollok(pad, TRUE);
  keypad(pad, TRUE);
  prefresh(pad, 0, 0, 0, 0, y, x);

  //create items                                                                                                                            
   n_choices = 4;
   my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
   for(int i = 0; i < n_choices; i++) {
     my_items[i] = new_item(choices[i], choices[i]);
    }

   //create menu                                                                                                                            
    my_menu = new_menu((ITEM **)my_items);

    //create menu mindow                                                                                                                    
    my_menu_win = newwin(10,40,4,4);
    keypad(my_menu_win, TRUE);

    //set main window and sub window                                                                                                        
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

    //set menu mark to string "*"                                                                                                           
    set_menu_mark(my_menu, "*");

    //print a border and title                                                                                                              
    box(my_menu_win, 0, 0);
    print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
    mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
    mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
    mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
    mvprintw(LINES - 2, 0, "F1 to exit");
    refresh();

    //post menu                                                                                                                                      
    post_menu(my_menu);
    wrefresh(my_menu_win);

    while((c = wgetch(my_menu_win)) != KEY_F(1))
      {       switch(c)
          {case KEY_DOWN:
              menu_driver(my_menu, REQ_DOWN_ITEM);
              break;
          case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
          }
        wrefresh(my_menu_win);
      }

    // deallocate memory       
         unpost_menu(my_menu);
    free_menu(my_menu);
    for(int i = 0; i < n_choices; ++i)
      free_item(my_items[i]);
    endwin();


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
  }// end loop for scrolling with arrow keys                                                                                                         


  endwin();
  return EXIT_SUCCESS;
}//main                                                                                                                                              

   
        
      
