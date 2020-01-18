#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int HowManycmd(FILE*);
int WhatCmd(FILE*);
void printFile(FILE*);
void lw(FILE*,int,int,int);
void lm(int);
void ls(int);


int main(int argc, char *argv[]){
	
	char* cin;
	cin=argv[1];
	
	FILE* pfile;
	pfile=fopen(cin,"r");
	
	if(pfile == NULL) {
	  printf("Cannot open!\n");
	  return(0);
	} 
	int numCmd;
	numCmd=HowManycmd(pfile);
	
	if(numCmd!=0){//there is command//// 	1: LW	2:LM 	3:FT 	4:LS 
		fseek(pfile,0,SEEK_SET);
		int x=0;
		int numWC;
		
		int cmdArr[5];
		cmdArr[1]=0;
		cmdArr[2]=0;
		cmdArr[3]=1;
		cmdArr[4]=0;
		
		for(x=0;x<numCmd;x++){
			
			numWC=WhatCmd(pfile);
			if(numWC==3){//FT
				char OFF[4];
				strcpy(OFF,"off");
				int compare;
				
				char strFT[4];
				fscanf(pfile,"%s",strFT);
				compare=strcmp(strFT,OFF);
				compare++;
				if(compare==1)
					cmdArr[3]=0;////off
				else
					cmdArr[3]=1;///on
				
			}
			else
				fscanf(pfile,"%d",&cmdArr[numWC]);
		}
		////////////////////////////////////
		//printf("LW value: %d\n",cmdArr[1]);
		
		//read 
		
		if(cmdArr[1]!=0){
			if(cmdArr[3]!=0){//FT on 
				lw(pfile,cmdArr[1],cmdArr[2],cmdArr[4]);
				
				
			}
			else{//FT off
				printFile(pfile);
				
			}
			
		}
		else{//LW=0
			printFile(pfile);
		}
			
	}
	else{//No command
		
		fseek(pfile,0,SEEK_SET);
		printFile(pfile);
	}	

	return 0;
}

int HowManycmd(FILE* fp){
	int a;
	char str1[200];

	int counter=0;
	while (1)
	{
		
		a=fgetc(fp);
		if (a!=46){
		break;
		}
    counter++;
    fscanf(fp,"%s",str1);
	////
	//printf("first str: %s\n",str1);
	///
    fscanf(fp,"%s",str1);
	//
	//printf("swcond str: %s\n",str1);
	///
	a=fgetc(fp);
	}
	
	return counter;
}



int WhatCmd(FILE* fp){
	char str1[4];
	int compare;
	char LW[4],LM[4],FT[4],LS[4];
	strcpy(LW,".LW");
	strcpy(LM,".LM");
	strcpy(FT,".FT");
	strcpy(LS,".LS");
	
	fscanf(fp,"%s",str1);
	compare =strcmp(str1,LW);
	compare++;
	if(compare==1)
		return 1;
	compare =strcmp(str1,LM);
	compare++;
	if(compare==1)
		return 2;
	compare =strcmp(str1,FT);
	compare++;
	if(compare==1)
		return 3;
	compare =strcmp(str1,LS);
	compare++;
	if(compare==1)
		return 4;
	return 0;
	
}

void printFile(FILE* fp){
		int a;
		a=fgetc(fp);
		while(a!=EOF)
		{
			printf("%c",a);
			a=fgetc(fp);
			
		}
		fclose(fp);
	
}

void lw(FILE* fp,int numLW,int numLM,int numLS){
	
	/////////////////
	/*printf("lw: %d\n",numLW);
			printf("lm: %d\n",numLM);
			
			printf("ls: %d\n",numLS);
	*//////////////////
	char str1[200];
	int a;
	int numstr=0;
	
	lm(numLM);
	numLW-=numLM;
	
	fscanf(fp,"%s",str1);
	numstr+=strlen(str1);
	a=fgetc(fp);///////////////////////////
	
	while(a!=EOF){
		
 		if (numstr>numLW){
			numstr=strlen(str1);
			////////////////////////////
			//printf("\ngreater numstr: %d\n",numstr);
			//printf("str1: %s",str1);
			/////////////////////////
			
			printf("\n");
			ls(numLS);
			lm(numLM);
			//printf("%s ",str1);///////////////////gsdhfdgagsgh
			
			//numstr+=strlen(str1);
			
			
			printf("%s ",str1);
			numstr++;
			//////////////////////////////
			
			if(a==10){
			a=fgetc(fp);
			a=fgetc(fp);
			///
				/*printf("\n a is %c\n",a);
				printf("%s",str1);
				printf("123456789\n");
				*/
				//
				if(a==10){
					ls(numLS);
					printf("\n");
					ls(numLS);
					lm(numLM);
				}
				else{
					fseek(fp,-1,SEEK_CUR);
				
				}
			
			}
			
			
			
		}
		else if (numstr==numLW){
			printf("%s\n",str1);//////////////////PROBLEM
			//printf("\nchang line equal: %s\n",str1);
			numstr=0;
			ls(numLS);
			lm(numLM);
			////////////////////////////
			if(a==10){
				a=fgetc(fp);
				a=fgetc(fp);
				///
				//printf("\n a is %c\n",a);
				//
				if(a==10){
				//ls
					printf("\n");
					ls(numLS);
					lm(numLM);
				}
				else{
					fseek(fp,-1,SEEK_CUR);
				}
			}
			
		}
			
		else{  //numstr<numLW
		     printf("%s",str1);
		     a=fgetc(fp);
		     numstr++;
		     //if(numstr<numLW){
		       printf(" ");
		     //}
		     
			if(a==10){
				a=fgetc(fp);
				//a=fgetc(fp);
				///
				//printf("\n a is %d\n",a);
				//
				if(a==10){
					ls(numLS);
					printf("\n");
					printf("\n");
					//printf("\nHELLO\n");
					//
					ls(numLS);
					//
					//printf("\nHELLO\n");
					numstr=0;
					lm(numLM);
				}
				else{
					fseek(fp,-1,SEEK_CUR);
				}
			}
			
			
		}
		//next read
		fscanf(fp,"%s",str1);
		numstr+=strlen(str1);
		a=fgetc(fp);
		fseek(fp,-1,SEEK_CUR);
		///
		//printf("\nless a: %d\n",a);
		///////////////////////////////////
		//numstr++;
	}
	/*
	if(numstr<=numLW){
		printf("%s",str1);
	}
	else{
		printf("\n%s",str1);
	}
	*/
	
	printf("\n");
}

void lm(int numLM){
	if(numLM!=0){
		char LMArr[200];
		int i=0;
		for(i=0;i<numLM;i++)
		{
			LMArr[i]=' ';
			printf("%c",LMArr[i]);
		}
		
	}
}

void ls(int numLS){
	
	int i=0;
	while(i<numLS){
		printf("\n");
		i++;

	}	
	
}

