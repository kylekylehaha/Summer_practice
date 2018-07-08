#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define len 10

int i,j,select;
int seq[len]={0,3,5,6,18,20,35,14,17,28};
void sort(int* seq, int select ,int left,int right);
void swap(int x,int y ,int *seq);

int main(){
	printf("Enter 1 or 2 for descend or ascend \n");
	scanf("%d",&select);
	printf("Before sort,the seq is: ");
	for(i=0;i<len;i++)
		printf("%3d",seq[i]);
	printf("\n");

	sort(seq,select,0,len-1);
	printf("After sort,the seq is : ");
	for(i=0;i<len;i++)
		printf("%3d",seq[i]);
	printf("\n");
	
}

void swap(int x,int y,int *seq){
	int temp=seq[x];
	seq[x]=seq[y];
	seq[y]=temp;
}

void sort(int *seq,int select,int left, int right){
	int pivotindex=(left+right)/2;
	int pivot=seq[pivotindex];
	int index;

	if(right<=left)
		return;
	index=left;
	swap(pivotindex,right,seq);
	for(i=left;i<right;i++){
		if(select==1){			// choose descend
			if(seq[i]>=pivot){
				swap(index,i,seq);
				index++;
			}
		}
		else{
			if(seq[i]<=pivot){			//choose ascend
				swap(index,i,seq);
				index++;
			}
		}
	}
	swap(index,right,seq);
	sort(seq,select,left,index-1);
	sort(seq,select,index+1,right);
}