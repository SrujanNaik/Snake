#include<ncurses.h>
#include<stdlib.h>
#include<time.h>

#define row 32 
#define col 64

struct snake_body {
	int x;
	int y;
	struct snake_body* previous;
	struct snake_body* next;
};

void display();
void snake(struct snake_body**);
void snake_length(struct snake_body**);
void snake_print(struct snake_body**,int,int,int);

int main(){
	struct snake_body* head = NULL;
	initscr();            
	noecho();             
	cbreak();             
	curs_set(0);          
	keypad(stdscr, TRUE);

	srand(time(0));
	display();
	snake(&head);

	endwin();
	return 0;
}

void snake_print(struct snake_body** head,int x,int y,int score){
	struct snake_body* temp = *head;
	if(temp->previous == NULL){
		temp->y = y;
		temp->x = x;
		mvprintw(temp->y,temp->x,"0");
	}
	temp->y = y;
	temp->x = x;
	while(temp->previous != NULL){
		temp = temp->previous;
		if(temp->x == x&&temp->y ==y){
			clear();
			move(0,0);
			printw("game over");
			move(1,0);
			printw("Your score : %d",score);
			getch();
			endwin();
			exit(0);
		}
	}
	mvaddch(temp->y,temp->x,' ');
	while(temp->next != NULL){
		temp->x = temp->next->x;
		temp->y = temp->next->y;
		mvprintw(temp->y,temp->x,"0");
		temp = temp->next;
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
	h->x = x;
	h->x = y;
	h->next = NULL;
	h->previous = NULL;

	*head = h;
	//initial food location
	int food_location_y = 1;
	int food_location_x = 2;
	int previousX = food_location_x;
	int previousY = food_location_y;
	if(food_location_x == 0 || food_location_x == -1) food_location_x = 1;
	if(food_location_y == 0 || food_location_y == -1) food_location_y = 1;
	move(food_location_y,food_location_x);
	printw("*");
	refresh();

	int score = 0;
	while(gameover){
		timeout(1000);
		ch = getch();

		if(ch != ERR){
			if(ch == KEY_LEFT){
				x--;
				if(x < 1) x = col-2;
				snake_print(head,x,y,score);
			}
			else if(ch == KEY_RIGHT){
				x++;
				if(x > col - 2) x = 1;
				snake_print(head,x,y,score);
			}
			else if(ch == KEY_UP){
				y--;
				if(y < 1) y = row-2;
				snake_print(head,x,y,score);
			}
			else if(ch == KEY_DOWN){
				y++;
				if(y > row-2) y = 1;
				snake_print(head,x,y,score);
			}
			previous = ch;
			refresh();
		}
		else{
			if(previous == KEY_LEFT){
				x--;
				if(x < 1) x = col-2;
				snake_print(head,x,y,score);
			}
			else if(previous == KEY_RIGHT){
				x++;
				if(x > col - 2) x = 1;
				snake_print(head,x,y,score);
			}
			else if(previous == KEY_UP){
				y--;
				if(y < 1) y = row-2;
				snake_print(head,x,y,score);
			}
			else if(previous == KEY_DOWN){
				y++;
				if(y > row-2) y = 1;
				snake_print(head,x,y,score);
			}
			refresh();
		}
		//update food loaction after consumption
		if(previousX == x && previousY == y){
			int food_location_y = rand()%row-1;
			int food_location_x = rand()%col-1;
			if(food_location_x == 0 || food_location_x == -1) food_location_x = 1;
			if(food_location_y == 0 || food_location_y == -1) food_location_y = 1;
			previousX = food_location_x;
			previousY = food_location_y;
			move(food_location_y,food_location_x);
			printw("*");
			snake_length(head);
			score++;
			refresh();
		}
		move(0,66);
		printw("%d",score);
		refresh();

	}
	getch();
}

void snake_length(struct snake_body** head){
	struct snake_body* newnode = (struct snake_body*)malloc(sizeof(struct snake_body));
	newnode->next = NULL;
	newnode->previous = NULL;

	struct snake_body* temp = *head;
	while(temp->previous != NULL){
		temp = temp->previous;
	}
	temp->previous = newnode;
	newnode->next = temp;
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














