#ifndef __MYSEM_H__
#define __MYSEM_H__

#define SEM_MAX_NUM 1
#define SEM_ERMS 0600

#define MY_SEM_SERV_KEY 1357
#define MY_SEM_CLNT_KEY 2468

union semun{
int val;
struct semid_ds *buf;
unsigned short int* arry;
};

int creatSem(int key);
int openSem(int key);
int lockSem(int semid);
int unlockSem(int semid);
int closeSem(int semid);

#endif
