#ifndef __CHATBOT__H
#define __CHATBOT__H

#include <stdio.h>
#include <stdlib.h>

#define M 5 
#define MAX (M-1)
#if M%2 == 0
#define CEIL_Mdiv2 (M/2)
#else
#define CEIL_Mdiv2 ((M+1)/2)
#endif
#define MIN (CEIL_Mdiv2 - 1)

typedef struct bot_arch bot;
struct bot_arch {
    int cout;
    int key[MAX+1];
    struct bot_arch *config[MAX+1];
};
#endif