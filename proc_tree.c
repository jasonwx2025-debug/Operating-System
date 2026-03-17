#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <depth N>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    int count = N;
    int status;
    int father = getpid();
    printf("Initial Parent PID: %d\n", father);
   
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);
    if (fd < 0) { perror("open failed"); exit(1); }

    while(N>0) {
        pid_t p = fork();
        if (p == 0) {
            printf("I am child at depth %d(PID:  %d), my father is%d\n", count - N + 1, getpid(), getppid());
            if (N>0){
                char buf[64];
                int len = sprintf(buf, "Depth %d: PID %d\n", N, getpid());
                write(fd, buf, len);
                N--;
            } else if (N==0){
                close(fd);
                exit(0);
            }
        } else {
            wait(NULL);
            if (getpid()==father){
                    printf("All children have exited. Parent exiting.\n");
                }
            close(fd);
            exit(0);
            
            }
        }
    close(fd);
    exit(0);
}