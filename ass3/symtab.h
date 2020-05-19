#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char *reg[] = { "AREG,", "BREG,", "CREG,", "DREG," };
char *cc[] = { "LT", "LE", "EQ", "GT", "GE", "ANY" };

char *opcode[] =
  { "STOP", "ADD", "SUB", "MULT", "DIV", "MOVER", "MOVEM", "COMP", "BC",
  "READ", "PRINT"
};
char *dir[] = { "LTORG", "ORIGIN", "EQU", "START", "END" };
char *dl[] = { "DC", "DS" };

int loc_count = 0;
int j=0;
int  locarr[25];

void adderror (char e1[], int l_no);

int isdir(char tok[])
{
 int i = 0;
  while (dir[i] != NULL)
    {
      if (strcmp (dir[i], tok) == 0)
        {
          return 1;
        }
      i++;
    }
  return 0;

}



int iscc(char tok[])
{
 int i = 0;
  while (cc[i] != NULL)
    {
      if (strcmp (cc[i], tok) == 0)
        {
          return 1;
        }
      i++;
    }
  return 0;

}


int
isdl (char tok[])
{
  int i = 0;
  while (dl[i] != NULL)
    {
      if (strcmp (dl[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  return 0;
}



struct symtab
{
  char symbol[10];
  int addr,used;
  struct symtab *next;
};

struct error
{
  char err[70];
  int l_no;
  struct error *next;
};

struct symtab *symhead = NULL;
struct error *errhead = NULL;

void getresult()
{
FILE *f = fopen ("symbol.txt", "w");
      if (f == NULL)
        {
          printf ("Error in opening file!");
	  exit(0);
        }

char e[40];
struct symtab *s = symhead;
//printf("\n\t\tSymbol table:\n");

while(s->next!=NULL)
{
fwrite(s,sizeof(struct symtab),1,f);	
if(s->used==0)
{
sprintf(e,"Warning: Symbol %s defined but not used",s->symbol);
adderror(e,-1);
}	
s = s->next;
}

//printf("\n%s\t",s->symbol);
if(s->addr==-1)
{
//printf("X\n");
sprintf(e,"Symbol %s is used but not defined",s->symbol);
adderror(e,-1);  
}               
if(s->used==0)
{
sprintf(e,"Warning: Symbol %s defined but not used",s->symbol);
adderror(e,-1);
}
fwrite(s,sizeof(struct symtab),1,f); 
fclose(f);
}

int
isreg (char tok[])
{
  int i = 0;
  while (reg[i] != NULL)
    {
      if (strcmp (reg[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  return 0;
}


int
isopcode (char tok[])
{
  int i = 0;
  while (opcode[i] != NULL)
    {
      if (strcmp (tok, opcode[i]) == 0)
	{
	  return 1;
	}
      i++;
    }
  return 0;
}



int
isany (char tok[])
{
  int i = 0;
  while (reg[i] != NULL)
    {
      if (strcmp (reg[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  i = 0;
  while (cc[i] != NULL)
    {
      if (strcmp (cc[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  i = 0;
  while (opcode[i] != NULL)
    {
      if (strcmp (opcode[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  i = 0;
  while (dir[i] != NULL)
    {
      if (strcmp (dir[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  i = 0;
  while (dl[i] != NULL)
    {
      if (strcmp (dl[i], tok) == 0)
	{
	  return 1;
	}
      i++;
    }
  return 0;
}

int
isnum (char tok[])
{
  int i = 0;
  while (tok[i])
    {
      if (isdigit (tok[i]))
	{
	  i++;
	}
      else
	{
	  return 0;
	}
    }
  return 1;
}

void
adderror (char e1[], int l_no)
{
  struct error *e;
  e = (struct error*)malloc(sizeof(struct error));
  strcpy(e->err,e1);
  e->l_no = l_no;	
	
  e->next = NULL;
  if (errhead == NULL)
    {
      errhead = e;
      
    }
  else
    {
      struct error *p;
      p = errhead;
      while (p->next != NULL)
	{
	  p = p->next;
	}
      p->next = e;
    }
}

void
syminoper (char sym[], int l_no)
{
  int flag = 0;
  struct symtab *s1;
  s1 = (struct symtab *)malloc(sizeof(struct symtab));
  strcpy(s1->symbol,sym);
  s1->addr = -1;
  s1->next = NULL;
  s1->used = 1;
  if (symhead==NULL)
    {
      symhead = s1;
    }
  else
    {
      struct symtab *p;
      p = symhead;
      while (p->next != NULL)
	{
	  if (strcmp (p->symbol, sym) == 0)
	    {
	      p->used = 1;	
	      flag = 1;
	      break;
	    }
	  p = p->next;
	}
	if (strcmp (p->symbol, sym) == 0 && flag==0)
            {
	      p->used = 1;
              flag = 1;
            }

      if (flag == 0)
	{/*
	  struct symtab *s;
	  sprintf (s->symbol, "%s", sym);
	  s->addr = NULL;
	  s->next = NULL;*/
	/*  p = symhead;
	  while (p->next != NULL)
	    {
	      p = p->next;
	    }*/
	  p->next = s1;
	}
    }
//printf("Symhead:%s",symhead);
}



void
syminlabel (char sym[], int l_no)
{
  //printf("\t\tsymbol in label:%s",sym);
  int flag = 0;
  char e[40];
  struct symtab *symb;
  symb = (struct symtab*)malloc(sizeof(struct symtab)); 
  //sprintf (symb->symbol, "%s", sym);
  strcpy(symb->symbol,sym);
  symb->addr = loc_count;
  symb->next = NULL;
  symb->used = 0;

  if (symhead == NULL)
    { 	
      symhead = symb;
      printf("symhead not pointing to null anymore");	
    }
  else
    {
      int pos = 0;
      struct symtab *p;
      p = symhead;
      while (p->next != NULL)
	{
	  pos++;
	  if (strcmp (p->symbol,symb->symbol) == 0)
	    {
	      if (p->addr != -1)
		{
		  sprintf(e,"Redeclaration of symbol %s",p->symbol);
		  adderror (e, l_no);
		}
	      else
		{
		  p->addr = loc_count;
		}
	      flag = 1;
	      break;
	    }
	  p = p->next;
	}
	if (strcmp (p->symbol,symb->symbol) == 0 && flag==0)
            {
              if (p->addr == -1)
                {
		  p->addr = loc_count;
		  flag = 1;
		  
                  //sprintf(e,"Redeclaration of symbol %s",p->symbol);
                  //adderror (e, l_no);
                }
            }

      if (flag == 0)
	{
	/*  p = symhead;
	  while (p->next != NULL)
	    {
	      p = p->next;
	    }*/
	  p->next = symb;
	}
    }
}


int
one1 (char line[], int l_no)
{
  char *token = strtok(line,"\n");
  if (strcmp (token, dir[4]) == 0)
    {
      //printf("got end %d",loc_count);
      return 1;
    }
  loc_count++;
  return 0;
}

void
two1 (char line[], int l_no)
{
  char token1[20];
  char *token2 = strtok (line, " ");
  strcpy (token1, token2);
  if (token2 != NULL)
    {
      token2 = strtok (NULL, "\n");
    }
  if (strcmp (token1, dir[3]) == 0)
    {
      if (!isnum (token2))
	{
	  printf ("\nError:Expected address specifier after START %d", l_no);
	}
      else
	{
	  sscanf (token2, "%d", &loc_count);
	  return;
	}
    }
  //loc_count++;
  if (isany (token1))
    {
      //loc_count++;
      if (isany (token2))
	{
	  adderror ("operand cannot be a reserved keyword", l_no);
	}
      if (!isnum (token2) && !isany (token2))
	{
	  syminoper (token2, l_no);
	}
    }

  else if (!isany (token1) || isany (token2))
    {
      //loc_count++;
      syminlabel (token1, l_no);
    }

  else if (strcmp (dir[2], token1) == 0)
    {
      if (!isnum (token2))
	{
	  adderror ("Address specifier expected after ORIGIN", l_no);
	}
    }
  else
    {
//do nothing
    }
if(isany(token1) || isany(token2))
{
loc_count++;
}
}






void
four1 (char line[], int l_no)
{
  //printf("\nfour token inst:%s\n",line);	
  char label[10], mnemonic[10], reg[10], memop[10];
  char *token = strtok (line, " ");
  strcpy (label, token);
  if (token != NULL)
    {
      token = strtok (NULL, " ");
    }
  strcpy (mnemonic, token);
  if (token != NULL)
    {
      token = strtok (NULL, " ");
    }
  strcpy (reg, token);
  if (token != NULL)
    {
      token = strtok (NULL, "\n");
    }
  strcpy (memop, token);

  if (isopcode (mnemonic))
    {
      //loc_count++;
      if (!isreg (reg))
	{
	  adderror ("Not a register", l_no);
	}
      if (isany (label))
	{
	  adderror ("label cannot be a reserved keyword", l_no);
	}
      else if (isnum (label))
	{
	  adderror ("label cannot be a numeric value", l_no);
	}
      else
	{
	  //syminlabel (label, l_no);
	}
      if (isany (memop))
	{
	  adderror ("Memory operand cannot be a reserved keyword", l_no);
	}
      else if (isnum (memop))
	{
	  adderror ("Memory operand cannot be a numeric value", l_no);
	}
      else
	{
	  syminoper (memop, l_no);
	}
    syminlabel(label,l_no); 
    }
if(isopcode(mnemonic))
{
loc_count++;
}
}

void
three1 (char line[], int l_no)
{
  //printf("three token inst");
  char token1[20], token2[20], token3[20];
  char *token = strtok (line, " ");	
  strcpy (token1, token);
  if (token != NULL)
    {
      token = strtok (NULL, " ");
    }
  strcpy (token2, token);
  if (token != NULL)
    {
      token = strtok (NULL, "\n");
    }
  strcpy (token3, token);

  //printf("token1:%s\ttoken2:%s\ttoken3:%s\t\t\tisany:%d   isreg(second token):%d\n",token1,token2,token3,isany(token1),isreg(token2));
  if (isany (token1))
    {
      //loc_count++;
      if (!isreg (token2))
	{
	  adderror ("Invalid register operand", l_no);
	}
      syminoper (token3, l_no);
    }
  else
    {
      if (isany (token1))
	{
	  adderror ("Symbol name cannot be a reserved key word", l_no);
	}
      else
	{
	  if (isopcode (token2))
	    {
	      if (isnum (token3) || isany (token3))
		{
		  adderror ("Invalid memory operand", l_no);
		}
	      else
		{
		  syminoper (token3, l_no);
		}
	    }
	  else if (strcmp (token2, dir[2]) == 0)
	    {
	      //loc_count++;
	    }
	 /* else if (isdl (token2))
	    {
	      if (strcmp (token2, dl[0]) == 0)
		{
		  //loc_count++;
		}
	      else
		{
		  int i;
		  sscanf (token3, "%d", &i);
		  //loc_count += i;
		}
	    }*/
	  else if (isopcode (token2))
	    {
	      if (isany (token3) || isnum (token3))
		{
		  adderror ("Invalid memory operand", l_no);
		}
	      else
		{
		  syminoper (token3, l_no);
		}
	    }
	  else
	    {

	    }
	  syminlabel (token1, l_no);
	}

    }





if(isopcode(token1) || isopcode(token2)|| strcmp(token2,dl[0])==0)
{
loc_count++;
}
if(strcmp(token2,dl[1])==0)
{
loc_count+= atoi(token3);
}
}



void
makesymbol(char file[])
{
      FILE *fp = fopen (file, "r");
      if (fp == NULL)
	{
	  printf ("Error in opening file!");
	  exit (0);
	}
     else{

	  char line[80], line1[80];
	  int toks,a;
	  int l_no=1;
	  while (!feof(fp))
	    {
	      fgets (line, sizeof (line), fp);
	      sprintf (line1, "%s", line);
	      toks = 0;
	      toks = 0;
	      char *token = strtok (line, " ");
	      locarr[j]=loc_count;	
	      while (token != NULL)
		{

		  toks++;
		  token = strtok (NULL, " ");
		}
	      switch (toks)
		{
		case 1:
		  a = one1 (line, l_no);
		  break;
		case 2:
		  two1 (line1, l_no);
		  break;
		case 3:
		  three1 (line1, l_no);
		  break;
		case 4:
		  four1 (line1, l_no);
		  break;
		default:
		  printf ("Erro:Invalid assembly language instruction %d",
			  l_no);
		}
	      j++;	
	      l_no++;
	    }
    		}
	getresult();

 
}
