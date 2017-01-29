/********************************************************************
* Description: System information utility.
* Author: John Cartwright <johncartwright302@dodo.com.au>
* Created at: Mon Jan 16 10:02:12 AEDT 2017
* Computer: localhost.localdomain
* System: Linux 4.8.15 on x86_64
*
********************************************************************/

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
#include <pwd.h>
#include <sys/types.h>
#include <ifaddrs.h>

#include "info.h"

#define BUF 0x05

int main (int argc, char **argv) {

	char hostname[128];
	struct passwd *passwd;
	passwd = getpwuid ( getuid());

	char* myarg1 = argv[1];

	if (!argc || !myarg1) {
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
	}

	if (argc > 1 && strncmp (argv[1], "--hostname", BUF) == 0) {
		// Get the system hostname.
		gethostname(hostname, sizeof hostname);
		printf("Hostname: %s\n", hostname);
	}

	if (argc > 1 && strncmp (argv[1], "--ip", BUF) == 0) {
		// Get the LAN IP address.
		printf("LAN IP address.\n");
		system("hostname -I | awk '{print $1}'");

		// Get the Internet facing IP address.
		internetip();
	}

	if (argc > 1 && strncmp (argv[1], "--disks", BUF) == 0) {

		// List the hard disks attached to the system.
		execl("/bin/lsblk", "/bin/lsblk", "-d",NULL);
	}

	if (argc > 1 && strncmp (argv[1], "--linux", BUF) == 0) {
		// Print system information.
		stuff();

		fprintf(stdout, "\nLogin Name is: %s\n", passwd->pw_name);
		fprintf(stdout, "Login shell is: %s\n", passwd->pw_shell);
		fprintf(stdout, "User home is: %s\n", passwd->pw_dir);
		fprintf(stdout, "User information: %s\n", passwd->pw_gecos);
		printf("\nThe system has %lu CPU cores.\n", sysconf(_SC_NPROCESSORS_ONLN));
		printf("The system has %lu pages of physical memory.\n", sysconf(_SC_PHYS_PAGES));
		printf("The system has %lu pages of available physical memory.\n", sysconf(_SC_AVPHYS_PAGES));
	}

	if (argc > 1 && strncmp (argv[1], "--motherboard", BUF) == 0) {
		printf("\t\tMotherboard & BIOS information.\n");
		printf("--BIOS date: ");
		kernel("/sys/class/dmi/id/bios_date", 4);
		printf("--BIOS vendor: ");
		kernel("/sys/class/dmi/id/bios_vendor", 4);
		printf("--Motherboard name: ");
		kernel("/sys/class/dmi/id/board_name", 4);
		printf("--Motherboard vendor: ");
		kernel("/sys/class/dmi/id/board_vendor", 4);
	}

	return 0;
}
