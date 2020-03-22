#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>        /* For the sysinfo struct. */
#include <sys/statvfs.h>
#include <stdio.h>
#include <string.h>		/* for strncpy */
#include <unistd.h>		/* for close */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <sys/unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h> /* For the system() function. */
#include <gnu/libc-version.h> /* Get the GNU Libc version. */
#include <netdb.h>

#include "info.h"
#include "iface.h"

#define BUF 0x05

int main (int argc, char **argv) {

	char hostname[128];
	unsigned long  hdd_size;
	unsigned long  hdd_free;

	struct sysinfo info;
	sysinfo( &info );
	struct statvfs fsinfo;
	statvfs("/", &fsinfo);

	if (argv[1] == NULL) {
		menu();
	}

	/* Getting information about the routing table. */

	if (argc > 1 && strncmp (argv[1], "--arp", BUF) == 0) {
		// Print the routing table.
		printf ("This is the routing table.\n");
		char *arg[] = { "cat", "/proc/net/arp", NULL };
		execvp (arg[0], arg);
	}

	if (argc > 1 && strncmp (argv[1], "--system", BUF) == 0) {
		information();
		// Print the GNU Libc version.
		printf("GNU libc version: %s\n", gnu_get_libc_version());
		stuff();
	}

	if (argc > 1 && strncmp (argv[1], "--hostname", BUF) == 0) {
		// Get the system hostname.
		gethostname(hostname, sizeof hostname);
		printf("Hostname: %s\n", hostname);
	}

	if (argc > 1 && strncmp (argv[1], "--ip", BUF) == 0) {
		printf("Printing the IP addresse(s) on the machine.\n");
		printf("-----------------------------------------------------\n\n\n");
                iface();
		// Get the Internet facing IP address.
		//fflush(stdout);
		printf("Printing the TCP table.\n");
		printf("-----------------------------------------------------\n\n\n");
//		internetip();
		kernel("/proc/net/tcp", 2);
	}

	if (argc > 1 && strncmp (argv[1], "--disks", BUF) == 0) {
		// List the hard disks attached to the system.

		hdd_size = fsinfo.f_frsize * fsinfo.f_blocks;
		hdd_free = fsinfo.f_bsize * fsinfo.f_bfree;

		unsigned long capacity = hdd_size / 1000 / 1000 / 1000;
		unsigned long freesize = hdd_free / 1000 / 1000 / 1000;
		printf("The HDD size is %lu gigabytes, and has %lu gigabytes free.\n\n", capacity, freesize);
		execl("/bin/lsblk", "/bin/lsblk", "-d", "-S", "-n",NULL);
	}

	return 0;
}
