# SoalShiftSISOP20_modul3_A09
#### ADAM ABELARD GARIBALDI 05111840000125
#### ALBERTO SANJAYA 05111840000150
---

## Soal 4
>source code
>**[4a.c](https://github.com/Alberto0150/SoalShiftSISOP20_modul3_A09/blob/master/Soal4/4a.c)** ,
> **[4b.c](https://github.com/Alberto0150/SoalShiftSISOP20_modul3_A09/blob/master/Soal4/4b.c)** ,
> **[4c.c](https://github.com/Alberto0150/SoalShiftSISOP20_modul3_A09/blob/master/Soal4/4c.c)**

pada soal 4a diminta membuat program yang berisikan perkalian matrix dimana matrix pertama berukuran 4x2 dan matrix kedua 2x5. isi matrix adalah angka dengan range 1-20 (tidak perlu dibuat filter angka). lalu tampilkan hasil perkalian tersebut
```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
 
int main()
{
    key_t key = 1234;
    int *value;
    int multiply[4][5];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    int c, d, k;
    int sum = 0;
    int m1[4][2] = {{1, 2},
                    {2, 3},
                    {3, 4},
                    {4, 5}};
    int m2[2][5] = {{1, 2, 2, 4, 3},
                      {5, 1, 2, 3, 5}};



    for (c = 0; c < 4; c++) {
      for (d = 0; d < 5; d++) {
        for (k = 0; k < 2; k++) {
          sum = sum + m1[c][k]*m2[k][d];
        }
 
        multiply[c][d] = sum;
        sum = 0;
      }
    }
 
    printf("Hasil Perkalian:\n");
 
    for (c = 0; c < 4; c++) {
      for (d = 0; d < 5; d++){
      *value = multiply[c][d];
      sleep(1);
      printf("hasilnye %d \n", *value);
      }
    }
    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
```

pada soal 4b diminta membuat program yang menampilkan penjumlahan faktorial dari hasil perkalian matrix di soal 4a
```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

void *facplusplus(void *);

void *facplusplus(void *arg){
	int i, j, x, f, final[4][5], k, a, b;
	key_t key = 1234;
    int **value;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
    for(i=0;i<4;i++){
    	for(j=0;j<5;j++){
    		x=value[i][j];
    		f=0;
    		for(k=1;k<x;k++){
    			f=f+k;
			}
		}
	}
	
	for(a = 0; a < 4; a++){
		for(b = 0; b < 5; b++){
			printf("%d\t", value[a][b]);
		}
		printf("\n");
	}
}

void main()
{
    key_t key = 1234;
    int *value;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    int i, j, x, f, k, final[4][5], a, b;
    
    pthread_t tid;
    
    pthread_create(&tid, NULL, facplusplus, NULL);
    pthread_join(tid, NULL);
}
```
pada soal 4c diminta menampilkan jumlah file dalam direktori saat ini
```
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
```
