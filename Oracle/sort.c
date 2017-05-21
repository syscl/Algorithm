#include "sort.h"

//==============================================================================
// sort(...) call specific sort functions(will refine it later)
//==============================================================================

char *sort(char *str)
{
    char *sort_str = calloc(strlen(str), sizeof(char));
    strcpy(sort_str, str);
    int end_index = strlen(str) - 1;
    quicksort(sort_str, 0, end_index);
    return sort_str;
}

//==============================================================================
// quicksort(...) quick sort the str(string)
//==============================================================================

void quicksort(char *str, int p, int r)
{
    if (p < r)
    {
        int q = part(str, p, r);
        quicksort(str, p, q - 1);
        quicksort(str, q + 1, r);
    }
    return;
}

//==============================================================================
// part(...) find the correct location for str[r] ranging from str[p] to str[r]
//==============================================================================

int part(char *str, int p, int r)
{
    char x = str[r];
    int  i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (str[j] <= x)
        {
            i = i + 1;
            exchange(str+i, str+j);
        }
    }
    exchange(str+i+1, str+r);
    return (i + 1);
}

//==============================================================================
// exchange(...) exchange the value of two values 
//==============================================================================

void exchange(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
