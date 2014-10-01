all:  suspend1 suspend2 sigsyn exit_status
suspend1: error.o  pr_mask.o sigsuspend1.o
	gcc -o suspend1 error.o  pr_mask.o sigsuspend1.o
suspend2: error.o  pr_mask.o sigsuspend2.o
	gcc -o suspend2 error.o  pr_mask.o sigsuspend2.o
sigsyn: error.o  sigsyn.o
	gcc -o sigsyn error.o  sigsyn.o
exit_status:error.o exit_status.o
	gcc -o exit_status error.o pr_exit.o exit_status.o

error.o : error.c util.h
	gcc -c error.c
pr_mask.o : pr_mask.c util.h
	gcc -c pr_mask.c
mask.o : mask.c util.h
	gcc -c mask.c
sigsuspend1.o:sigsuspend1.c util.h
	gcc -c sigsuspend1.c

sigsuspend2.o:sigsuspend2.c util.h
	gcc -c sigsuspend2.c

sigsyn.o:sigsyn.c util.h
	gcc -c sigsyn.c

pr_exit.o:pr_exit.c util.h
	gcc -c pr_exit.c
exit_status.o:exit_status.c util.h
	gcc -c exit_status.c



clean :
	-rm test_siglongjmp *.o
