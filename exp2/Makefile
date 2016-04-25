lshell: lshell.h lshell.c prompt.c readcmd.c parse.c buildin.c read_command.c
	gcc lshell.c prompt.c readcmd.c parse.c buildin.c read_command.c -o lshell -D READLINE_ON -D DEBUG -I /usr/include -ltermcap -lreadline

clean:
	rm -f lshell
