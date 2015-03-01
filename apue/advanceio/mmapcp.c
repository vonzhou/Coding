#include "util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#define FILE_MODE (S_IRWXU | S_IRGRP | S_IROTH)

int main(int argc, char *argv[]){
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;
    if(argc != 3)
        err_quit("usage:%s <fromfile> <tofile>", argv[0]);
    if((fdin = open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s for reading.", argv[1]);
    if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("cannot open %s for writing.", argv[2]);
    if(fstat(fdin, &statbuf) < 0)
        err_sys("fstat error..");
    // set size of output file by lseek
    if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)
        err_sys("lseek error..");
    if(write(fdout, "", 1) != 1)
        err_sys("write error..");
    if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
        err_sys("mmap error for input file.");
    if((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)
        err_sys("mmap error for output file.");

    //// does the file copy
    memcpy(dst, src, statbuf.st_size);
    
    return 0;
}
