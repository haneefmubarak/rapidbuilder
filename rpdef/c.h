// c.h -- header file for rpdef C

#pragma once

typedef struct {
	char *always;
	char *native;
	char *warn;
	char *quiet;
	char *debug;
	char *lib;
	char *link;
} cflaglist;

extern int whichCC (char *);
extern void parseCFlags (FILE *, cflaglist *);
