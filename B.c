#include <stdio.h>
#include "operacje.h"
#include <sys/types.h>
#include <unistd.h>

int main()
{
    key_t klucz;
    int semID;
    int N = 3;
    FILE *fp;
    pid_t pidNr;

    if ( (klucz = ftok(".", 'A')) == -1 )
    {
        printf("Blad ftok (B)\n");
        exit(2);
    }

    semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
    pidNr = getpid();

    fflush(stdout);

    waitSemafor(semID, 0, 0);
    printf("Sekcja b1 procesu o PID=%d\n",pidNr);
    sleep(4);
    printf("Sekcja b2 procesu o PID=%d\n",pidNr);
    sleep(5);
    signalSemafor(semID, 3);
    
    printf("Sekcja b3 procesu o PID=%d\n",pidNr);  
    sleep(6);
    fflush(stdout);

}

