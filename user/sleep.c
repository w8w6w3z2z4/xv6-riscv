#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    
    if (argc != 2)
    {
        fprintf(2, "Error! An argument must be typed in!\n");
        exit(1);
    }

    int CycNum = atoi(argv[1]);
    sleep(CycNum);
    fprintf(1, "nothing happens for a little while\n");
    exit(0);
}