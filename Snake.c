#include<ncurses.h>
#include<stdlib.h>
#include<time.h>

#define row 32 
#define col 64

void display();
void create_map();
void snake();
void food_placement();

int main(){
	initscr();            
	noecho();             
	cbreak();             
	curs_set(0);          
	keypad(stdscr, TRUE);

	srand(time(0));
	display();
	create_map();
	snake();

	endwin();
	return 0;
}

void snake(){
	int x = 1,y = 1;
	move(y,x);
	printw("0");
	refresh();
	bool gameover = 1;
	int previous = KEY_RIGHT;
	int ch;

	while(gameover){
		timeout(1000);
		ch = getch();
		if(ch != ERR){
			if(ch == KEY_LEFT){
				x--;
				if(x < 1) x = col-2;
				mvprintw(y,x,"0");
			}
			else if(ch == KEY_RIGHT){
				x++;
				if(x > col - 2) x = 1;
				mvprintw(y,x,"0");
			}
			else if(ch == KEY_UP){
				y--;
				if(y < 1) y = row-2;
				mvprintw(y,x,"0");
			}
			else if(ch == KEY_DOWN){
				y++;
				if(y > row-2) y = 1;
				mvprintw(y,x,"0");
			}
			previous = ch;
			refresh();
		}
		else{
			if(previous == KEY_LEFT){
				x--;
				if(x < 1) x = col-2;
				mvprintw(y,x,"0");
			}
			else if(previous == KEY_RIGHT){
				x++;
				if(x > col - 2) x = 1;
				mvprintw(y,x,"0");
			}
			else if(previous == KEY_UP){
				y--;
				if(y < 1) y = row-2;
				mvprintw(y,x,"0");
			}
			else if(previous == KEY_DOWN){
				y++;
				if(y > row-2) y = 1;
				mvprintw(y,x,"0");
			}
			refresh();
		}

	}

	getch();
}

void display(){
	int x = 0;
	int y = 0;

	move(0,0);
	WINDOW *win = newwin(row,col,x,y);
	box(win,'#','#');
	refresh();
	wrefresh(win);

	refresh();
}

void create_map(){
	FILE *file = fopen("map.txt","a");
	if(file == NULL){
		printw("Game not loaded");
		exit(0);
	}

	for(int i = 0;i < row;i++){
		for(int j = 0;j < col;j++){
			fprintf(file,"*");
		}
	}
	
	fclose(file);
}













