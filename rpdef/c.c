// #include "c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int whichCC (unsigned char *cc) {
	char * whichCC = malloc (19 + strlen (cc)); // Allocate enough memory for "env which"...
	strcpy (whichCC, "/usr/bin/env which ");
	strcat (whichCC, cc); // Append the name of the compiler
	return system (whichCC);
}
