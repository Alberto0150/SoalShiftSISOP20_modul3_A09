#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>

#define maks 1000
int a = 1;
char ofile[1000];

void *buatfile (void* arg)
{
	char nfile[1000];
	int ch;
	strcpy(nfile,ofile);
	struct stat typestat;
	if(stat(nfile,&typestat)!=-1)
	{
		if(S_ISDIR(typestat.st_mode) !=0)
		{
			a=1;
		}
		else if(S_ISREG(typestat.st_mode) != 0)
		{
			struct stat st;
			char eks[1000];
			char lokbar[1000];
			char *pch;	
			int index=0,i;
			
			getcwd(lokbar,1000);
			strcat(lokbar,"/");
			pch =strrchr(nfile '.');
			if(pch==NULL)
			{
				FILE *fp1, *fp2;
				strcat(lokbar,"Unknown");

				mkdir(lokbar,0777);
				strcat(lokbar,"/");
				
				
				pch=strrchr(nfile,'/');
				char temp[1000];
				strcpy(temp,pch);
				memmoce(&temp[index],&temp[index+1],strlen(temp)-index);
				strcat(lokbar,temp);
				
				
				fp1=fopen(nfile,"rb");
				fp2=fopen(lokbar,"wb");
				
				if(!fp1)
				{
					fclose(fp2);
				}
				if(!fp2)
				{
					fclose(fp2);
				}
				while ((ch=fgetc(fp1))!=EOF)
				{
					fputc(ch,fp2);
				}
				fclose(fp1);
				fclose(fp2);
				a=1;
				
			}
			else
			{
				strcpy(eks,pch);
				memmove(&eks[index],&eks[index+1],strlen(eks)-index);
				for (i=0;i<strlen(eks);i++)
				{
					if(eks[i]>='A'&&eks[i]<='Z')
					{
						eks[i]=eks[i]+32;
					}
				}
				strcat(lokbar,eks);
				if(strcmp(eks,"*")==0)
				{
					getcwd(lokbar,1000);
					strcat(lokbar,"/unknown/");
					mkdir(lokbar,0777);
					FILE *fp1 , *fp2;
					index=0;
					pch=strrchr(nfile,'/');
					char temp[1000];
					strcpy(temp,pch);
					memmove(&temp[index],&temp[index+1],strlen(temp)-index);

					strcat(lokbar,temp);
					fp1=fopen(nfile,"rb");
					fp2=fopen(lokbar,"wb"):
					if(!fp1)
					{
						fclose(fp2);
					}
					if(!fp2)
					{
						fclose(fp2);
					}
					while ((ch=fgetc(fp1))!=EOF)
					{
						fputc(ch,fp2);
					}
					fclose(fp1);
					fclose(fp2);
					a=1;
					// hmmmm
					DIR *dir=opendir(lokbar);
					if(dir)
					{
						closedir(dir);
						FILE *fp1, *fp2;
						char namafile[1000];
						pch=strrchr(nfile,'/');
						strcpy(namafile,pch);
						memmove(&namafile[index],&namafile[index+1],strlen(namafile)-index);
						strcat(lokbar,"/");
						strcat(lokbar,namafile);

						fp1=fopen(nfile,"rb");
						fp2=fopen(lokbar,"wb");
						if(!fp1)
						{
							fclose(fp2);
						}
						if(!fp2)
						{
							fclose(fp2);
						}
						while ((ch=fgetc(fp1))!=EOF)
						{
							fputc(ch,fp2);
						}
						fclose(fp1);
						fclose(fp2);
						a=1;
					}
					else if (ENOENT==errno)
					{
						mkdir(lokbar,0777);
						FILE *fp1, *fp2;
						char namafile[1000];
						pch=strrchr(namafile,pch);
						memmove(&namafile[index],&namafile[index+1],strlen(namafile)-index);
						strcat(lokbar,"/");
						strcat(lokbar,namafile);
						
						fp1=fopen(nfile,"rb");
						fp2=fopen(lokbar,"wb");
						if(!fp1)
						{
							fclose(fp2);
						}
						if(!fp2)
						{
							fclose(fp2);
						}
						while ((ch=fgetc(fp1))!=EOF)
						{
							fputc(ch,fp2);
						}
						fclose(fp1);
						fclose(fp2);
						a=1;
					}	
				}
			}
		else
		{
			a=1;
			return 0;
		}
	}
}


int main(int argc, char *argv[])
{
pthread_t thread[];	
int count=0;
int i;



/////////////////////////////////////////////////////////// declare

if(strcmp(argv[1],"-f")==0) // udh
{
	for(i=1;i<argc-1;i++)
	{
		strcpy(nfile,argv[i+1]);
		pthread_create(&thread[count],NULL,&buatfile,NULL)
		count++;
	}
	
	
}
else if (strcmp(argv[1],"-d")==0) // udh
{
	struct dirent *tujuan;
	DIR *dir = opendir(argv[2]);
	if(dir==NULL)
	{
		return 0;
	}

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
			int size;
			strcpy(locpath,argv[2]);
			strcat(locpath,"/");
			
			size=sizeof(tujuan->d_name)+2;
			char tmp[size];
			strcpy(tmp,tujuan->d_name);
			int flag=0;
			
			for(i=0;i<strlen(tmp);i++)
			{
				if(tmp[i]==32)
				{
					flag++;
				}
			}
			if(flag>0)
			{
				snprintf(tmp,1024,"%s", tujuan->d_name);
			}
			else
			{
				snprintf(tmp,1024,"%s",tujuan->d_name);
			}
			strcat(locpath,tmp);
			strcpy(ofile,locpath);
			pthread_create(&thread[count],NULL,buatfile,NULL);
			count++;
		}
		
	}	
}
else // untuk terakhir
{
	if(strcmp(argv[1],"*")==0)
	{
		char temp[1000];
		getcwd(temp,sizeof(temp));

		struct dirent *tujuan;
		DIR *dir = opendir(argv[2]);
		if(dir==NULL)
		{
			return 0;
		}
		while((tujuan = readdir(dir))!=NULL)
		{
			char locpath[1000];
			struct stat typestat;
			
			if(strcmp(tujuan->d_name,"."==0||strcm(tujuan->d_name,"..")==0)
			{
				continue;
			}
			else
			{
				int size;
				char temp[1000];
				getcwd(temp,sizeof(temp));
				strcpy(locpath,temp);
				strcpy(locpath,argv[2]);
				strcat(locpath,"/");
				
				size=sizeof(tujuan->d_name)+2;
				char tmp[size];
				strcpy(tmp,tujuan->d_name);
				int flag=0;
				
				for(i=0;i<strlen(tmp);i++)
				{
					if(tmp[i]==32)
					{
						flag++;
					}
				}
				if(flag>0)
				{
					snprintf(tmp,1024,"%s", tujuan->d_name);
				}
				else
				{
					snprintf(tmp,1024,"%s",tujuan->d_name);
				}
				strcat(locpath,tmp);
				strcpy(ofile,locpath);
				pthread_create(&thread[count],NULL,buatfile,NULL);
				count++;
					
			}
			
		}
		
	}
	else
	{
		a=0;
		pthread_create(&(thread[0]), NULL, buatfile, (void *)argv[1]);
		return 0;
	}
}
}
for(i=0;i<count;i++)
{
	pthread_join(thread[i],NULL);
}
return 0;
}
