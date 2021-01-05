#include <stdio.h>
#include "operacje.h"
#include <sys/types.h>
#include <unistd.h>

int main()
{
    key_t klucz;
    int semID;
    int N = 4; //l. semaforów
  
    pid_t pidNr;

    if ( (klucz = ftok(".", 'A')) == -1 )
    {
        printf("Blad ftok (A)\n");
        exit(2);
    }

    semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
    pidNr = getpid();
    
    fflush(stdout);
    
    printf("Sekcja a1 procesu o PID=%d\n",pidNr);
    sleep(1);
    signalSemafor(semID, 0);
    signalSemafor(semID, 1);
    waitSemafor(semID, 2);
    printf("Sekcja a2 procesu o PID=%d\n",pidNr);
    sleep(2);
    printf("Sekcja a3 procesu o PID=%d\n",pidNr);
    sleep(3);
    fflush(stdout);
}

