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
xx0 *find(double skey,xx0 *p,int *pn);
int find_xx0(double skey,xx0 *p,int *pn);
void view_xx0(xx0 *ptr,int blank);
void inorder(xx0 *ptr);
/*Functions used in insertion*/
xx0 *insert(double ikey,xx0 *proot);
int rec_ins(double ikey,xx0 *p,double *pk,xx0 **pkrsub);
void insertByShift(int k,xx0 *krsub,xx0 *p,int n);
void split(int k,xx0 *krsub,xx0 *p,int n,int *upkey,xx0 **newnode);
/*Function used in deletion*/
xx0 *delete(double dkey,xx0 *p);
void rec_del(double dkey,xx0 *p);
void delByShift(xx0 *p,int n);
int copy_succkey(xx0 *p,int n);
void restore(xx0 *p,int n);
void borrowLeft(xx0 *p,int n);
void borrowRight(xx0 *p,int n);
void combine(xxx0 *p,int m);

#include "sys_xx0/xxx001.c"
#include "sys_xx0/xxx002.c"
#include "sys_xx0/xxx003.c"

#endif 
