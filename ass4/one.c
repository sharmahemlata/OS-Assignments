#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "inter.h"





char inst[12];



FILE *tar;
int
getsymadd (int pos)
{
  struct symtab *s;
  s = symhead;
  int i = 0;
  while (i != pos - 1 && s->next != NULL && s->addr!=-1)
    {
      s = s->next;
      i++;
    }
  return s->addr;
}

void
displaysymtab ()
{
  struct symtab *s;
  s = symhead;
  while (s->next != NULL)
    {
      if (s->addr != -1)
	{
	  printf ("\n%s\t%d", s->symbol, s->addr);
	}
      s = s->next;
    }
  if (s->addr != -1)
    {
      printf ("\n%s\t%d", s->symbol, s->addr);
    }
}



int
process (char opcode[])
{
  char *zero = "0";
  char **list, *val;
  char append[2];
  char more[1], test[1];
  sprintf (more, "%c", opcode[5]);
  sprintf (test, "%c", opcode[4]);
  char one[3], two, other[1];
  sprintf (one, "%c%c", opcode[1], opcode[2]);
  two = opcode[strlen (opcode) - 1];
  sprintf (other, "%c", two);
  if (strcmp (more, ">") == 0)
    {
      sprintf (val, "%c", opcode[4]);
    }
  else
    {
      sprintf (val, "%c%c", opcode[4], opcode[5]);
    }
  printf ("%s", one);
  if (atoi (val) == 10)
    {
      sprintf (inst, "%d", atoi (val));
    }
  else
    {
      sprintf (inst, "0%d", atoi (val));
    }
  if (two == ' ')
    {
      strcat (inst, zero);
    }
  else
    {
      strcat (inst, other);
    }
  if (strcmp (inst, "000") == 0)
    {
      //printf ("\t000%s\n", inst);
      fprintf (tar, "\t000%s\n", inst);
      return -1;
    }
  return 1;
}



void
process1 (char operand[])
{
  int add;
  char num[4];
  char *tok = strtok (operand, ",");
  tok = strtok (NULL, ">");
  if (tok != NULL)
    {
      if (operand[1] == 'S')
	{
	  char this[1];
	  sprintf (this, "%s", tok);
	  add = getsymadd (atoi (this));
	  sprintf (num, "%d", add);
	}
      if (operand[1] == 'C')
	{
	  sprintf (num, "%s", tok);
	  if (strlen (tok) == 2)
	    {
	      sprintf (num, "0%s", tok);
	    }
	  if (strlen (tok) == 1)
	    {
	      sprintf (num, "00%s", tok);
	    }
	  else
	    {
	      sprintf (num, "%s", tok);
	    }
	}
      strcat (inst, num);
      //printf ("\t%s\n", inst);
      fprintf (tar, "\t%s\n", inst);
    }
}


void
main (int argv, char *argc[])
{
  if (argv != 2)
    {
      printf ("Invalid number of arguments.\n");	
      exit(0);
    }
  else
    {
      makeinter (argc[1]);
      struct intermediate *line;
      line = head;
      tar = fopen ("target.asm", "w");
      if (!tar)
	{
	  printf ("Could not open target file");
	  exit (0);
	}
      else
	{
	  while (line->next != NULL)
	    {
	      if (!
		  ((line->opcode[1] == 'A' && line->opcode[2] == 'D')
		   || (line->opcode[1] == 'D' && line->opcode[2] == 'L'
		       && line->opcode[4] == '1')))
		{
		  fprintf (tar, " %d ", line->addr);
	          fflush(tar);
		  //printf ("\n%d", line->addr);
		  //fprintf (tar, "%d", line->addr);
		  if (line->opcode[1] == 'D' && line->opcode[2] == 'L'
		      && line->opcode[4] == '2')
		    {
		      char *token = strtok (line->operand, "<,C,,,>");
		      //printf ("\t%s", token);
		      fprintf (tar, "\t%s\n", token);
		    }
		  else
		    {
		      if (process (line->opcode) == 1)
			{
			  process1 (line->operand);
			}
		    }
		}
	      line = line->next;
	    }
	  fclose (tar);
	}
    }
  displaysymtab ();
  printf("\nTarget code stored in target.asm\n");	
}
