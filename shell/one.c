#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>


int fd, words, lines, chars, gotchar;

void
getcounts ()
{
  char buf, prev = '\0';
  words = lines = chars = gotchar = 0;
  while (read (fd, &buf, 1) == 1)
    {
      if (buf == '\n')
	{
	  lines++;
	}
      if ((prev == ' ' || prev == '\t' || prev == '\n')
	  && (buf != ' ' && buf != '\t' && buf != '\n'))
	{
	  words++;
	}
      chars++;
      if (buf != '\t' || buf != '\n' || buf != ' ')
	{
	  gotchar = 1;
	}
      prev = buf;
    }


 if (words > 0)
   {
                          words += 1;
                        }
                      if (gotchar == 1 && words == 0)
                        {
                          words = 1;
 }
}

void
main ()
{
  char instruction[80], instruction1[80];
  char input1[10], input2[10], input3[10];
  int numtoks, i, invalid = 0;
  while (1)
    {
      invalid = 0;
      printf ("myshell$ ");
      fgets (instruction, sizeof (instruction), stdin);
      strcpy (instruction1, instruction);
      char *tok = strtok (instruction, " ");
      i = 0;
      numtoks = 0;
      while (tok != NULL)
	{
//numtoks++;
//strcpy(token[i],tok);
	  tok = strtok (NULL, " ");
	  numtoks++;
//i++;
	}
//printf("toks:%d",numtoks);
      if (numtoks == 1)
	{
	  sscanf (instruction1, "%s", input1);
	  if (strcmp (input1, "quit") == 0)
	    {
	      exit (0);
	    }
	  else if (strcmp (input1, "\t") == 0)
	    {
//do nothing
	    }
	  else
	    {
	      invalid = 1;
	    }
	}
      else if (numtoks==2)
	{
	sscanf (instruction1, "%s%s", input1, input2);
	if (strcmp (input1, "count") != 0)
            {
              invalid = 1;
            }
	else
	{
	      fd = open (input2, O_RDONLY);
              if (fd == -1)
                {
                  printf ("Invalid file name\n");
                }
              else
                {
		getcounts();
		printf("lines:%d   words:%d   characters:%d\n",lines,words,chars);
		}
	}
	}
      else if (numtoks == 3)
	{
	  sscanf (instruction1, "%s%s%s", input1, input2, input3);
	  if (strcmp (input1, "count") != 0)
	    {
	      invalid = 1;
	    }
	  else
	    if (!
		(strcmp (input2, "c") == 0 || strcmp (input2, "w") == 0
		 || strcmp (input2, "l") == 0))
	    {
	      invalid = 1;
	    }
	  else
	    {
	      fd = open (input3, O_RDONLY);
	      if (fd == -1)
		{
		  printf ("Invalid file name\n");
		}
	      else
		{
		  getcounts ();
		  char ch = input2[0];
		  switch (ch)
		    {
		    case 'c':
		      printf ("%d\n", chars);
		      break;
		    case 'w':
		      printf ("%d\n", words);
		      break;
		    case 'l':
		      printf ("%d\n", lines);
		      break;
		    }
		}
	    }
	}
      else
	{
	  invalid = 1;
	}
      if (invalid == 1)
	{
	  printf ("Invalid statement\n");
	}
    }
}
