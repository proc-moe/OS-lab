thread_stack_size: thread_stack_size.o
	gcc thread_stack_size.o -o thread_stack_size.out

thread_stack_size.o: stack-probe.c
	gcc -c stack-probe.c -o thread_stack_size.o

clean:
	rm *.o 
	rm *.out