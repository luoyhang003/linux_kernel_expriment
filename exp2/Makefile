lshell: lshell.h lshell.c prompt.c readcmd.c
	gcc lshell.c prompt.c readcmd.c -o lshell -D DEBUG -D READLINE_ON -I /usr/include -lreadline

clean:
	rm -f lshell
