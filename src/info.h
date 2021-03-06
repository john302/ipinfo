#ifndef INFO_H_
#define INFO_H_

#define BUF 0x05

/*
 * Function prototypes. Sexy... And unlike on the show `24', function
 * prototypes have nothing to to with hard disk sectors!
 */

//void kernel(const char,int);

/*
 *  @brief  /proc file opener
 *  @param  File  An output stream.
 *  @param  len  A string length.
 *  @return  none.
 *  @pre  @a len must be a non-NULL int.
 * I hope this little function is not offending anyone. it is the only
 * way I could think to have a single function that would be able to 
 * load the different files quickly and without fuss. And it works just
 * fine, and that is what matters in the end.
 */

struct _kern1 {
	char *File;
	int len;
	char Kyo[40];
} *kern1 = (struct _kern1 *) 0x80;

int information(void) {
	/* This code from:
	 * http://stackoverflow.com/questions/14345937/sysinfo-returns-incorrect-value-for-freeram-even-with-mem-unit
	 */
	/* Conversion constants. */
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	const double megabyte = 1024 * 1024;

	/* Obtain system statistics. */
	struct sysinfo si;
	sysinfo (&si);

	/* Summarize interesting values. */
	printf ("System uptime : %ld days, %ld:%02ld:%02ld\n", 
		si.uptime / day, (si.uptime % day) / hour, 
		(si.uptime % hour) / minute, si.uptime % minute);
	printf ("Total RAM   : %5.1f MB\n", si.totalram / megabyte);
	printf ("Free RAM   : %5.1f MB\n", si.freeram / megabyte);
	printf ("Number of running processes : %d\n", si.procs);

	/* Print the number of CPU cores available. */
	system("echo \"The computer has $(cat /proc/cpuinfo | grep CPU | wc -l) core(s).\"");
	return EXIT_SUCCESS;
}

void kernel(const char *File, int len)
{
	FILE *f;
	char Kyo[40];

	if (len > 10 || len < 2)
		return;

	f = fopen(File, "r");
	if(!f) {
		printf ("Sorry, I cannot open: %s.\n", File);
		printf("Please check your permissions with\n"		\
			"your supervisor. The feature may not\n"	\
			"be compiled and\\or enabled in your\n"		\
			"kernel version. Or a scsi device, eg,\n"	\
			"a USB drive may not be attached.\n");
		return;
	} else {
/* Based on sample code from:
 * www.koders.com/c/fid84CFEFBF311605F963CB04E0F84A2F52A8120F33.aspx
 * Specifically the section on parsing the /proc/version.
 */
		while (feof(f) != 1) {
			fgets(Kyo, len, f);
			if (strncmp(Kyo, "((", 1) == 0)
				printf ("\n-");
			if (strncmp(Kyo, "#", 1) == 0) {
				printf ("\nVersion: #");
			} else {
/*
 * This function is fast, owing to this i feel. especially with gcc 
 * 4.3.2 & glibc 2.5+. it is faster than using: printf (Kyo);
 */
				fprintf (stdout, "%s", Kyo);
			}
			fflush(stdout);
		}
	}
	fclose(f);
}

int stuff(void) {
	struct utsname uname_pointer;
	/* Conversion constants. */
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	const double megabyte = 1024 * 1024;

	/* Obtain system statistics. */
	struct sysinfo si;
	sysinfo (&si);

	/* Summarize interesting values. */
	printf ("System uptime : %ld days, %ld:%02ld:%02ld\n", 
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
	return EXIT_SUCCESS;
}

int menu(void) {
	printf ("********************************************\n");
	printf ("*          Simple system information.      *\n");
	printf ("*                                          *\n");
	printf ("* IP address info:                --ip     *\n");
	printf ("* Print ARP table:                --arp    *\n");
	printf ("* Print linux info:               --linux  *\n");
	printf ("* Print sys info:                 --system *\n");
	printf ("* List disk in the system:        --disks  *\n");
	printf ("*                                          *\n");
	printf ("********************************************\n");
	return EXIT_SUCCESS;
}

int internetip(void) {
	printf("Internet facing IP address.\n");
	execl("/usr/bin/curl", "/usr/bin/curl", "http://myexternalip.com/raw",NULL);
	return EXIT_SUCCESS;
};

#endif /* info.h */
