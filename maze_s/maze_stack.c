#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

#define rowsize 200
#define colsize 200
#define dirsize 4
#define startX 0
#define startY 0

typedef struct {
	int vert;
	int horiz;
} offsets;
offsets movedir[dirsize]={{-1,0} , {0,1} , {1,0} , {0,-1}};		//north , east , south , west

typedef struct{
	int row;
	int col;
	int dir;
} elements;
elements stack[rowsize * colsize];

int i , j , top , mrow ,mcol;
void push(elements item , elements *stack , int *top){
		stack[++(*top)]=item;
}

elements pop(elements *stack , int *top){
	return stack[(*top)--];
}

void initial();
void printm(int (*maze)[colsize], int mrow, int mcol);
void readmaze(FILE *fp ,int (*maze)[colsize] , int (*mark)[colsize],int *mrow ,int *mcol);
void path(int (*maze)[colsize] , int (*mark)[colsize] , int *mrow ,int *mcol ,int *top);
int i , j ,top ,mrow ,mcol;

int main(){
	int mrow=0;
	int mcol=0;
	int top=0;
	int maze1[rowsize][colsize] , maze2[rowsize][colsize] , mark1[rowsize][colsize] , mark2[rowsize][colsize] ;
	FILE *fp1 , *fp2;
	fp1=fopen("maze-layer1.txt","r");
	fp2=fopen("maze-layer2.txt","r");

	initial();
//	readmaze(fp1,maze1,mark1,&mrow,&mcol);
//	path(maze1,mark1 ,&mrow,&mcol ,&top);
	readmaze(fp2,maze2,mark2,&mrow,&mcol);
	path(maze2 , mark2,&mrow,&mcol,&top);

}

void readmaze(FILE *fp , int (*maze)[colsize] , int (*mark)[colsize],int *mrow , int *mcol){
	int x=startX;
	int y=startY;
	int haha;
	char c;
	i=0;j=0;
	(*mrow)=0;
	(*mcol)=0;
	if(fp==NULL){
		printf("Not Found maze.txt\n");
		exit(1);
	}
	while((c=getc(fp))!=EOF){
		if((c==' ') || (c=='-') || (c=='0') || (c=='|') || (c=='_')){			//wall
			maze[i][j++]=0;
		}
		if(c=='1')
			maze[i][j++]=1;
		if(c=='2')
			maze[i][j++]=2;
		if(c=='\n'){
			i++;
			(*mrow)=i;
			(*mcol)=j;
			j=0;
		}
	}
	move(y,x);
	for(i=0;i<(*mrow);i++)
		for(j=0;j<(*mcol);j++){
			mark[i][j]=maze[i][j];
		}
	fclose(fp);
	
}

void printm(int (*maze)[colsize] , int mrow, int mcol){
	int x=startX;
	int y=startY;
	move(y,x);
	for(i=0;i<mrow;i++){
		for(j=0;j<mcol;j++){
			switch(maze[i][j]){
				case 0: mvaddch(y,x++,'|'); break;
				case 1: mvaddch(y,x++,' '); break;
				case 2: mvaddch(y,x++,'$'); break;
			}
		}
		mvaddch(y++,x,'\n');
		x=0;
	}
}

void path(int (*maze)[colsize] , int (*mark)[colsize],int *mrow ,int *mcol , int *top){
	int x=1;
	int y=1;
	int c;
	int kyle=(*mrow);
	int lydia=(*mcol);
	int row=0;
	int col=0;
	int dir=0;
	int money=0;
	int nextrow=0;
	int nextcol=0;
	int EXIT_ROW=0;
	int EXIT_COL=0;
	int found=0;
	elements position;
	mark[1][1]=0; 			//0代表走過，不能再走了(because wall is same with 0)
	(*top)=0; i=0; 
	EXIT_ROW=(*mrow)-2; EXIT_COL=(*mcol)-2;
	stack[0].row=1; stack[0].col=1; stack[0].dir=1;
	while(((*top)>-1) && (!found)){
		position=pop(stack , top);
		row=position.row;
		col=position.col;
		dir=position.dir;
		while((dir<4) && (!found)){
			nextrow=row+movedir[dir].vert;
			nextcol=col+movedir[dir].horiz;
			if((nextrow==EXIT_ROW) && (nextcol==EXIT_COL)){
				found=1;
				position.row=row;
				position.col=col;
				position.dir= ++dir;
				push(position,stack,top);
			}
			else if ((maze[nextrow][nextcol]!=0) && (mark[nextrow][nextcol]!=0)){
				mark[nextrow][nextcol]=0;
				position.row=row; 
				position.col=col;
				position.dir= ++dir;
				push(position , stack , top);
				row=nextrow;
				col=nextcol;
				dir=0;
			}
			else ++dir;
		}
	}
	if(found){
		printm(maze,kyle,lydia);
		attron(A_REVERSE);
		for(i=0;i<=(*top);i++){
			mvaddch(y,x,' ');
			mvaddch(stack[i].row,stack[i].col,'*');
			y=stack[i].row;
			x=stack[i].col;
		}
		attroff(A_REVERSE);
		c=getch();
		if(c==27){
			endwin();
			exit(1);
		}
	}
	else
		printf("The maze doesn't have path");
}

void initial(){
	initscr();
	cbreak();
	nonl();
	noecho();
	intrflush(stdscr,FALSE);
	keypad(stdscr,TRUE);
	refresh();
}
