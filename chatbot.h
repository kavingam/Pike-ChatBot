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

bot *search(int skey,bot *p,int *pn);
int search_info(int skey,bot *p,int *pn);
void printList(bot *ptr,int blank);
/*  functions used in insertion */ 
bot *insertByShift(int k,bot *proot);
int rec_ins(int ikey,bot *p,int *pk,bot **pkrchild);
void split(int k,bot *krchild,bot *p,int n,int *upkey,bot **newnode);
/* functions used in deletion */
bot *delete(int dkey,bot *p);
void rec_del(int dkey,bot *p);
void delByShift(bot *p,int n);
int copy_succkey(bot *p,int n);
void restore(bot *p,int n);
void borrowLeft(bot *p,int n);
void borrowRight(bot *p,int n);
void combine(bot *p,int m);
#endif