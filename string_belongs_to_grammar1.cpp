#include<iostream>
#include<ctype.h>
#include<string.h>
using namespace std;
int main()
{
char a[20];
int b=0,c=0;
cout<<"Given grammar is:\nE->E+T/E-T/T\nT->T*F/ T/E /F\nF->(E)/i\n\n\tEnter the string you want to check:\n";
cin>>a;
int d=strlen(a);
if(d==1&&a[0]=='i')
{
cout<<"string belongs to a given grammar";
return 0;
}
if(a[0]=='i')
for(c=1;c<d;c++)
	{
	if(a[c-1]=='i')
	{
	if(a[c]!='+'&&a[c]!='-'&&a[c]!='*'&&a[c]!='/')
	{
	b=0;
	break;
	}
	}
	if(a[c-1]=='+'||a[c-1]=='-'||a[c-1]=='*'||a[c-1]=='/')
	if(a[c]=='i')
	b=1;
	}
if(b==0)
cout<<"string does not belong to a given grammar";
if(b==1)
cout<<"string belongs to a given grammar";
return 0;
}
