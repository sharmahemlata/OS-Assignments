#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

void four(char line[], int l_no);



char *reg[] = { "AREG", "BREG", "CREG", "DREG" };
char *cc[] = { "LT", "LE", "EQ", "GT", "GE", "ANY" };
char *opcode[] =
  { "STOP", "ADD", "SUB", "MULTI", "DIV", "MOVER", "MOVEM", "COMP", "BC",
"READ", "PRINT" };
char *dir[] = {"LTORG", "ORIGIN", "EQU","START","END"};
char *dl[] = { "DC", "DS" };


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
checkreg (char tok[], int l_no)
{
  int flag = 0, i = 0,ismnem=0;
  char *exp = strtok (tok, " ");
  if (exp != NULL)
    {
      char *comreg[] = { "AREG,", "BREG,", "CREG,", "DREG," };
      while (comreg[i] != NULL)
	{
	  if (strcmp (comreg[i], exp) == 0)
	    {
	      flag = 1;
	      ismnem=1;	
	      break;
	    }
	  i++;
	}
      if (flag == 0)
	{
	  i = 0;
	  while (reg[i] != NULL)
	    {
	      if (strcmp (reg[i], exp) == 0)
		{
		  ismnem = 1;
		  printf ("Error:Comma expected after register %d", l_no);
		  break;
		}
	      i++;
	    }
	}
    }

  if (ismnem==0)
    {
      //printf ("Error:Invalid mnemonic instruction %d", l_no);
      return 0;
    }
  return 1;
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

int
ifupper (char tok[])
{
  int i = 0;
  while (tok[i] != NULL && !isdigit (tok[i]))
    {
      if (isupper (tok[i]))
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

int isreg(char tok[])
{
int i=0;
while(reg[i]!=NULL)
{
if(strcmp(tok,reg[i])==0)
	{
	return 1;
	}
}
return 0;
}

void
one (char line[], int l_no)
{
  char *tok = strtok (line, "\n");
  if (!((strcmp (tok, dir[0]) == 0) || (strcmp (tok, opcode[0]) == 0)||(strcmp (tok, dir[4]) == 0)))
    {
      printf ("Error:Invalid mnemonic instruction-> %d\n", l_no);
    }
}

void
three (char line[], int l_no)
{
  //printf("\nInstruction:%s\n",line);	
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
  if (isopcode (token1))
    {
      if(strcmp(token1,opcode[8]) == 0 && ! iscc(token2))
	{
	printf("Error:Invalid mnemonic instruction %d",l_no);
	}
	
      if (checkreg (token2, l_no))
	{
	  if (isany (token3))
	    {
	      printf ("\nError:Invald symbolic name %d\n", l_no);
	    }
	}
    }
  else
    {
      if (isany (token1))
	{
	  printf ("\nError:Invalid Symbolic name %d\n", l_no);
	}
      else
	{
	  if(!isany(token2))
	{
	printf("\nError:Invalid Mnemonic instruction %d",l_no);
	}
	  char equ[3] = "EQU";
	  if (isopcode (token2))
	    {
	      if (isany (token3))
		{
		  printf ("\nError:Invalid Symbolic name %d\n", l_no);
		}
	    }			//check if second token is mnemonic
	  else if (isdl (token2))
	    {
	      if (!isnum (token3))
		{
		  printf ("\nError:Invalid mnemonic instruction  %d\n",
			  l_no);
		}
	    }			//check if second token is DC/DS
	  else if (strcmp (equ, token2) == 0)
	    {
	      if (!isnum (token3))
		{
		  printf ("\nError:Address sepcifier expected after EQU %d\n",
			  l_no);
		}
	    }			//check if second token is EQU
	  else
	    {
	    	
	    }			//do nothing  since it is neither
	}
    }
}



void
two (char line[], int l_no)
{
  //printf("\ninput:%s\n",line);	
  char token[20];
  char *token1 = strtok (line, " ");
  strcpy (token, token1);
  if (token != NULL)
    {
      token1 = strtok (NULL, "\n");
    }
  if (isopcode (token))
    {
	//printf("operand:%s\t isnum:%d\tisupper:%d\tisopcode:%d",token1,isnum(token1),ifupper(token1),isopcode(token1));
      if ((isopcode(token1))||(!isnum (token1))|| (!ifupper (token1)))	//token1 is not a const or memmory op
	{
	  printf
	    ("\nError:Invalid mnemonic instruction%d\n",
	     l_no);
	}
    }

  else if (strcmp (dir[1], token) == 0 || strcmp(dir[3],token)==0)
    {
      if (!isnum (token1) || !ifupper (token1))
	{
	  printf ("\nError:Invalid mnemonic instruction %d\n",
		  l_no);
	}
    }	
  else
    {
      if (isany (token))
	{
	  printf ("\nError:Invalid Symbolic Name %d\n", l_no);
	}
      else if(isnum(token))
	{
	printf("\nError:Label cannot be a constant %d\n",l_no);
	}	
      else
	{
	  if (!(strcmp(token1,opcode[0])==0))
	    {
	      printf ("\nError:Invalid mnemonic instruction %d\n", l_no);
	    }
	}
    }
}

void
main (int argv, char *argc[])
{
  if (argv != 2)
    {
      printf ("Invalid number of arguments");
      exit (0);
    }
  else
    {
      FILE *fp = fopen (argc[1], "r");
      if (fp == NULL)
	{
	  printf ("Error");
	  exit (0);
	}
      else
	{
	  char line[79], line1[79];
	  int l_no = 1, toks;
	  while (!feof (fp))
	    {
	      fgets (line, sizeof (line), fp);
	      strcpy (line1, line);
	      char *token = strtok (line, " ");
	      toks = 0;
	      while (token != NULL)
		{
		  token = strtok (NULL, " ");
		  toks++;
		}
//		printf("\ntoks:%d",toks);
	      switch (toks)
		{
		case 0:
		  printf ("Error:nothing on line %d", l_no);
		  break;
		case 1:
		  one(line,l_no);
		  break;
		case 2:
		  two(line1,l_no);
		  break;
		case 3:
		  three (line1, l_no);
		  break;
		case 4:
		  four(line1,l_no);
		  break;
		default:
		  printf ("Error on line %d", l_no);
		}
	      l_no++;
	    }



	}
    }
}


void four(char line[], int l_no)
{
//  printf("\t\tInstruction :%s\n",line);	
  char token1[20], token2[20], token3[20],token4[20];
  char *token = strtok (line, " ");
  strcpy (token1, token);
  if (token != NULL)
    {
      token = strtok (NULL, " ");
    }
  strcpy (token2, token);
  if (token != NULL)
    {
      token = strtok (NULL, " ");
    }


  strcpy (token3, token);


  if(token!=NULL)
  {
  //printf("\nsdfsmmmqma");
  token = strtok(NULL,"\n");	
  }	


  strcpy(token4,token);	


 // printf("\t%s\t%s\t%s\t%s\t",token1,token2,token3,token4);
  if(isany(token1))
	{
	printf("\nError:Invalid symbolic name:%d\n",l_no);
	}
  else
      {
        //printf("first is not anything");
        if(isany(token2))
        {
        //printf("second is a token");
        if(strcmp(token2,opcode[8])==0 && !iscc(token3))
        {
        printf("\nError:Invalid mnemonic instruction %d\n",l_no);
        }
        else
        {
        if(!isreg(token3))
        {
        printf("\nError:Invalid mnemonic instruction %d\n",l_no);
        }        
        }
        }                       
        }
	
  if(!isopcode(token2))
	{
	printf("\nError:Invalid Mnemonic instruction:%d\n",l_no);
	} 
  if(checkreg(token3,l_no))
	{
	if(isany(token4))
	{
	printf("\nError:Invalid Symbolic name:%d\n",l_no);
	}
	}
}
