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

