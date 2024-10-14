#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int count = 0;
int ignoreCase = 0;
int duplicate = 0;
char buf[512];
char lc = '\0';
int aln=0;
void
copyArray (char *source, char *dest)
{
  int i;
  for (i = 0; source[i] != '\0'; i++)
    {
      dest[i] = source[i];
    }
  dest[i] = '\0';
}

int
compareArrayCase (char *a, char *b)
{
  int i;
  for (i = 0; a[i] != '\0'; i++)
    {

    }
  int j;
  for (j = 0; b[j] != '\0'; j++)
    {

    }
  if (i == j)
    {
      for (i = 0; a[i] != '\0'; i++)
	{
	  if ((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122))
	    {
	      if ((b[i] >= 65 && b[i] <= 90) || (b[i] >= 97 && b[i] <= 122))
		{
		  if (a[i] - b[i] == 0 || a[i] - b[i] == 32
		      || a[i] - b[i] == -32)
		    {
		      continue;
		    }
		  else
		    {
		      return -1;
		    }
		}
	      else
		{
		  return -1;
		}
	    }
	  else
	    {
	      if (a[i] == b[i])
		{
		  continue;
		}
	      else
		{
		  return -1;
		}
	    }
	}
    }
  else
    {
      return -1;
    }
  return 0;
}

