/*
 * 		proc.c ---- Description
 *------------------------------------------------------------
 * Date: April 8th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Monitoring the actions of linux kernel
 *------------------------------------------------------------
 */

#include<stdio.h>
#include<sys/time.h>

#define LB_SIZE 512 /* Buffer Size */


enum TYPE{STANDARD, SHORT, LONG};
FILE *current_proc_file; /* pointer to /proc file */
struct timeval now; /* current system time */
enum TYPE report_type; /* type of the type returned */
char report_name[16]; /* report name */
char *line_buffer; /* buffer when reading files */
int interval; /* interval of monitoring */
int duration; /* duration of monitoring */
int iteration;
char arg1, arg2;


/*
 * To get the type of CPU
 */
void get_cpu_type()
{
	FILE *in;
	char c[LB_SIZE];
	int i;

	in = fopen("/proc/cpuinfo", "r"); /* open /proc/cpuinfo */
	for(i = 0; i < 5; i++)
	{
		fgets(c, LB_SIZE, in); /* read cpu type line */
	}
	printf("------------------------------------------------------------\n");
	printf("| CPU type      | %s ", c+12); /* print info */
	printf("------------------------------------------------------------\n");

	fclose(in);
}

/*
 * To get kernel version
 */
void get_kernel_version()
{
	FILE *in;
	char c[30];

	in = fopen("/proc/version", "r"); /* open /proc/version */
	fgets(c, 30, in);
	printf("|Kernel Version |%s\n", c);
	printf("------------------------------------------------------------\n");

	fclose(in);
}


/*
 * To get running time of the system
 */
void get_running_time()
{
	FILE *in;
	int time = 0,
	    day = 0,
	    hour = 0,
	    minute = 0,
	    second = 0;

	in = fopen("/proc/uptime", "r");
	fscanf(in, "%d", &time);

	day = time / 86400;
	time = time % 86400;
	hour = time / 3600;
	time = time % 3600;
	minute = time / 60;
	time = time % 60;
	second = time;
	printf("-----------------------------------------------------------------------\n");
	printf("| System running time  | %d days  |  %d hours  | %d minutes  | %d seconds |\n", day, hour, minute, second);
	printf("-----------------------------------------------------------------------\n");

	fclose(in);
}
/*
 * To get CPU ticks of USER/KERNEL/IDLE states
 */
void get_cpu_ticks()
{
	FILE *in;
	char c[LB_SIZE];
	int user, nice, system, idle;

	in = fopen("/proc/stat", "r");
	fscanf(in, "%s %d %d %d %d", c, &user, &nice, &system, &idle);
    printf("==============================================\n");
    printf("CPU Ticks:\n");
    printf("==============================================\n");
	printf("--------------------------------------------------\n");
	printf("| User ticks     | %d            |\n", user);
	printf("--------------------------------------------------\n");
	printf("| System ticks   | %d             |\n", system);
	printf("--------------------------------------------------\n");
	printf("| Idle ticks     | %d            |\n", idle);
	printf("--------------------------------------------------\n");

	fclose(in);
}


/*
 * To get the times of disk requests
 */
void get_disk_requests()
{
	FILE *in;
	char c[LB_SIZE], disk[32];
	int read, write, nothing;

	in = fopen("/proc/diskstats", "r");


	while((fgets(c, LB_SIZE, in)) != NULL)
	{
		sscanf(c, "%d %d %s %d %d %d %d %d", &nothing, &nothing, disk, &read, &nothing, &nothing, &nothing, &write);

		if(disk[0] == 's' && disk[1] == 'd'){
            printf("==============================================\n");
			printf("Disk requests of [%s]:\n", disk);
            printf("==============================================\n");
            printf("----------------------------------------------\n");
			printf("| Read requests         |  %d times       |\n", read);
            printf("----------------------------------------------\n");
			printf("| Write requests        |  %d times        |\n", write);
            printf("----------------------------------------------\n");
			printf("| Total requests        |  %d times       |\n", read+write);
            printf("----------------------------------------------\n");
			break;
		}
	}
	fclose(in);
}


