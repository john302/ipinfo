#ifndef INFO_H_
#define INFO_H_

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
	printf ("* IP info:                        --ip     *\n");
	printf ("* Print ARP table:                --arp    *\n");
	printf ("* Print linux info:               --linux  *\n");
	printf ("* Print sys info:                 --system *\n");
	printf ("* List disk in the system:        --disks  *\n");
	printf ("*                                          *\n");
	printf ("********************************************\n");
	return EXIT_SUCCESS;
}

#endif /* info.h */
