// return the first index in the string
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i , j , lenp , lens;
void failture(char *pat , int* nextcomp, int now, int com);
void compare(char *string ,char *pat, int* nextcomp,int i, int j);

int main(){
	char string[]="abxabcxyzaby";
	char pat[]="xyz";
	int *nextcomp;
	int now,com;
	lens=strlen(string);
	lenp=strlen(pat);
	nextcomp=(int*)malloc(sizeof(int)*lenp);
	for(i=0;i<lenp;i++)
		nextcomp[i]=9;
	now=1; com=0;
	nextcomp[com]=0;
	failture(pat,nextcomp,now,com);
	for(i=0;i<lenp;i++)
		printf("nextcomp is : %d\n",nextcomp[i]);

	i=0; j=0;
	compare(string,pat,nextcomp,i,j);
}

void failture(char* pat , int* nextcomp , int now, int com){
	if(now==lenp)
		return;
	if((com==0) && (pat[now]!=pat[com])){
		nextcomp[now]=0;
		now++;
	}
	else if(pat[now]==pat[com]){
		nextcomp[now]=com+1;
		now++; com++;
	}
	else if((com!=0) && (pat[now]!=pat[com])){
		com=nextcomp[com-1];
	}
	
	failture(pat,nextcomp,now,com);
}

void compare(char* string , char* pat,int* nextcomp , int i,int j){
	if((i==lens) || (j==lenp)){
		if(j==lenp)
			printf("Found!! :D\n");
		else
			printf("Not Found :(\n");
		return;
	}
	if(string[i]==pat[j]){
		i++; j++;
	}
	else if((j!=0) && (string[i]!=pat[j])){
		j=nextcomp[j-1];
	}
	else if((j==0) && (string[i]!=pat[j])){
		i++;
	}
	compare(string,pat,nextcomp,i,j);
}