#include<ncurses.h>
#include<stdlib.h>
#include<time.h>

#define row 32 
#define col 64

struct snake_body {
	struct snake_body* left;
	struct snake_body* right;
};

void display();
void create_map();
void snake(struct snake_body**);
void snake_body(struct snake_body**,int,int);
void food_placement();

int main(){
	struct snake_body* head = NULL;
	initscr();            
	noecho();             
	cbreak();             
	curs_set(0);          
	keypad(stdscr, TRUE);

	srand(time(0));
	display();
	create_map();
	snake(&head);

	endwin();
	return 0;
}

void snake_body(struct snake_body** head,int x,int y){
	struct snake_body* temp = *head;
	if(temp->left == NULL){
		mvprintw(y,x,"0");
	}
	while(temp->left != NULL){
		mvprintw(y,x,"0");
		temp = temp->left;
	}
}

void snake(struct snake_body** head){
	int x = 1,y = 1;
	move(y,x);
	bool gameover = 1;
	int previous = KEY_RIGHT;
	int ch;

	struct snake_body* h;
	h = malloc(sizeof(struct snake_body*));
	h->right = NULL;
	h->left = NULL;

	*head = h;

	while(gameover){
		timeout(1000);
		ch = getch();
		if(ch != ERR){
			if(ch == KEY_LEFT){
				mvaddch(y,x,' ');
				x--;
				if(x < 1) x = col-2;
				snake_body(head,x,y);
			}
			else if(ch == KEY_RIGHT){
				mvaddch(y,x,' ');
				x++;
				if(x > col - 2) x = 1;
				snake_body(head,x,y);
			}
			else if(ch == KEY_UP){
				mvaddch(y,x,' ');
				y--;
				if(y < 1) y = row-2;
				snake_body(head,x,y);
			}
			else if(ch == KEY_DOWN){
				mvaddch(y,x,' ');
				y++;
				if(y > row-2) y = 1;
				snake_body(head,x,y);
			}
			previous = ch;
			refresh();
		}
		else{
			if(previous == KEY_LEFT){
				mvaddch(y,x,' ');
				x--;
				if(x < 1) x = col-2;
				snake_body(head,x,y);
			}
			else if(previous == KEY_RIGHT){
				mvaddch(y,x,' ');
				x++;
				if(x > col - 2) x = 1;
				snake_body(head,x,y);
			}
			else if(previous == KEY_UP){
				mvaddch(y,x,' ');
				y--;
				if(y < 1) y = row-2;
				snake_body(head,x,y);
			}
			else if(previous == KEY_DOWN){
				mvaddch(y,x,' ');
				y++;
				if(y > row-2) y = 1;
				snake_body(head,x,y);
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













