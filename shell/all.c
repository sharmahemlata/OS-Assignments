#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<unistd.h>


int lines;


void
getcount (char ch, char file[])
{
  int fd;
  fd = open (file, O_RDONLY);
  if (fd == -1)
    {
      printf ("Error in opening file\n");
    }
  else
    {
      int words = 0, chars = 0;
      char buf, prev = '\n';
      lines = 0;
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
	  prev = buf;
	}
      close (fd);
      switch (ch)
	{
	case 'a':
	  printf ("Lines:%d\tWords:%d\tCharacters:%d\n", lines, words, chars);
	  break;
	case 'c':
	  printf ("%d\n", chars);
	  break;
	case 'w':
	  printf ("%d\n", words);
	  break;
	case 'l':
	  printf ("%d\n", lines);
	  break;
	case 'b':
	  break;
	}
    }
}

void
printfile (int fd)
{
  char buf;
  while (read (fd, &buf, 1) == 1)
    {
      printf ("%c", buf);
    }
  close (fd);
}



void
typeline (char option[], char file[])
{
  int fd, nread;
  char buf;
  fd = open (file, O_RDONLY);
  if (fd == -1)
    {
      printf ("Error in opening file");
    }
  else
    {
      getcount ('b', file);
      if (strcmp (option, "a") == 0)
	{
	  printfile (fd);
//print the whole file;
	}
      else
	{
	  int num = atoi (option);
	  if (abs (num) >= lines)
	    {
	      printfile (fd);
//print the whole file
	    }
	  else if (num > 0)
	    {
	      off_t seek = lseek (fd, 0, SEEK_SET);
	      int j = 0;
	      while (j < num)
		{
		  nread = read (fd, &buf, 1);
		  printf ("%c", buf);
		  if (buf == '\n')
		    {
		      j++;
		    }
		}
	      close (fd);
	    }
	  else			//from peeche
	    {
	      off_t seek = lseek (fd, -2, SEEK_END);
	      int j = 0;
	      num = -1 * num;
	      while (j < num)
		{
		  nread = read (fd, &buf, 1);
		  if (buf == '\n')
		    {
		      j++;
		    }
		  seek = lseek (fd, -2, SEEK_CUR);
		}
	      seek = lseek (fd, 1, SEEK_CUR);
	      while (read (fd, &buf, 1) == 1)
		{
		  printf ("%c", buf);
		}
	      close (fd);
	    }
	}
    }
}

/*
void
typeline (char option[], char file[])
{
  //getcount ('b', file);
  int fd, nread;
  char buf;
  fd = open (file, O_RDONLY);
  if (fd == -1)
    {
      printf ("Error in opening file\n");
    }
  else
    {
	 getcount ('b', file);
      if (strcmp (option, "a") != 0)
	{
	  int num = atoi (option);
	  if (abs (num) >= lines)
	    {
	      goto here;
	    }
	  else if (num < 0)	//read file from bottom
	    {
	      int cnt = 0;
	      int j = lines + num;
	      while (cnt < j)
		{
		  nread = read (fd, &buf, 1);
		  if (buf == '\n')
		    {
		      cnt++;
		    }
		}
	      while ((read (fd, &buf, 1) == 1))
		{
		  printf ("%c", buf);
		}
	      close (fd);
	    }
	  else
	    {
	      int i = 0;
	      while (i < num)
		{
		  nread = read (fd, &buf, 1);
		  printf ("%c", buf);
		  if (buf == '\n')
		    {
		      i++;
		    }
		}
	      close (fd);
	    }
	}
      else
	{
	here:
	  while (read (fd, &buf, 1) == 1)
	    {
	      printf ("%c", buf);
	    }
	  close (fd);
	}
    }
}

*/


void
getfile (char ch, char dirname[])
{
  DIR *dir;
  dir = opendir (dirname);
  if (dir != NULL)
    {
      int cntentr = 0;
      struct dirent *entry;
      while ((entry = readdir (dir)) != NULL)
	{
	  if (ch == 'f')
	    {
	      printf ("%s\n", entry->d_name);
	    }
	  if (ch == 'i')
	    {
	      printf ("%lu\t%s\n", entry->d_fileno, entry->d_name);
	    }
	  cntentr++;
	}
      if (ch == 'n')
	{
	  printf ("No of entries:%d\n", cntentr);
	}
      closedir (dir);
    }
  else
    {
      printf ("Error in opening directory\n");
    }
}




void
main ()
{
  char input[80], token1[10], token2[10], token3[10], token4[10];
  int numtoks, invalid;
  while (1)
    {
      invalid = 0;
      printf ("hemashell$ ");
      fgets (input, sizeof (input), stdin);
      numtoks = sscanf (input, "%s%s%s%s", token1, token2, token3, token4);

      if (numtoks == -1)
	{
//do nothing
	}
      else if (numtoks == 1)
	{
	  if (strcmp ("quit", token1) == 0 || strcmp ("q", token1) == 0)
	    {
	      exit (0);
	    }
	  else
	    {
	      invalid = 1;
	    }
	}

      else if (numtoks == 2)
	{
	  if (strcmp ("count", token1) != 0)
	    {
	      invalid = 1;
	    }
	  else
	    {
	      getcount ('a', token2);
	    }
	}

      else if (numtoks == 3)
	{
	  if (!
	      (strcmp ("list", token1) == 0 || strcmp ("count", token1) == 0
	       || strcmp ("typeline", token1) == 0))
	    {
	      invalid = 1;
	    }

	  else
	    {
	      if (strcmp ("count", token1) == 0)
		{
		  if (!
		      (strcmp ("l", token2) == 0 || strcmp ("c", token2) == 0
		       || strcmp ("w", token2) == 0))
		    {
		      invalid = 1;
		    }
		  else
		    {
		      getcount (token2[0], token3);
		    }
		}


	      else if (strcmp ("list", token1) == 0)	//list commands
		{
		  if (!
		      (strcmp ("i", token2) == 0 || strcmp ("n", token2) == 0
		       || strcmp ("f", token2) == 0))
		    {
		      invalid = 1;
		    }
		  else
		    {
		      getfile (token2[0], token3);
		    }
		}

	      else		//typeline section
		{
		  typeline (token2, token3);
		}
	    }
	}


      else
	{
	  invalid = 1;
	}


      if (invalid == 1)		//system commands
	{
	  int pid = fork ();

	  if (pid == -1)
	    {
	      exit (-1);
	    }
	  else if (pid == 0)
	    {

	      if (numtoks == 1)
		{
		  execlp (token1, token1, NULL);
		  perror (token1);
		}

	      else if (numtoks == 2)
		{
		  execlp (token1, token1, token2, NULL);
		  perror (token1);
		}

	      else if (numtoks == 3)
		{
		  execlp (token1, token1, token2, token3, NULL);
		  perror (token1);
		}

	      else if (numtoks == 4)
		{
		  execlp (token1, token1, token2, token3, token4, NULL);
		  perror (token1);
		}

	      else
		{
		  perror (token1);
		}
	      exit (-1);
	    }
	  else
	    {
	      wait (NULL);
	    }
	}
    }
}
