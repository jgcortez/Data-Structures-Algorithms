#include <string.h>
#include <stdio.h>
#include "util.h"
#include <ctype.h>

// 00-Programming-Help/03-nextWord

int nextWord(char *word){
    
    char c;
    int i, r_value;

//---------------------------------------------------
//  search for the start of the next word
//---------------------------------------------------

    r_value = 0;
    c = getchar();

#if _util_version == 1
    while (c == ' ' || c == '\t' || c == '\n'){
        c = getchar();
    }
#else
    while (!isalpha(c)){
        c = getchar();
        if (c == EOF) return (0);
    }
#endif

//---------------------------------------------------
//  within a word
//---------------------------------------------------

    i = 0;
    while (c != EOF){
#if _util_version == 1
        if (c == ' ' || c == '\t' || c == '\n'){
            break;
        }
#else
        if (!isalpha(c)){
            break;
        }
#endif
        r_value = 1;
        word[i] = c;
        i++;
        c = getchar();
    }

//---------------------------------------------------
//  end of a word
//---------------------------------------------------

    word[i] = "\0";

    return r_value;
}