//
//  scrabbler.c
//  scrabbler
//
//  Created by Yating Zhou(aka syscl) on 20/05/2017.
//  Copyright (c) 2017 Yating Zhou(aka syscl). All rights reserved.
//
//  This work is licensed under the Creative Commons Attribution-NonCommercial
//  4.0 Unported License => http://creativecommons.org/licenses/by-nc/4.0
//
#include "syscl_lib.h"
#include "scrabbler.h"
#include "sort.h"

//============================start=============================================

int main(int argc, char **argv)
{
    if (argc == 1) return kRETFAILURE;
    FILE* file = fopen(gFILENAME, "r");
    char line[kMAXBUF];
    int mode = NORMAL;
    char *pattern = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (*(argv+i)[0] == '-')
        {
            mode = catchMode(*(argv+i));
            switch (mode)
            {
                case PREFIX:
                    pattern = *(argv+i+1);
                    letterIsMatch = &prefixIsMatch;
                    break;

                case SUFFIX:
                    letterIsMatch = &suffixIsMatch;
                    pattern = *(argv+i+1);
                    break;

                default:
                    puts(kUSAGE);
                    return kRETFAILURE;
                    break;
            }
        }
        else if (i == SINGLE_ARGV)
        {
            //
            // normal searching
            //
            letterIsMatch = &ptnIsMatch;
            pattern = *(argv+i);
            break;
        }
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        if (letterIsMatch(pattern, line) == true)
        {
            printf("%s\n", line);
        }
    }

    fclose(file);
    return kRETSUCCESS;
}

//==============================================================================
// catchMode(...) which search pattern should we use? prefix vs suffix vs normal
//==============================================================================

pattern_t catchMode(char *pattern)
{
    if (strcmp(pattern, "--prefix")==0||strcmp(pattern, "-p")==0)      return PREFIX;
    else if (strcmp(pattern, "--suffix")==0||strcmp(pattern, "-s")==0) return SUFFIX;
    return INVALID_ARGV; 
}

//==============================================================================
// ptnIsMatch(...) check if src(source) is match the ptn(pattern)
//==============================================================================

bool ptnIsMatch(char *tar, char *src)
{ 
    int wlimit = strlen(tar);
    int lnlen  = strlen(src);
    if (wlimit < lnlen) return false;
    
    for (int i = 0; i < lnlen; i++)
    {   
        //
        // check if all the letters that are contained in pattern(tar)
        //    
        if (strchr(tar, src[i]) == NULL) return false;
    }

    /*
     * check if there's duplicate letters:
     * suppose the length of src(source) is m, using quicksort takes O(mln(m)) runtime
     * comparation between adjency elements to check 
     * if there's duplicate letters takes at most O(m) 
     * Here's the theorem to ensure the following checking takes at most O(m)
     * If a_1 <= ... <= a_n and each of the adjency elements is unique, then all the elements are unique
     * Proof(by contradiction): suppose there's two elements(say a_k and a_j) that are the same, then
     * a_k = a_(k+1) = ... = ... = a_j, but, a_k != a_(k+1), we finish the proof. 
     */
    char *tmpln = sort(src);

    /* check duplicate characters
         notice strlen(tmpln) is identical to lnlen */
    for (int i = 0; i < lnlen; i++)
    {
        if (tmpln[i] != '\0')
        {
            if (tmpln[i] == tmpln[i + 1]) return false;
        }
    }

    return true;
}

//==============================================================================
// prefixIsMatch(...) check if prefix is match the ptn(pattern)
//==============================================================================

bool prefixIsMatch(char *tar, char *src)
{
    int wlim  = strlen(tar);
    int lnlen = strlen(src);
    if (wlim  > lnlen) return false; // note: here's the difference between ptnIsMatch vs prefixIsMatch
    if (strstr(src, tar) != src) return false;
    return true;
}

//==============================================================================
// suffixIsMatch(...) check suffix is match the ptn(pattern)
//==============================================================================

bool suffixIsMatch(char *tar, char *src)
{
    int wlim  = strlen(tar);
    int lnlen = strlen(src);
    if (wlim  > lnlen) return false;

    char *rsrc = reverse_str(src);
    char *rtar = reverse_str(tar);

    if (strstr(rsrc, rtar) != rsrc) return false;
    return true;
}

//==============================================================================
// reverse_str(...) reverse str(string)
//==============================================================================

char *reverse_str(char *str)
{
    char *tmpstr = calloc(strlen(str), sizeof(char));
    strcpy(tmpstr, str);
    int i, j, c;
    for (i=0, j=strlen(str)-1; i<j; i++, j--)
    {
        c = tmpstr[i];
        tmpstr[i] = tmpstr[j];
        tmpstr[j] = c;
    }
    return tmpstr;
}
