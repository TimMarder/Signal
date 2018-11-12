
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

void sighandler( int sig ) {

    if (sig == SIGINT) {

        int file = open("log.txt", O_CREAT | O_WRONLY);
        if (file < 0) {
            printf("Appending to file failed!\n");
            exit( 1 );
        }
        char error[] = "Program stopped due to SIGINT";
        write( file , error, sizeof(error) );
        close( file );
        exit ( 0 );

    }

    else if (sig == SIGUSR1) {

        printf("Parent pid: %d\n", getppid() );
        sleep(1);

    }

}

int main() {

    signal( SIGUSR1, sighandler );
    signal( SIGINT, sighandler );
    while( 1 ) {
        printf("Current PID: %d\n", getpid() );
        sleep( 1 );
    }
    return 0;

}
