#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct mnt
{
  char name[10];
  int npp, nkp, mdtptr, kpdtptr;
};

struct mnt one[10];

struct mdt
{
  char lbl[20], opcode[20], reg[20], oper[20];
};

struct mdt arr[4];


char apt[10][20];

char pnt[10][20];


struct kpdtab
{
  char formal[10];
  char actual[10];
};
struct kpdtab k;

FILE *fp, *tar;





void
init ()
{
  strcpy (arr[0].opcode, "MOVER");
  strcpy (arr[0].reg, "AREG,");
  strcpy (arr[0].oper, "(P,1)");
  strcpy (arr[1].opcode, "(P,3)");
  strcpy (arr[1].reg, "AREG,");
  strcpy (arr[1].oper, "(P,2)");
  strcpy (arr[2].opcode, "MOVEM");
  strcpy (arr[2].reg, "AREG,");
  strcpy (arr[2].oper, "(P,1)");
  strcpy (arr[3].opcode, "MEND");
  strcpy (arr[3].reg, "");
  strcpy (arr[3].oper, "");


  strcpy (one[0].name, "CALC");
  one[0].npp = 2;
  one[0].nkp = 1;
  one[0].mdtptr = 0;
  one[0].kpdtptr = 0;

  strcpy (pnt[0], "X");
  strcpy (pnt[1], "Y");
  strcpy (pnt[2], "OP");


  strcpy (k.formal, "OP");
  strcpy (k.actual, "ADD");
}


void
main (int argv, char *argc[])
{
  init ();
  int i;
  printf
    ("\n-------------------MACRO NAME TABLE------------------------------\n");
  fflush (stdout);
  printf ("\tName\tnpp\tnkp\tmdtptr\tkpdtptr\n");
  fflush (stdout);
  printf ("\t%s\t%d\t%d\t%d\t%d\n", one[0].name, one[0].npp, one[0].nkp,
	  one[0].mdtptr, one[0].kpdtptr);
  fflush (stdout);


  printf
    ("\n----------------------Parameter Name Table-------------------------\n");
  fflush (stdout);

  printf ("\t%s\n\t%s\n\t%s\n", pnt[0], pnt[1], pnt[2]);
  fflush (stdout);


  printf
    ("\n---------------------Keyword Parameter Default Value Table---------------\n");
  fflush (stdout);

  printf ("\tParameter\tValue\n");
  printf ("\t%s\t\t%s\n", k.formal, k.actual);
  fflush (stdout);


  printf
    ("\n----------------------Macro Defination Table----------------------\n");
  for (i = 0; i < 4; i++)
    {
      printf ("\n\t%s\t%s\t%s\t", arr[i].opcode, arr[i].reg, arr[i].oper);
    }
  printf ("\n");
}
