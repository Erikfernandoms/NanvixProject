/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This file is part of Nanvix.
 * 
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/* Software versioning. */
#define VERSION_MAJOR 1 /* Major version. */
#define VERSION_MINOR 0 /* Minor version. */

/*
 * Program arguments.
 */
static struct
{
	char *dirname; /* Directory name. */
} args = { NULL };

int dir_empty(char *path)
{
	struct dirent *ent;
	int ret = 1;
 
	DIR *d = opendir(path);
	if (!d) {
		return -1;
	}
 
	while ((ent = readdir(d))) {
		if (!strcmp(ent->d_name, ".") || !(strcmp(ent->d_name, "..")))
			continue;
		ret = 0;
		break;
	}
 
	closedir(d);
	return ret;
}
 
int functionrmdir(char *path){
	
	struct stat stats;
	
	stat(path, &stats);

	
	if(S_ISDIR(stats.st_mode)){
		if(dir_empty(path) == 0){
			printf("rmdir: %s is not empty \n", path);
		}else{
			/*remove*/
			rmdir(path);
			return EXIT_SUCCESS;
		}
	}else{
		printf("rmdir: cannot rmdir, is not a directory: %s \n", path);
	}
    	return 0;

}
/*
 * Prints program version and exits.
 */
static void version(void)
{
	printf("rmdir (Nanvix Coreutils) %d.%d\n\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Copyright(C) 2011-2014 Pedro H. Penna\n");
	printf("This is free software under the "); 
	printf("GNU General Public License Version 3.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n\n");
	
	exit(EXIT_SUCCESS);
}

/*
 * Prints program usage and exits.
 */
static void usage(void)
{
	printf("Usage: rmdir [options] <dirname>\n\n");
	printf("Brief: Removes directories.\n\n");
	printf("Options:\n");
	printf("  --help    Display this information and exit\n");
	printf("  --version Display program version and exit\n");
	
	exit(EXIT_SUCCESS);
}

/*
 * Gets program arguments.
 */
static void getargs(int argc, char *const argv[])
{
	int i;     /* Loop index.       */
	char *arg; /* Current argument. */
		
	/* Read command line arguments. */
	for (i = 1; i < argc; i++)
	{
		arg = argv[i];
		
		/* Parse command line argument. */
		if (!strcmp(arg, "--help")) {
			usage();
		}
		else if (!strcmp(arg, "--version")) {
			version();
		}
		else {
			args.dirname = arg;
		}
	}
	
	/* Missing operands. */
	if ((args.dirname == NULL))
	{
		fprintf(stderr, "rmdir: missing operands\n");
		usage();
	}
}

/*
 * Creates a link between two files
 */
int main(int argc, char *const argv[])
{
	getargs(argc, argv);
	
	/* Failed to rmdir(). */
	if (functionrmdir(args.dirname) < 0)
	{
		fprintf(stderr, "rmdir: cannot rmdir()\n");
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}
