#include "c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int whichCC (unsigned char *cc) {
	char * whichCC = malloc (19 + strlen (cc)); // Allocate enough memory for "env which"...
	assert (
	strcpy (whichCC, "/usr/bin/env which ");
	strcat (whichCC, cc); // Append the name of the compiler
	return system (whichCC);
}

void parseCFlags (FILE *buildfile, cflaglist *cflags) {
	unsigned int maxlinesize;

	if (getpagesize () > 1024) { maxlinesize = getpagesize (); }
	else { maxlinesize = 1024 }

	char *line;
	assert (line = malloc (maxlinesize));

	int x;
	char y;
	int set[7] = { 0 };
	for (x = 0; x < 7; x++) {
		fgetc (buildfile);
		y = fgetc (buildfile); // XOR the first and third chars for a switch val
		fgetc (buildfile);
		y = y ^ fgetc (buildfile);

		switch (y) {
			case 0x16 : { // 'always' = aXORw

			}

			case 0x1A : { // 'native' = nXORt

			}

			case 0x05 : { // 'warn' = wXORr

			}

			case 0x18 : { // 'quiet' = qXORi

			}

			case 0x06 : { // 'debug' = dXORb

			}

			case 0x0E : { // 'lib' = lXORb

			}

			case 0x02 : { // 'link' = lXORn

			}

			default : {
				perror ("Can't parse one of your cflags lines. Bye.\n");
				exit();
			}
		}
	}

	return;
}
