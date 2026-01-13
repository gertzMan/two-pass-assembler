PROGNAME = assembler
FLAGS = -pedantic -Wall -ansi
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(PROGNAME) : $(OBJS)
	gcc -o $(PROGNAME) $(OBJS) 
	
-include depends

%.o : %.c
	gcc -g -c $(FLAGS) $<
	gcc -g -c $(FLAGS) -MM $< >> depends 
		
clean:
	rm -f *.o
	rm -f *.d
	rm -f depends
	rm -f *.ob
	rm -f *.ext
	rm -f *.ent
	rm -f *.txt
