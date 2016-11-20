#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main()
{

//take input from file
FILE *fp;
char string[50];
fp=fopen("grammar.txt","r");
fgets(string,50, (FILE*)fp);

int count=0,state=0;
int length;

cout<<"The grammar is -> \t";
cout<<"S->aS , S->ab , S->Sb\n";
cout<<"Taking sting as input from file\n";

cout<<string<<"\n";

while(string[count]!='\0')
  {
    switch(state)
    {
    case 0: if (string[count]=='a')
  state=1;
  else
  state=3;
  break;
   case 1: if (string[count]=='a')
  state=1;
  else if(string[count]=='b')
  state=2;
  else
  state=3;
  break;
   case 2: if (string[count]=='b')
  state=2;
  else
  state=3;
  break;
   default: break;
  }
  count++;
  if(state==3)
  break;
 }
 if(state==2)
  cout<<"string is accepted\n";
  else
  cout<<"string is not accepted\n";

	return 0;
}