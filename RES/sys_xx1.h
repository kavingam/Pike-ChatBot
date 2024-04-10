#ifndef SYS_XX0_H
#define SYS_XX0_H

// Header file content goes here

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BT_O 5
#define BT_MAX (BT_O - 1)
#if BT_O % 2 == 0
#define CEIL_BTDIV (BT_O / 2)
#else
#define CEIL_BTDIV ((BT_O + 1 ) / 2)
#endif
#define BT_MIN (CEIL_BTDIV - 1)

typedef struct sys_xx0 xx0;
struct sys_xx0 {
    int count;
    double key[BT_MAX + 1];
    struct sys_xx0 *sub[BT_MAX+1];
};

/* B - Tree */
xx0 find(double skey,xx0 *p,int *pn);
int find_xx0(double skey,xx0 *p,int *pn);
void view_xx0(xx0 *ptr,int blank);
void inorder(xx0 *ptr);







#endif 
