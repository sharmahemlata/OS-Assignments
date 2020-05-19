#include<stdio.h>
#include<stdlib.h>

int errflag = 0, loadf = 0;

int mem[1000], cc[6], regs[4], startaddr, lastaddr, pc, starting,lastone,gotstart=0;

FILE *fptr;


void
printfile ()
{
 int i;
 for(i=startaddr;i<=lastone;i++)
	{
	 printf("\n%d\t%d",i,mem[i]);
	}
	
}

int
runprog ()
{
  int i;
  for (i = 0; i < 4; i++)
    {
      regs[i] = 0;
    }
  for (i = 0; i < 5; i++)
    {
      cc[i] = 0;
    }
  cc[5] = 1;
  char address[3], instruction[7];
  char line[79];
  int addr, inst, opcode, reg, operand, comp,temp;
  while (1)
    {
      inst = mem[pc];
      opcode = inst / 10000;
      operand = inst % 1000;
      reg = (inst % 10000) / 1000;
      switch (opcode)
	{
	case 0:
	  if (operand == 0)
	    {
	      pc = starting;
	      gotstart=1;
	      return;
	    }
	  break;
	case 1:
	  regs[reg - 1] += mem[operand];
	  break;
	case 2:
	  regs[reg - 1] -= mem[operand];
	  break;
	case 3:
	  regs[reg - 1] *= mem[operand];
	  break;
	case 4:
	  regs[reg - 1] = mem[operand];
	  break;
	case 5:
	  mem[operand] = regs[reg - 1];
	  break;
	case 6:
	  if (regs[reg - 1] < mem[operand])
	    {
	      cc[0] = 1;
	      cc[1] = 1;
	    }
	  if (regs[reg - 1] == mem[operand])
	    {
	      cc[2] = 1;
	      cc[1] = 1;
	      cc[4] = 1;
	    }
	  if (regs[reg - 1] > mem[operand])
	    {
	      cc[3] = 1;
	      cc[4] = 1;
	    }
	  break;
	case 7:
	  if (cc[reg - 1] == 1)
	    {
	      pc = operand-1;
	      for (i = 0; i < 5; i++)
            	{
              	cc[i] = 0;
            	}
	    }
            cc[5]=1;
	    break;
		
	  break;
	case 8:
	  regs[reg - 1] /= mem[operand];
	  break;
	case 9:
	  printf ("Enter a number:");
	  scanf ("%d", &mem[operand]);
	  break;
	case 10:
	  printf ("%d", mem[operand]);
	  break;
	case 11:
		temp = regs[reg-1];
		regs[reg-1]=mem[operand];
		mem[operand] = temp;
		break;
	case 12:
		regs[reg-1]+=1;	
		break;
	case 13:
		regs[reg-1]-=1;
	case 14:
		mem[operand]+=1;
		break;
	case 15:
		mem[operand]-=1;
		break;
	case 16:
		mem[operand]+=regs[reg-1];
		break;
	case 17:
		mem[operand]-=regs[reg-1];
		break;
	case 18:
		mem[operand]*=regs[reg-1];
		break;
	case 19:
		mem[operand]/=regs[reg-1];
		break;
	case 20:
		printf("\n%d",regs[reg-1]);
		break;
	case 21:
		printf("\nEnter a number:");		
		scanf("%d",&regs[reg-1]);
		break;
	case 22:
		regs[reg-1]=0;
		break;
	case 23:
		regs[reg-1]=1;
		break;
	}	
	if(pc==lastone+1 && gotstart==0)
	{
	while(1)
	{
	printf('\0');
	}
	}	
      pc++;
  
    }
  pc = starting;
  gotstart=0;	
  return;
}



void
loadprog ()
{
  char address[3], instruction[7];
  char line[79];
  int addr,inst, opcode, reg, operand, l_no = 0, found = 0;
  gotstart=0;
  while (fgets (line, sizeof (line), fptr) != NULL)
    {
      sscanf (line, "%s %s", address, instruction);
      addr = atoi (address);
      inst = atoi (instruction);
      l_no++;
      if (addr == -1)
	{
	  found = 1;
	  lastaddr = inst;
	  if (startaddr != lastaddr)
	    {
	      printf
		("\nRelocation required.Execution address is not equal to start address");
	      errflag = 1;
	      break;
	    }
	  else
	    {
	      pc = inst;
	      starting = inst;	
	    }
	}
      else
	{
	  mem[addr] = inst;
	  lastone = addr;
	  if (l_no == 1)
	    {
	      startaddr = addr;
	    }
	  loadf = 1;
	  opcode = inst / 10000;
	  operand = inst % 1000;
	  reg = (inst % 10000) / 1000;
//printf("\n%d\t%d\topcode:%d\treg:%d\toperand:%d\t",addr,inst,opcode,reg,operand);
	  switch (opcode)
	    {
	    case 0:
	      if (reg != 0)
		{
		  printf ("\nError:Invalid instruction %d", l_no);
		  errflag = 1;
		}	
	      break;
	    case 1:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	    case 6:
	    case 8:
	    case 11:
	    case 12:
	    case 13:
	    case 16:
	    case 17:
	    case 18:
	    case 19:
            case 20:
	    case 21:
	    case 22:
	    case 23:	
	      if (reg < 1 || reg > 4)
		{
		  printf ("\nError:Invalid register code %d", l_no);
		  errflag = 1;
		}
	      break;
	    case 7:
	      if (reg < 1 || reg > 6)
		{
		  printf ("\nError:Invalid condition code %d", l_no);
		  errflag = 1;
		}
	      break;
	    case 9:
	      if (reg != 0)
		{
		  printf ("\nError:Invalid Read instruction %d", l_no);
		  errflag = 1;
		}
	      break;
	    case 10:
	      if (reg != 0)
		{
		  printf ("\nError:Invalid Print instruction.%d", l_no);
		  errflag = 1;
		}
	      break;	
	    case 14:
	    case 15:
		if (reg != 0)
                {
                  printf ("\nError:invalid  instruction.%d", l_no);
                  errflag = 1;
                }
		break;
	    default:
	      printf ("\nError:Invalid opcode %d", l_no);
	      errflag = 1;
	    }
	}
    }
  if (found == 0)
    {
      errflag = 1;
      printf ("Error:Program missing execution start address");
    }
  if (errflag == 0)
    {
      loadf = 1;
      printf ("Program loaded successfully!");
    }
}

void
main ()
{
  int choice;
  char fname[30];
  do
    {
      printf ("\n1)Load file.\n2)Print file.\n3)Run.\n0)Exit.\n");
      scanf ("%d", &choice);
      switch (choice)
	{
	case 0:
	  exit (0);

	case 1:
	  loadf = 0;
	  printf ("\nEnter file name:");
	  scanf ("%s", fname);
	  fptr = fopen (fname, "r");
	  if (fptr == NULL)
	    {
	      printf ("\nError in opening file.");
	    }
	  else
	    {
	      loadf = 1;
	      loadprog ();
	    }
	  break;

	case 2:
	  if (loadf == 0)
	    {
	      printf
		("\nYou have not loaded a file.Please load a file first");
	    }
	  else
	    {
	      printfile ();
	    }
	  break;
	case 3:
	  if (loadf == 0 || errflag == 1)
	    {
	      printf
		("\nCannot run! You have either not loaded a file or the loaded file has errors");
	    }
	  else
	    {
	      gotstart=0;
	      runprog ();
	    }
	  break;
	default:
	  printf ("\nInvalid input");
	}
    }
  while (choice != 0);
}
