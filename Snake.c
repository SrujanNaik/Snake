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

	endwin();
	return 0;
}

void display(){
	timeout(1000);
	int x = 0;
	int y = 0;

	move(0,0);
	WINDOW *win = newwin(row,col,x,y);
	box(win,'#','#');
	refresh();
	wrefresh(win);

	getch();
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
