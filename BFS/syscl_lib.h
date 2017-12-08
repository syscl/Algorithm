//
// This is Yating Zhou(aka syscl)'s header
//
#ifndef __SYSCL_LIB_H__
#define __SYSCL_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// homework information
#define HW_INFO "Homework X"
#define AUTHOR 	"Yating Zhou"
#define CWID   	"A12345678"

//
// define kDEBUG, true  = turn on
//              , false = turn off(default) *
//
#define kDEBUG false

#if kDEBUG
#define DEBUG_PREFIX "Debug: "
#define DBG(arg...) do { printf(DEBUG_PREFIX arg); } while(0)
#else
#define DBG(arg...) do {} while(0)
#endif

#define kRETSUCCESS false
#define kRETFAILURE true

#define kMAXBUF		256	// change if you want more jugs' situation
#define kMAXJUG     10	// change if you want more jugs 

//==============================================================================
// gMin() gMax(): we don't use marco to define max and min function 
// due to it will cause some weird bug once it extends to large scale project
//==============================================================================

static inline int gMin(int a, int b) 
{
	return (a < b) ? a : b;
}

static inline int gMax(int a, int b)
{
	//return -(gMin(-a, -b)); // reuse exist function, but cause one more function push to stack
	return (a > b) ? a : b;
}

//==============================================================================
// printHeader
//==============================================================================

#define printHeader(...) do {\
	puts("\n-------------------------------");\
	puts(HW_INFO);\
	printf("Author: %s\n", AUTHOR);\
	printf("CWID:   %s\n", CWID);\
	printf("Debug:  %s\n", kDEBUG ? "ON" : "OFF");\
	puts("-------------------------------");\
} while (0)

//==============================================================================
// BFS private methods and type
//==============================================================================

#define INF   -1

typedef int vol;	// volume

// jug has two props: 1 for current water another one for its maximum capacity
struct _jug {
	vol water;
	vol capacity;
};

typedef struct _jug jug_t;

// init jug props
bool initJug(jug_t *jug, vol water, vol capacity)
{
	jug->water 	  = water;
	jug->capacity = capacity;
	return ((jug->water == water) && (jug->capacity == capacity)); 
}

struct _vtx {
	jug_t  		jug[kMAXJUG];	// current water status
	int   		distance;		// distance
	struct _vtx *parent;		// parent
};

typedef struct _vtx vtx;

struct _graph {
	vtx* vertex;
	int  length;
};

typedef struct _graph graph_t;

//
// private functions declare here
//
bool initVtx(vtx *);
bool initGraph(graph_t *);
void printVtx(vtx *);
void print(vtx *);
bool vtxcp(vtx *, vtx *);
bool pour(jug_t *, jug_t *);
bool findVolume(vtx *, vol);
bool vtxcmp(vtx *, vtx *);
bool isInGraph(vtx *, graph_t *);
int getUsrInt(const char *);
void fillWater(vtx *, int);
void vtxfree(vtx *);
void graphfree(graph_t *);
bool insertVtx(vtx *, graph_t *, int);

#endif
