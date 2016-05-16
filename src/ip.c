#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>        /* For the sysinfo struct. */
#include <stdio.h>
#include <string.h>		/* for strncpy */
#include <unistd.h>		/* for close */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h> /* For the system() function. */
#include <gnu/libc-version.h> /* Get the GNU Libc version. */

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
		printf("GNU libc version: %s\n", gnu_get_libc_version());
	}

	if (argc > 1 && strncmp (argv[1], "--hostname", BUF) == 0) {
		gethostname(hostname, sizeof hostname);
		printf("Hostname: %s\n", hostname);
	}

	if (argc > 1 && strncmp (argv[1], "--ip", BUF) == 0) {
		printf("Internet facing IP address.\n");
		execl("/usr/bin/curl", "/usr/bin/curl", "ipinfo.io/ip",NULL);
		printf("LAN IP address.\n");
		system("ip route get 8.8.8.8 | awk 'NR==1 {print $NF}'");

	}

	if (argc > 1 && strncmp (argv[1], "--disks", BUF) == 0) {
		execl("/bin/lsblk", "/bin/lsblk", "-d",NULL);
	}

	if (argc > 1 && strncmp (argv[1], "--linux", BUF) == 0) {
		stuff();
	}

	return 0;
}
