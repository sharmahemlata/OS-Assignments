#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symtab.h"

char *regs[] = { "", "AREG,", "BREG,", "CREG,", "DREG," };
char *ccs[] = { "", "LT", "LE", "EQ", "GT", "GE", "ANY" };

char *opcodes[] =
  { "STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV",
  "READ", "PRINT"
};
char *dirs[] = { "", "START", "END", "ORIGIN", "EQU", "LTORG" };
char *dls[] = { "", "DS", "DC" };

char tok1[10], tok2[10], tok3[10], tok4[10];

char *type;
char *oper = NULL;

int toks;

struct intermediate
{
  int addr;
  char opcode[10];
  char operand[10];
  struct intermediate *next;
};

struct intermediate *head = NULL;


void
addinter (int addr, int opcode, int operand)
{
//printf("\ttype:%s\topcode:%d\toper:%s\t%d",type,opcode,oper,operand);
  char one[10], two[10], err[4];
  sprintf (err, "null");
/*iif(oper==NULL)
{
node->operand = NULL;
}
else
{
sprintf(two,"<%s,%d>",oper,operand);
}
sprintf(one,"<%s,%d>",type,opcode);*/
//sprintf(two,"<%s,%d>",oper,operand);
  struct intermediate *node;
  node = (struct intermediate *) malloc (sizeof (struct intermediate));
  node->addr = locarr[j];
  if (oper == NULL)
    {
      strcpy (node->operand, err);
    }
  else
    {
      sprintf (two, "<%s,%d>", oper, operand);
    }
  sprintf (one, "<%s,%d>", type, opcode);

//strcpy(node->opcode,one);
//strcpy(node->operand,two);

//sprintf(node->opcode,"<%s,%d>",type,opcode);
//sprintf(node->operand,"<%s,%d>",oper,operand);

  if (opcode > 0 && opcode < 9 && strcmp (type, "IS") == 0)
    {
      char append[4];
//printf("%s",tok3);
      if (toks == 4)
	{
//printf("\nprocessing:%s",tok3);
	  sprintf (append, " %d", getindex (getlist (tok3), tok3));
	}
      else
	{
//printf("\nprocessing %s",tok2);
	  sprintf (append, " %d", getindex (getlist (tok2), tok2));
	}
//strcat(node->opcode,append);
//sprintf(one,"<%s,%d>  %d ",type,opcode,getindex(getlist(tok3),tok3));
      strcat (one, append);
//printf("appending:%s",one);
    }

  else
    {
      sprintf (one, "<%s,%d>", type, opcode);
    }

  strcpy (node->opcode, one);
  strcpy (node->operand, two);

  node->next = NULL;
  if (head == NULL)
    {
      head = node;
    }
  else
    {
      struct intermediate *p;
      p = head;
      while (p->next != NULL)
	{
	  p = p->next;
	}
      p->next = node;
    }
  j++;
}

void
display ()
{
  struct intermediate *n;
  n = head;
  while (n->next != NULL)
    {
      printf ("\n %d  %s ", n->addr, n->opcode);
      if (strcmp (n->operand, "null") != 0)
	{
	  printf (" %s", n->operand);
	}
      n = n->next;
    }
  printf ("\n");
}


int
getindex (int a, char search[])
{
  char **list;

  switch (a)
    {
    case 1:
      list = regs;
      type = "REG";
      break;
    case 2:
      list = ccs;
      type = "CC";
      break;
    case 3:
      list = opcodes;
      type = "IS";
      break;
    case 4:
      list = dirs;
      type = "AD";
      break;
    case 5:
      list = dls;
      type = "DL";
      break;
    default:
      printf ("Invalid option");
    }
  int pos = 0;
  do
    {
      if (strcmp (search, list[pos]) == 0)
	{
	  return pos;
	}
      pos++;
    }
  while (list[pos] != NULL);
  return -1;
}



int
getsym (char sym[])
{
  int srno = 1;
  struct symtab *s;
  s = (struct symtab *) malloc (sizeof (struct symtab));
  FILE *fp = fopen ("symbol.txt", "r");
  if (fp != NULL)
    {
      while (!feof (fp))
	{
	  fread (s, sizeof (struct symtab), 1, fp);
	  if (strcmp (s->symbol, sym) == 0)
	    {
	      return srno;
	    }
	  srno++;
	}
      fclose (fp);
      return -1;
    }
  else
    {
      printf ("\nError in opening file:");
      exit (0);
    }
}