void
unique (int fd)
{
  int c = 1;
  int i, n;
  int index = 0;
  int emp=0;
  char *prev_line = (char *) malloc (1024);
  char *curr_line = (char *) malloc (1024);
  int batch=0;
  int sc=1;
  while ((n = read (fd, buf, sizeof (buf))) > 0)
    {
    emp=1;
      for (i = 0; i < n; i++)
	{
	lc = buf[i];
	if(batch==0 && i==0){
	if(buf[i]=='\n'){
	while(i<n && buf[i+1]=='\n'){
	i++;
	sc=sc+1;
	}
	if(!(duplicate==1 && sc<2)){
	if(count==1){
	printf(1,"%d \n",sc);
	}
	else{
	printf(1,"\n");
	}
	}
	continue;
	}
	}
	  if (buf[i] == '\n')
	    {
	    int nc = 0;
	    while(i<n && buf[i+1]=='\n'){
	    i++;
	    nc = nc+1;
	    }
	    if(nc>0){
	    	  if (!
		      (ignoreCase == 1
		       && compareArrayCase (prev_line, curr_line) == 0)
		      && strcmp (prev_line, curr_line) != 0)
		    {
		      if (count == 1)
			{
				  if(prev_line[0]!='\0'){
				  if(!(duplicate==1 && c<2)){
			  printf (1, "%d %s\n", c, prev_line);}}
			  if(curr_line[0]!='\0'){
			  if((duplicate==0)){
			  printf (1, "1 %s\n", curr_line);}}
			  if(!(duplicate==1 && nc<2)){
			  printf(1,"%d\n",nc,"");
			  }
			}
		      else
			{

				  if(prev_line[0]!='\0'){
				  if(!(duplicate==1 && c<2)){
			  printf (1, "%s\n",prev_line);}}
			  if(curr_line[0]!='\0'){
			  if((duplicate==0)){
			  printf (1, "%s\n",curr_line);}}
			  if(!(duplicate==1 && nc<2)){
			  printf(1,"\n");
			  }
			}
		    }
		  else
		    {
		      if (count == 1)
			{
			if(!(duplicate==1 && c+1<2)){
			  printf (1, "%d %s\n", c + 1, prev_line);}
			  if(duplicate==0){
			  printf(1,"%d\n",nc,"");}

			}
		      else
			{
			if(!(duplicate==1 && c+1<2)){
			  printf (1, "s\n", prev_line);}
			  if(duplicate==0){
			  printf(1,"\n");}
			}

		    }


	    index=0;
	    prev_line[0]='\0';
	    curr_line[0]='\0';
	    aln=1;
	    c=1;
	    continue;
	    }
aln=0;
	      if (!
		  (ignoreCase == 1
		   && compareArrayCase (prev_line, curr_line) == 0)
		  && strcmp (prev_line, curr_line) != 0)
		{
		  if (*prev_line != 0 && prev_line[0]!='\0')
		    {
		      if (count == 1 )
			{
			if(!(duplicate==1 && c<2)){
			  printf (1, "%d %s\n", c, prev_line);
			  }
			}
		      else
			{
			  if(!(duplicate==1 && c<2)){
			  printf (1, "%s\n", prev_line);
			  }
			}

		    }
		  copyArray (curr_line, prev_line);
		  curr_line[0]='\0';
		  c = 1;
		}
	      else
		{
		  c = c + 1;
		}
	      index = 0;
	    }
	  else
	    {
	      curr_line[index] = buf[i];

	      curr_line[index + 1] = '\0';
	      index++;
	    }
	}
	batch++;
    }
    if(i>0){
    if(lc=='\n'){
    if(aln==0){
    		  if (!
		      (ignoreCase == 1
		       && compareArrayCase (prev_line, curr_line) == 0)
		      && strcmp (prev_line, curr_line) != 0)
		    {
		      if (count == 1)
			{
			if(prev_line[0]!='\0'){
			if(!(duplicate==1 && c<2)){
			  printf (1, "%d %s\n", c, prev_line);}
			  }
			  if(curr_line[0]!='\0'){
			  if(duplicate==0){
			  printf (1, "1 %s\n", curr_line);}}
			}
		      else
			{
			  	if(prev_line[0]!='\0'){
			if(!(duplicate==1 && c<2)){
			  printf (1, "%s\n", prev_line);}
			  }
			  if(curr_line[0]!='\0'){
			  if(duplicate==0){
			  printf (1, "%s\n",curr_line);}}
			}
		    }
		  else
		    {
		      if (count == 1)
			{
			if(!(duplicate==1 && c<2)){
			  printf (1, "%d %s\n", c, prev_line);}
			}
		      else
			{
			  if(!(duplicate==1 && c<2)){
			  printf (1, "%s\n", prev_line);}
			}

		    }
		    }
    }
    else{
    		  if (!
		      (ignoreCase == 1
		       && compareArrayCase (prev_line, curr_line) == 0)
		      && strcmp (prev_line, curr_line) != 0)
		    {
		      if (count == 1)
			{
			if(prev_line[0]!='\0'){
			if(!(duplicate==1 && c<2)){
			  printf (1, "%d %s\n", c, prev_line);
			  }
			  }
			  if(duplicate==0){
			  printf (1, "1 %s\n", curr_line);
			  }
			}
		      else
			{
			  if(prev_line[0]!='\0'){
			if(!(duplicate==1 && c<2)){
			  printf (1, "%s\n", prev_line);
			  }
			  }
			  if(duplicate==0){
			  printf (1, "%s\n", curr_line);
			  }
			}
		    }
		  else
		    {
		      if (count == 1)
			{
			if(!(duplicate==1 && c+1<2)){
			  printf (1, "%d %s\n", c+1, prev_line);
			  }
			}
		      else
			{
			  if(!(duplicate==1 && c+1<2)){
			  printf (1, "%s\n", prev_line);
			  }
			}

		    }

    }

    }

    if(emp==0){
    printf(1,"wrong usage!\n");
    exit();
    }

}

int
main (int argc, char *argv[])
{
  int fd = 0, i;


  for (i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "-c") == 0)
	{
	  count = 1;
	  continue;
	}
      if (strcmp (argv[i], "-i") == 0)
	{
	  ignoreCase = 1;
	  continue;
	}
      if (strcmp (argv[i], "-d") == 0)
	{
	  duplicate = 1;
	  continue;
	}
      if ((fd = open (argv[i], 0)) < 0)
	{
	  printf (1, "uniq: cannot open %s\n", argv[i]);
	  exit ();
	}
    }
  unique (fd);
  close (fd);
  exit ();
}
