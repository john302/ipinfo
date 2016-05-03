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

int main (int argc, char **argv) {

	char hostname[128];

	if (argv[1] == NULL) {
		menu();
	}

	/* Getting information about the routing table. */

	if (argc > 1 && strncmp (argv[1], "--arp", BUF) == 0) {
		printf ("This is the routing table.\n");
		char *arg[] = { "cat", "/proc/net/arp", NULL };
		execvp (arg[0], arg);
	}

	if (argc > 1 && strncmp (argv[1], "--system", BUF) == 0) {
		information();
	}

	if (argc > 1 && strncmp (argv[1], "--hostname", BUF) == 0) {
		gethostname(hostname, sizeof hostname);
		printf("Hostname: %s\n", hostname);
	}

	if (argc > 1 && strncmp (argv[1], "--ip", BUF) == 0) {
		system("ip route get 8.8.8.8 | awk 'NR==1 {print $NF}'");
	}

	if (argc > 1 && strncmp (argv[1], "--disks", BUF) == 0) {
		system("lsblk -d");
	}

	if (argc > 1 && strncmp (argv[1], "--linux", BUF) == 0) {
		stuff();
	}

	return 0;
}
