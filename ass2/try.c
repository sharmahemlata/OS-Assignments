#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void main()
{
char hema[30];
struct name
{
char fname[30];
struct name *next;
};

struct name *head =NULL;

printf("enter a name");
scanf("%s",hema);




if(head==NULL)
{
struct name *new;
new = (struct name *)malloc(sizeof(struct name));
strcpy(new->fname,hema);
printf("%s",new->fname);
}


}
