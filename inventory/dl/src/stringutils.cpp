#include<stringutils>
#include<string.h>
int compareStringIgnoreCase(const char *a,const char*b)
{
if(a==NULL) return -1;
if(b==NULL) return 1;
if(a==b) return 0;
char c,d;
while(*a!='\0' && *b!='\0')
{
c=*a;
d=*b;
if(c>='A' && c<='Z') c=c+32;
if(d>='A' && d<='Z') d=d+32;
if(c!=d) return c-d;
a++;
b++;
}
if(*a==*b) return 0;
c=*a;
if(c>='A' && c<='Z') c=c+32;
d=*b;
if(d>='A' && d<='Z') d=c+32;
return c-d;
}

string stringTrimme(string title)
{

int i,j;
char newstr[51];
for(i=0,j=0; title[i]!='\0'; i++)
{

if(title[i]!=' ')
{
newstr[j]=title[i];
j++;
}
else if(j!=0 && newstr[j-1]!=' ')
{
newstr[j]=' ';
j++;
}

}

newstr[j]='\0';
int len;
len=strlen(newstr);
i=len-1;
if(newstr[i]==' ')
{
while(newstr[i]==' ') i--;
newstr[i+1]='\0';
}

return string(newstr);
}
