xx0 *find(double skey,xx0 *p,int *pn) {
    int found;
    if(p == NULL)  /*base case 1 : if key not found*/
        return NULL;
    found = find_xx0(skey,p,pn); /*Base case 2 : if key not found*/
    if(found) {
        return p; /*Recursive case : search in node p->child[*pn]*/
    }
    else {
        return find(skey,p->sub[*pn],pn);
    }
}
int find_xx0(double skey,xx0 *p,int *pn) {
    if(skey < p->key[1]) {
        *pn = 0;
        return 0;
    }
    *pn = p->count;
    while((skey < p->key[*pn]) && *pn>1) {
        (*pn)--;
    }
    if(skey == p->key[*pn]) {
        return 1;
    }
    else {
        return 0;
    }
}
void view_xx0(xx0 *ptr,int blank) {
    if(ptr) {
        int i;
        for(i=1;i<=blank;i++) {
            printf(" ");
        }
        for(i=1;i<=ptr->count;i++) {
            printf("%f ",ptr->key[i]);
        }
        printf("\n");
        for(i=0;i<=ptr->count;i++) {
            view_xx0(ptr->sub[i],blank+10);
        }
    }
}
void inorder(xx0 *ptr) {
    int i;
    if(ptr != NULL) {
        for(i = 0;i<ptr->count; i++) {
            inorder(ptr->sub[i]);
            printf("%f\t",ptr->key[i+1]);
        }
        inorder(ptr->sub[i]);
    }
}