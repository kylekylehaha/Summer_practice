#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 10
#define MAX_COLS 9
typedef struct {
	int col;
	int row;
	int value;
} term;

term a[MAX_TERMS];
term b[MAX_TERMS];
int i,j,numberTerm,numberCol;
void fastTranspose(term a[] , term b[]);

int main(){
	a[0].row=6; a[0].col=6; a[0].value=8;
	a[1].row=0; a[1].col=0; a[1].value=15;
	a[2].row=0; a[2].col=3; a[2].value=22;
	a[3].row=0; a[3].col=5; a[3].value=-15;
	a[4].row=1; a[4].col=1; a[4].value=11;
	a[5].row=1; a[5].col=2; a[5].value=3;
	a[6].row=2; a[6].col=3; a[6].value=-6;
	a[7].row=4; a[7].col=0; a[7].value=91;
	a[8].row=5; a[8].col=2; a[8].value=28;
	numberTerm=a[0].value;
	numberCol=a[0].col;

	printf("before transpose, the array a is: \n");
	for(i=0;i<numberTerm+1;i++)
		printf("%3d %3d %3d\n",a[i].row , a[i].col , a[i].value);

	fastTranspose(a,b);

	printf("after fastTranspose, the array is: \n");
	for(i=0;i<numberTerm+1;i++)
		printf("%3d %3d %3d\n",b[i].row , b[i].col , b[i].value);
}

void fastTranspose(term a[] , term b[]){
	int rowterm[MAX_COLS],startingPos[MAX_COLS];
	b[0].row=numberCol;
	b[0].col=a[0].row;
	b[0].value=numberTerm;
	for(i=0;i<MAX_COLS;i++)			//initial rowterm
		rowterm[i]=0;
	for(i=1;i<=numberTerm;i++)
		rowterm[a[i].col]++;
	startingPos[0]=1;
	for(i=1;i<=numberCol;i++)
		startingPos[i]=startingPos[i-1]+rowterm[i-1];
	for(i=1;i<=numberTerm;i++){
		j=startingPos[a[i].col]++;
		b[j].row=a[i].col;
		b[j].col=a[i].row;
		b[j].value=a[i].value;
	}
}