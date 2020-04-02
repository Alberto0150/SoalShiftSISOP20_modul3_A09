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

//void printmatrix(int arr[4][5]){
//	int i, j;
//	int hasil[4][5];
//	for(i=0;i<4;i++){
//		for(j=0;j<5;j++){
//			printf("%d", hasil[i][j]);
//		}
//		printf("\n");
//	}
//}

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
    
//    printf("hasilnye cuks\n");
  //  printmatrix()
	//for(a = 0; a < 4; a++){
	//	for(b = 0; b < 5; b++){
	//		printf("%llu\t", final[a][b]);
	//	}
	//	print("\n");
	//}
    
    //shmdt(value);
    //shmctl(shmid, IPC_RMID, NULL);

}

