#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "c.h"

inline int readuntil (FILE *, char);

int whichCC (char *cc) {
	char * whichCC = malloc (19 + strlen (cc)); // Allocate enough memory for "env which"...
	assert (whichCC);
	strcpy (whichCC, "/usr/bin/env which ");
	strcat (whichCC, cc); // Append the name of the compiler
	register int x = system (whichCC);
	free (whichCC);
	return x;
}

void parseCFlags (FILE *buildfile, cflaglist *cflags) {
	unsigned int maxlinesize;

	if (getpagesize () > 1024) { maxlinesize = getpagesize (); }
	else { maxlinesize = 1024; }

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

		assert (!(readuntil (buildfile, ':'))); // Move the byte pointer to ":"
		assert (!(fgets (line, maxlinesize, buildfile))); // Get the rest of the line

		switch (y) {
			case 0x16 : { // 'always' = aXORw
				cflags->always = strdup (line);
				assert (cflags->always);
			}

			case 0x1A : { // 'native' = nXORt
				cflags->native = strdup (line);
				assert (cflags->native);
			}

			case 0x05 : { // 'warn' = wXORr
				cflags->warn = strdup (line);
				assert (cflags->warn);
			}

			case 0x18 : { // 'quiet' = qXORi
				cflags->quiet = strdup (line);
				assert (cflags->quiet);
			}

			case 0x06 : { // 'debug' = dXORb
				cflags->debug = strdup (line);
				assert (cflags->debug);
			}

			case 0x0E : { // 'lib' = lXORb
				cflags->lib = strdup (line);
				assert (cflags->lib);
			}

			case 0x02 : { // 'link' = lXORn
				cflags->link = strdup (line);
				assert (cflags->link);
			}

			default : {
				perror ("Can't parse one of your cflags lines. Bye.\n");
				exit(17);
			}
		}
	}

	free(line);
	return;
}

inline int readuntil (FILE *stream, char until) {
	register char c;

	do {
		c = fgetc (stream);
	} while (!( (c == until) || (c == EOF) )); // Finish off if the character is correct or you hit EOF

	if (c == EOF) { perror ("Like seriously? I just got EOF'ed! Like WTH?!?!?"); return 1; }

	return 0;
}
