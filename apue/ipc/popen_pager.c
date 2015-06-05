#include "util.h"

#define PAGER "${PAGER:-more}" // environment var or default

int main(int argc, char *argv[]){
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if(argc != 2)
        err_quit("usage:a.out <pathname>");

    if((fpin = fopen(argv[1], "r")) == NULL)
        err_sys("cannot open %s", argv[1]);

    if((fpout = popen(PAGER, "w")) == NULL)
        err_sys("popen error");
    // copy the file to pager
    while(fgets(line, MAXLINE, fpin) != NULL){
        if(fputs(line, fpout) == EOF)
            err_sys("fputs error to pipe");
    }

    if(ferror(fpin))
        err_sys("fgets error");
    pclose(fpout);

    exit(0);
}

