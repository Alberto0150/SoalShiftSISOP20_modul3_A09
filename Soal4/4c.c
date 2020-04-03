#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
	// We use two pipes 
	// First pipe to send input string from parent 
	// Second pipe to send concatenated string from child 

	int fd1[2]; // Used to store two ends of first pipe 
	int fd2[2]; // Used to store two ends of second pipe 
	pid_t p ; 
		if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Gagal" ); 
		return 1; 
	} 
	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Gagal" ); 
		return 1; 
	} 
	p=fork();
	
	if (p < 0) 
	{ 
		fprintf(stderr, "fork Gagal" ); 
		return 1; 
	} 
	else if(p == 0){
		 // input from pipe1
    dup2(fd1[0], 0);
    // output to pipe2
    dup2(fd2[1], 1);
    // close fds
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    // exec
  	 char *args1[] = {"ls", NULL};
    execv("/bin/ls", args1);
	}
	else{
	 // input from pipe2
    dup2(fd2[0], 0);
    // close fds
    close(fd2[0]);
    close(fd2[1]);
    // exec
    char *args2[] = {"wc", "-l", NULL};
    execv("/usr/bin/wc", args2);
  }

}
