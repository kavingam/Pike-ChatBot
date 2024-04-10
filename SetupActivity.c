#include "RES/sys_xx0.h"

/*MainActivity Function Testing*/
int main() {
    xx0 *root = NULL;
    
    int i;
    for(i=1;i<=5;i++) 
        root = insert(i,root);    
    // inorder(root);
    view_xx0(root,0);
    return 0;
}