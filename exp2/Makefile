lshell: lshell.h lshell.c prompt.c readcmd.c parse.c
	gcc lshell.c prompt.c readcmd.c parse.c -o lshell -D DEBUG -D READLINE_ON -I /usr/include -lreadline

clean:
	rm -f lshell
