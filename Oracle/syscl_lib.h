//
// Yating Zhou(aka syscl)'s lib 
//

#ifndef __SYSCL_LIB_H__
#define __SYSCL_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//
// define kDEBUG, 1 = turn on
//              , 0 = turn off(default) *
//
#define kDEBUG 		true

//
// common constant place here
//
#define kTRUE  		true
#define kFALSE 		false
#define kRETSUCCESS 0
#define kRETFAILURE 1

#if kDEBUG
#define DBG_PREFIX "Debug: "
#define DBG(args...) do { printf(DBG_PREFIX args); } while(kFALSE)
//
// getFunctionName: retrieve function's name
//
#define getFunctionName(args...) do { printf(DBG_PREFIX "%s()", __func__); } while(kFALSE) 
//
// list init information for specific function
//
#define InitDBG(args...) do { printf(DBG_PREFIX "%s() ===>\n", __func__); } while(kFALSE)
//
// list return information for specific function
//
// usage: e.g. ReturnDBG("%s\n", string); ReturnDBG("%d\n", ret); 
//
#define ReturnDBG(args...) do { printf(DBG_PREFIX "%s() <==", __func__); printf("=" args); } while(kFALSE)
#else
#define DBG(args...) 
#define getFunctionName(args...)
#define InitDBG(args...)
#define ReturnDBG(args...)
#endif

#endif