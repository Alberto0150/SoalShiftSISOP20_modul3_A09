#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

char ofile[1000];

void *buatfile (void* arg)
{
	char ofile[1000];
	strcpy(nfile,ofile);
	struct stat typestat;
	if(stat(nfile,&typestat)!=-1)
	{
		if(S_ISDIR(typestat.st_mode) !=0)
		{
		}
		else if(S_ISREG(typestat.st_mode) != 0)
		{
		}
	}
}


int main(int argc, char *argv[])
{
pthread_t thread[];	
int count=0;
int i;


struct dirent *tujuan;
DIR *dir = opendir("/home/alberto/praktikum3/soal3");
if(dir==NULL)
{
	return 0;
}

if(strcmp(argv[1],"-f")==0)
{
	for(i=1;i<argc-1;i++)
	{
		strcpy(nfile,argv[i+1]);
		pthread_create(&thread[count],NULL,&buatfile,NULL)
		count++;
	}
	
	
}
else if (strcmp(argv[1],"-d")==0)
{
	while((tujuan = readdir(dir))!=NULL)
	{
		char locpath[100];
		struct stat typestat;
		
		if(strcmp(tujuan->d_name,"."==0||strcm(tujuan->d_name,"..")==0)
		{
			continue;
		}
		else
		{
			
		}
		strcpy(nfile,sumber);
		strcat(nfile,tujuan->d_name);
		pthread_create(&thread[count],NULL,buatfile,NULL);
		count++;
	}	
}
else 
{
	
}
for(i=0;i<count;i++)
{
	pthread_join(thread[i],NULL);
}
return 0;
}
