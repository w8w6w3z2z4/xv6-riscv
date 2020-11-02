#include "kernel/types.h"
#include "user/user.h"
int main() {
    int p2c[2]; //pipe: parent to child
    int c2p[2]; //pipe: child to parent
    pipe(p2c);
    pipe(c2p);
    char buf[] = {'b'}; // the passed byte
    int len = sizeof(buf);

    //create child process
    int pid = fork();
    if (pid < 0)
    {
        fprintf(2, "Create child process error!");
        exit(1);
    }else if (pid == 0)
    {
        close(p2c[1]);
        close(c2p[0]);
        if (read(p2c[0], buf, len) != len)//child process read
        {
            fprintf(2,"read error!");
            exit(1);
        }else
        {
            fprintf(1, "%d: received ping\n", getpid());
        }
        close(p2c[0]);
        
        write(c2p[1], buf, sizeof(buf)); //child process write
        close(c2p[1]);
        
        exit(0);
    }else
    {
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], buf, len); //parent process write
        close(p2c[1]);

        if (read(c2p[0], buf, len) != len)//parent process read
        {
            fprintf(2,"parent process read error!");
            exit(1);
        }else
        {
            fprintf(1, "%d: received pong\n", pid);
        }
        close(c2p[0]);
        wait(0);
        exit(0);
    }
    
    
}