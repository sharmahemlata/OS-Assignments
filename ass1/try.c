#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main()
{
char line[80];
char tok1[10],tok2[10],tok3[10];
printf("write something");
fgets(line,sizeof(line),stdin);
int a = sscanf(line,"%s%s%s",tok1,tok2,tok3);
printf("\n%d",a);
}
