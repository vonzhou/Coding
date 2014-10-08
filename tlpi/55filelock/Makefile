
all:tflock

tflock:t_flock.o error_functions.o get_num.o curr_time.o
	gcc t_flock.o error_functions.o get_num.o curr_time.o -o tflock

t_flock.o:t_flock.c tlpi_hdr.h

error_functions.o:error_functions.c error_functions.h tlpi_hdr.h

get_num.o:get_num.c get_num.h tlpi_hdr.h

curr_time.o:curr_time.c curr_time.h tlpi_hdr.h


clean:
	rm -f *.o tflock