/*
 * To get context switches times
 */
void get_context_switches_times()
{
	FILE *in;
	char c[LB_SIZE], ctxt[10];
	int times;

	in = fopen("/proc/stat", "r");

	while((fgets(c, LB_SIZE, in)) != NULL)
	{
		sscanf(c, "%s %d", ctxt, &times);

		if(strcmp(ctxt, "ctxt") == 0)
		{
			printf("| Context switches times | %d           |\n", times);
            printf("----------------------------------------------\n");

		}
	}

	fclose(in);
}


/*
 * To get the number of threads started
 */
void get_threads_num()
{
	FILE *in;
	char c[LB_SIZE], processes[10];
	int num;

	in = fopen("/proc/stat", "r");

	while((fgets(c, LB_SIZE, in)) != NULL)
	{
		sscanf(c, "%s %d", processes, &num);

		if(strcmp(processes, "processes") == 0)
		{
			printf("| Number of threads      | %d              |\n", num);
            printf("----------------------------------------------\n");

		}
	}

	fclose(in);
}

void get_total_mem_size()
{
	FILE *in;
	char c[LB_SIZE], flag[20];
	int num;

	in = fopen("/proc/meminfo", "r");

	while((fgets(c, LB_SIZE, in)) != NULL)
	{
		sscanf(c, "%s %d", flag, &num);

		if(strcmp(flag, "MemTotal:") == 0)
		{
			printf("Total memory size: %d\n", num);
		}
	}
	fclose(in);
}

void get_available_mem_size()
{
	FILE *in;
	char c[LB_SIZE], flag[20];
	int num;

	in = fopen("/proc/meminfo", "r");

	while((fgets(c, LB_SIZE, in)) != NULL)
	{
		sscanf(c, "%s %d", flag, &num);

		if(strcmp(flag, "MemAvailable:") == 0)
		{
			printf("Available memory size: %d\n", num);
		}
	}
	fclose(in);
}


void get_load_averange()
{
	FILE *in;
	in = fopen("/proc/loadavg", "r");
	char c[LB_SIZE];
	float num1, num2, num3;

	fscanf(in, "%f %f %f", &num1, &num2, &num3);

	printf("Load Averange:\n");
	printf("\tAverange threads in 1 minute: %f\n", num1);
	printf("\tAverange threads in 5 minute: %f\n", num2);
	printf("\tAverange threads in 15 minute: %f\n", num3);

	fclose(in);
}

int main(int argc, char *argv[])
{
	if(argc == 1){
		printf("Usage:  [-a] Print Problem A\n\t[-b] Print Problem B\n\t[-c] Print Problem C\n\t[-d] Print Problem D\n");
	}
	else
	{
		sscanf(argv[1], "%c %c", &arg1, &arg2);
		if(arg1 != '-')
		{
			printf("Usage:  [-a] Print Problem A\n\t[-b] Print Problem B\n\t[-c] Print Problem C\n\t[-d] Print Problem D\n");
		}
		else
		{
			if(arg2 == 'a')
			{
				get_cpu_type();
				get_kernel_version();
			}
			else if(arg2 == 'b')
			{
				get_running_time();
			}
			else if(arg2 == 'c')
			{
				get_cpu_ticks();
				get_disk_requests();
                printf("==============================================\n");
				get_context_switches_times();
                printf("==============================================\n");
				get_threads_num();
			}
			else if(arg2 == 'd')
			{
				get_total_mem_size();
				get_available_mem_size();
				get_load_averange();
			}
			else
			{
				printf("Usage:  [-a] Print Problem A\n\t[-b] Print Problem B\n\t[-c] Print Problem C\n\t[-d] Print Problem D\n");
			}
		}
	}
}



/* TODO
Problem A:
* 1. CPU type
* 2. kernel version

Problem B:
* 1. duration from system starting till now

Problem C:
* 1. durations when CPU ticks on USER/KERNEL/IDLE states
* 2. times of disks requests
* 3. times of context switches
* 4. number of threads started

Problem D:
* 1. total memory size
* 2. available memory size
* 3. load averange of the system
*/

