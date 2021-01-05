#include <stdio.h>
#include "operacje.h"
#include <sys/types.h>
#include <unistd.h>

int main()
{
    key_t klucz;
    int semID;
    int N = 4;
    
    pid_t pidNr;

    if ( (klucz = ftok(".", 'A')) == -1 )
    {
        printf("Blad ftok (C)\n");
        exit(2);
    }

    semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
    pidNr = getpid();
    fflush(stdout);

    waitSemafor(semID, 1, 0);
    printf("Sekcja c1 procesu o PID=%d\n",pidNr);
    sleep(7);
    signalSemafor(semID, 2);
    printf("Sekcja c2 procesu o PID=%d\n",pidNr);
    sleep(8);
    waitSemafor(semID, 3, 0);
    printf("Sekcja c3 procesu o PID=%d\n",pidNr);
    sleep(9);
    fflush(stdout);
    
}
