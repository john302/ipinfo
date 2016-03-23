#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>        /* For the sysinfo struct. */
#include <stdio.h>
#include <string.h>		/* for strncpy */
#include <unistd.h>		/* for close */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <stdlib.h> /* For the system() function. */
#include <arpa/inet.h>

#include "info.h"

#define BUF 0x05

int main (int argc, char **argv)
{
	char hostname[128];
	struct utsname uname_pointer;

	if (argv[1] == NULL)
	{
		printf ("********************************************\n");
		printf ("*          Simple system information.      *\n");
		printf ("*                                          *\n");
		printf ("* IP info: --ip                            *\n");
		printf ("* Print ARP table: --arp                   *\n");
		printf ("* Print linux info: --linux                *\n");
		printf ("* Print sys info: --system                 *\n");
		printf ("********************************************\n");
		printf ("\nThe PID of this program was: %i\n", getpid ());
	}

	/* Getting information about the routing table. */

	if (argc > 1 && strncmp (argv[1], "--arp", BUF) == 0)
	{
		printf ("This is the routing table.\n");
		char *arg[] = { "cat", "/proc/net/arp", NULL };
		execvp (arg[0], arg);
	}

	if (argc > 1 && strncmp (argv[1], "--system", BUF) == 0)
	{
		information();
	}


	if (argc > 1 && strncmp (argv[1], "--hostname", BUF) == 0)
	{
		gethostname(hostname, sizeof hostname);
		printf("Hostname: %s\n", hostname);
	}

	if (argc > 1 && strncmp (argv[1], "--ip", BUF) == 0)
	{
		system("ip route get 8.8.8.8 | awk 'NR==1 {print $NF}'");
	}

	if (argc > 1 && strncmp (argv[1], "--linux", BUF) == 0)
	{
		/* Conversion constants. */
		const long minute = 60;
		const long hour = minute * 60;
		const long day = hour * 24;
		const double megabyte = 1024 * 1024;

		/* Obtain system statistics. */
		struct sysinfo si;
		sysinfo (&si);

		/* Summarize interesting values. */
		printf ("\n\nSystem uptime : %ld days, %ld:%02ld:%02ld\n", 
			si.uptime / day, (si.uptime % day) / hour, 
			(si.uptime % hour) / minute, si.uptime % minute);
		printf ("Total RAM   : %5.1f MB\n", si.totalram / megabyte);
		printf ("Free RAM   : %5.1f MB\n", si.freeram / megabyte);
		printf ("Number of running processes : %d\n", si.procs);

		uname(&uname_pointer);
		printf ("System name : %s \n"	\
			"Nodename    : %s \n"		\
			"Release     : %s \n"		\
			"Version     : %s \n"		\
			"Machine     : %s \n",
			uname_pointer.sysname,
			uname_pointer.nodename,
			uname_pointer.release,
			uname_pointer.version,
			uname_pointer.machine
		);
	}

	return 0;
}
