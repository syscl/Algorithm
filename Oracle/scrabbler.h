

#ifndef __SCRABBLER_H__
#define __SCRABBLER_H__

#include "syscl_lib.h"
//
// global variables here
//
const char *gFILENAME = "words.txt";

#define kMAXBUF       256

#define PREFIX        0 
#define SUFFIX        1
#define NORMAL       -1
#define INVALID_ARGV -2

#define SINGLE_ARGV   1

typedef int pattern_t;

#define kUSAGE "[Error] Invalid arguments.\n[Usage] scrabbler --prefix ... or scrabbler -p ...\n[Usage] scrabbler --suffix ... or scrabbler -s ..."
//
// functions declare here
//
pattern_t catchMode(char *);
//
// pointer to function
//
bool (*letterIsMatch)(char *, char *);
//
// comparing functions waits for calling
//
bool ptnIsMatch(char *, char *);
bool prefixIsMatch(char *, char *);
bool suffixIsMatch(char *, char *);

#endif
