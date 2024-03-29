bot *search(int skey,bot *p,int *pn) {
    int found;
    if(p == NULL) {
        /* Base case 1 : if key not found */
        return NULL;
    }
    found = search_info(skey,p,pn);
    if(found) {
        /* Base case 2 : if key found in node p */
        return p; 
    }
    else {
        /* Recursive case : search in noded p->config[*pn] */ 
        return search(skey,p->config[*pn],pn);
    }
}
int search_info(int skey,bot *p,int *pn) {
    if(skey < p->key[1]) { /* skey less than left most key*/
        *pn = 0;
        return 0;
    }
    *pn = p->count;
    while((skey < p->key[*pn]) && *pn > 1) {
        (*pn) --;
    }
    if(skey == p->key[*pn]) {
        return 1;
    }
    else {
        return 0;
    }
}

void printList(bot *ptr,int blanks) {
    if(ptr) {
        int i;
        for(i=1;i<=blanks;i++) {
            printf(" ");
        }
        for(i=1;i<=ptr->count;i++) {
            printf("%d ",ptr->key[i]);
        }
        printf("\n");
        for(i=1;i<=ptr->count;i++) {
            printList(ptr->config[i],blanks+10);
        }
    }
}
void inorder(bot *ptr) {
    int i;
    if(ptr!=NULL) {
        for(i=0;i<=ptr->count;i++) {
            inorder(ptr->config[i]);
            printf("%d\t",ptr->key[i+1]);
        }
        inorder(ptr->config[i]);
    }
}
/*  functions used in insertion */ 
bot *insert(int ikey,bot *proot) {
    int k,taller;
    bot *krconfig,*temp;
    taller = rec_ins(ikey,proot,&k,&krconfig);
    if(taller) {
        /* tree grown in height, new root is create */
        temp = (bot *)malloc(sizeof(bot));
        temp->count = 1;
        temp->config[0] = proot;
        temp->key[1] = k;
        temp->config[1] = krconfig;
        proot = temp;
    }
    return proot;
}
void insetByShift(int k,bot *krconfig,bot *p,int n) {
    int i;
    for(i=p->count;i>n;i--) {
        p->key[i+1] = p->key[i];
        p->config[i+1] = p->config[i];
    }
    p->key[n+1] = k;
    p->config[n+1] = krconfig;
    p->count++;
}
int rec_ins(int ikey,bot *p,int *pk,bot **pkrchild) {
    int n,flag;
    if(p==NULL) {
        /*Base case 1*/ 
        *pk = ikey;
        *pkrchild = NULL;
        return 1;
    }
    if(search_info(ikey,p,&n)) /*Base case 2*/
    {
        printf("Duplicate keys are not allowed\n");
        return 0;
    }
    flag = rec_ins(ikey,p->config[n],pk,pkrchild);
    if(flag) {
        if(p->count < MAX) {
            insetByShift(*pk,*pkrchild,p,n);
            return 0;
        }
        else {
            split(*pk,*pkrchild,p,n,pk,pkrchild);
            return 1;
            /*median key to be inserted*/
        }
    }
    return 0;
}
void split(int k,bot *krchild,bot *p,int n,int *upkey,bot **newnode) {
    int i,j;
    int lastkey;
    bot *lastchild;
    int d = CEIL_Mdiv2;
    if(n==MAX) {
        lastkey = k;
        lastchild = krchild;
    }
    else {
        lastkey = p->key[MAX];
        lastchild = p->config[MAX];
        for(i=p->count-1;i > n;i--) {
            p->key[i+1] = p->key[i];
            p->config[i+1] = p->config[i];
        }
        p->key[i+1] = k;
        p->config[i+1] = krchild;
    }
    *newnode = (bot*)malloc(sizeof(bot));
    *upkey = p->key[d];
    for(i=1,j=d+1;j<=MAX;i++,j++) {
        (*newnode)->key[i] = p->key[j];
        (*newnode)->config[i] = p->config[j];
    } 
    (*newnode)->config[0] = p->config[0];
    p->count = d-1; /*number of keys in the left splitted node*/
    (*newnode)->count = M-d;/*number of keys in the right splitted node*/
    (*newnode)->key[M-d] = lastkey;
    (*newnode)->config[M-d] = lastchild;
}
/* functions used in deletion */
bot *rec_delete(int dkey,bot *root) {
    bot *temp;
    rec_del(dkey,root);
    /*if tree becomes shorter, root is changed*/
    if(root!=NULL && root->count==0) {
        temp = root;
        root = root->config[0];
        free(temp);
    }
    return root;
}
void rec_del(int dkey,bot *p) {
    int n,flag,succkey;
    if(p==NULL) /*reached leaf node,key does not exist*/
    {
        printf("value %d not found\n",dkey);
    }
    else {
        flag = search_info(dkey,p,&n);/*node p is a leaf node*/
        if(flag) /*found in current node p*/
        {
            if(p->config[n]==NULL) /*node p is a leaf node*/
            {
                delByShift(p,n);
            }
            else /*node p is a non leaf node*/
            {
                succkey = copy_succkey(p,n);
                rec_del(succkey,p->config[n]);
            }
        }
        else /*not found in current node p*/
        {
            rec_del(dkey,p->config[n]);
        }
        if(p->config[n] != NULL) /*if p is not a leaf node*/
        {
            if(p->config[n]->count < MIN) /*checkk underflow in p->child[n]*/
            {
                restore(p,n);
            }
        }
    }
}
void delByShift(bot *p,int n) {
    int i;
    for(i=n+1;i<=p->count;i++) {
        p->key[i-1] = p->key[i];
        p->config[i-1] = p->config[i];
    }
    p->count--;
}
int copy_succkey(bot *p,int n) {
    bot *ptr;
    ptr = p->config[n]; /*point to the right subtree*/
    while (ptr->config[0]!=NULL)
    {
        ptr=ptr->config[0];
    }
    p->key[n] = ptr->key[1];
    return ptr->key[1];
    
}
void restore(bot *p,int n) {
    if(n!=0 && p->config[n-1]->count > MIN) {
        borrowLeft(p,n);
    }
    else if(n!=p->count && p->config[n+1]->count>MIN) {
        borrowRight(p,n);
    }
    else {
        if(n==0) /*if understand node is leftmost node*/
        {
            combine(p,n+1); /*combine with right sibling*/
        }
        else {
            combine(p,n); /*combine with left sibling*/
        }
    }
}
void borrowLeft(bot *p,int n) {
    int i;
    bot *u; /*underflow node*/
    bot *ls; /*left sibling of node*/
    u = p->config[n];
    ls = p->config[n-1];
    /*shift all the keys and pointers in underflow node u one position right*/ 
    for(i=u->count;i>0;i--) {
        u->key[i+1] = u->key[i];
        u->config[i+1] = u->config[i];
    }
    u->config[1] = u->config[0];
    /*move the separator key from parent node p to underflow node*/
    u->key[1] = p->key[n];
    u->count++;
    /*move the rightmost key of node ls to the parent node *p*/
    p->key[n] = ls->key[ls->count];
    /*rightmost child of ls become leftmost child of node u*/
    u->config[0] = ls->config[ls->count];
    ls->count--;
}

void borrowRight(bot *p,int n) {
    int i;
    bot *u; /*underflow node*/
    bot *rs; /*right sibling of node*/
    u = p->config[n];
    rs = p->config[n+1];
    u->count++;
    u->key[u->count] = p->key[n+1];
    u->config[u->count] = rs->config[0];
    p->key[n+1] = rs->key[1];
    rs->count--;
    rs->config[0] = rs->config[1];
    for(i=1;i<=rs->count;i++) {
        rs->key[i] = rs->key[i+1];
        rs->config[i] = rs->config[i+1];
    }
}
void combine(bot *p,int m) {
    int i;
    bot *x;
    bot *y;
    x = p->config[m];
    y = p->config[m-1];
    y->count++;
    y->key[y->count] = p->key[m];
    for(i=m;i<p->count;i++) {
        p->key[i] = p->key[i+1];
        p->config[i] = p->config[i+1];
    }
    p->count--;
    y->config[y->count] = x->config[0];
    for(i=1;i<=x->count;i++) {
        y->count++;
        y->key[y->count] = x->key[i];
        y->config[y->count] = x->config[i];
    }
    free(x);
}
