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
	printf("CPU type: %s", c+13); /* print info */

	fclose(in);
}

/*
 * To get kernel version
 */
void get_kernel_version()
{
	FILE *in;
	char c[LB_SIZE];
	
	in = fopen("/proc/version", "r"); /* open /proc/version */
	fgets(c, LB_SIZE, in);
	printf("Kernel Version: %s", c);

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

	printf("System running time: %d days, %d hours, %d minutes, %d seconds.\n", day, hour, minute, second); 

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

	printf("User ticks: %d\n", user);
	printf("System ticks: %d\n", system);
	printf("Idle ticks: %d\n", idle);

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
			printf("Disk requests of [%s]:\n", disk);
			printf("\tRead requests: %d times.\n", read);
			printf("\tWrite requests: %d times.\n", write);
			printf("\tTotal requests: %d times.\n", read+write);
			break;
		}
	}
	fclose(in);
}

void get_context_switches_times()
{
	
}


int main(int argc, char *argv[])
{
	get_cpu_type();
	get_kernel_version();
	get_running_time();
	get_cpu_ticks();
	get_disk_requests();
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
3. times of context switches
4. times of threads starting

Problem D:
1. total memory size
2. available memory size
3. load averange of the system
*/