int
getlist (char tok[])
{
  if (iscc (tok))
    return 2;
  if (isreg (tok))
    return 1;
//if(iscc(tok))
//return 2;
  if (isopcode (tok))
    return 3;
  if (isdir (tok))
    return 4;
  if (isdl (tok))
    return 5;
  return 0;
}

void
one (char tok1[])
{
  oper = NULL;
  addinter (loc_count, getindex (getlist (tok1), tok1), -1);
}


void
two (char tok1[], char tok2[])
{
  int listno;
  if (isany (tok1))
    {
      listno = getlist (tok1);
      if (!isany (tok2) && !isnum (tok2))
	{
	  oper = "S";
	  addinter (loc_count, getindex (listno, tok1), getsym (tok2));
	}
      if (isnum (tok2))
	{
	  oper = "C";
	  addinter (loc_count, getindex (listno, tok1), atoi (tok2));
	}
    }
  else
    {
      if (isany (tok2))
	{
	  addinter (loc_count, getindex (listno, tok1), -1);
	}
    }
}

void
three (char tok1[], char tok2[], char tok3[])
{
  if (strcmp ("BC", tok1) == 0 && getlist (tok2) == 2 && !isany (tok3))
    {
      oper = "S";
      addinter (loc_count, getindex (getlist (tok1), tok1), getsym (tok3));
    }
  else
    {
      if (isopcode (tok1))
	{
	  oper = "S";
	  addinter (loc_count, getindex (getlist (tok1), tok1),
		    getsym (tok3));
	}
      else if (isdl (tok2) && isnum (tok3))
	{
	  oper = "C";
	  addinter (loc_count, getindex (getlist (tok2), tok2), atoi (tok3));
	}
      else if (strcmp ("EQU", tok2) == 0 && isnum (tok3))
	{
	  oper = "C";
	  addinter (loc_count, getindex (getlist (tok2), tok2), atoi (tok3));
	}
      else
	{
	  oper = "S";
	  addinter (loc_count, getindex (getlist (tok2), tok2),
		    getsym (tok3));
	}
    }
}

void
four (char tok1[], char tok2[], char tok3[], char tok4[])
{
  oper = "S";
  addinter (loc_count, getindex (getlist (tok2), tok2), getsym (tok4));
}






void
main (int argv, char *argc[])
{
  if (argv != 2)
    {
      printf ("Invalid number of arguments");
    }
  else
    {
      makesymbol (argc[1]);
      j = 0;
      FILE *fp = fopen (argc[1], "r");
      char line[80], line1[80];
      char *str = "null";
      //int toks,a;
      int l_no = 1;
      while (!feof (fp))
	{
	  fgets (line, sizeof (line), fp);
	  sprintf (line1, "%s", line);
	  //printf("\n%s:",line1);
	  toks = 0;
	  char *token = strtok (line, " ");
	  while (token != NULL)
	    {

	      toks++;
	      token = strtok (NULL, " ");
	    }


	  strcpy (tok1, str);
	  strcpy (tok2, str);
	  strcpy (tok3, str);
	  strcpy (tok4, str);


	  switch (toks)
	    {
	    case 1:
	      token = strtok (line1, "\n");
	      strcpy (tok1, token);
	      one (token);
	      break;
	    case 2:
	      token = strtok (line1, " ");
	      strcpy (tok1, token);
	      token = strtok (NULL, "\n");
	      two (tok1, token);
	      break;
	    case 3:
	      token = strtok (line1, " ");
	      strcpy (tok1, token);
	      token = strtok (NULL, " ");
	      strcpy (tok2, token);
	      token = strtok (NULL, "\n");
	      three (tok1, tok2, token);
	      break;
	    case 4:
	      token = strtok (line1, " ");
	      strcpy (tok1, token);
	      token = strtok (NULL, " ");
	      strcpy (tok2, token);
	      token = strtok (NULL, " ");
	      strcpy (tok3, token);
	      token = strtok (NULL, "\n");
	      four (tok1, tok2, tok3, token);
	      break;
	    default:
	      printf ("Erro:Invalid assembly language instruction %d", l_no);
	    }
	  l_no++;
	}
      display ();
    }
}
