xx0 *insert(double ikey,xx0 *proot) {
    double k,taller;
    xx0 *krsub,*temp;
    taller = rec_ins(ikey,proot,&k,&krsub);
    if(taller) /*tree grown in height, new root is created*/
    {
        temp = (xx0*)malloc(sizeof(xx0));
        temp->count = 1;
        temp->sub[0] = proot;
        temp->key[1] = k;
        temp->sub[1] = krsub;
        proot = temp;
    }
    return proot;
}
int rec_ins(double ikey,xx0 *p,double *pk,xx0 **pkrsub) {
    int n;
    int flag;
    if(p == NULL) {
        *pk = ikey;
        *pkrsub = NULL;
        return 1;
    }
    if(find_xx0(ikey,p,&n)) {
        printf("duplicate keys are not allowed\n");
        return 0;
    }
    flag = rec_ins(ikey,p->sub[n],pk,pkrsub);
    if(flag) {
        if(p->count < BT_MAX) {
            insertByShift(*pk,*pkrsub,p,n);
            return 0;
        }
        else {
            split(*pk,*pkrsub,p,n,pk,pkrsub);
            return 1;
        }
    }
    return 0;
}
void insertByShift(int k,xx0 *krsub,xx0 *p,int n) {
    int i;
    for(i = p->count; i>n;i--) {
        p->key[i+1] = p->key[i];
        p->sub[i+1] = p->sub[i];
    }
    p->key[n+1] = k;
    p->sub[n+1] = krsub;
    p->count++;
}
void split(int k,xx0 *krsub,xx0 *p,int n,int *upkey,xx0 **newnode) {
    int i,j;
    int lastkey;
    xx0 *lastsub;
    int d = CEIL_BTDIV;
    if(n==BT_MAX) {
        lastkey = k;
        lastsub = krsub;
    }
    else {
        lastkey = p->key[BT_MAX];
        lastsub = p->sub[BT_MAX];
        for(i=p->count-1;i>n;i--) {
            p->key[i+1] = p->key[i];
            p->sub[i+1] = p->sub[i];
        }
        p->key[i=1] = k;
        p->sub[i+1] = krsub;
    }
    *newnode = (xx0*)malloc(sizeof(xx0));
    p->count = d-1;
    (*newnode)->count = BT_O - d;
    (*newnode)->key[BT_O-d] = lastkey;
    (*newnode)->sub[BT_O-d] = lastsub;
}