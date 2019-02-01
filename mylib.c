#include "header.h"
/****************MAIN METHODS****************/
struct node r;
int n = 0;
void Initialize(){
    root = (struct node*)malloc(sizeof(struct node));               //set global root to point to struct node
    strcpy(root->name, "/");
    root->type = 'D';
    root->siblingPtr = root; //root sibling points to itself
    root->parentPtr = root;  //root parent points to itself
    cwd = root;   

}
/*************************TOKENIZE***************************/
int clearName(){
    memset(bname,'\0',sizeof(bname));
    memset(dname,'\0',sizeof(dname));
}
int checkABS(){
    if((pathname[0]) == '/'){
        _ABS = true; //set global ABS (for absolute pathname)
    }
    else{
        _ABS = false;
    }
}
bool tokenize(char *path){
    clearName();
    int end = strlen(pathname) - 1;    //set last index
    int index = 0;
    //printf("In tokenize(%s) | size: %d\n", pathname,end+1);
    char *s;
    checkABS();
    
    s = strtok(path,"/");
    while(s){
        //printf("s: %s\n", s);
        dname[index] = s;
        s = strtok(0,"/");
        index++;
        n++;
    }
    bname[0] = dname[index-1];

   /* printf("bname: %s\n", (bname[0]));
    printf("dname: %s\n", (dname[0])); 
    printf("dname: %s\n", (dname[1])); */

   
    if(strlen(dname[0]) > 0 || strlen(bname[0]) > 0){
        return true;
    } 
    else{
        return false;
    }
}
/************************SEARCHING***************************/
struct node* searchChild(struct node* parent, char* name, int flag){
    struct node *cp = parent->childPtr;  //child pointer
    struct node *previousNode = parent->childPtr;  //child pointer

        while(cp){
             if(name){
                if(strcmp(cp->name,name) == 0 || strcmp(cp->name,bname[0]) == 0)  //compare param. name and childptr name
                { 
                    if(flag == 2){
                        if((strcmp(cp->name, bname[0]) == 0) && cp->type =='D'){
                            exists = 1;
                            cwd = cp;
                        }
                    }
                    return cp;
                }
             }
       
        previousNode = cp;
        cp = cp->siblingPtr;                //traverse to next sibling
    }
    //if inserting for mkdir
    //MAKE A SWITCH THAT WILL RETURN WHAT IT NEEDS TOO
    // BASED OFF OF THE FLAG PARAM...
    //.... mkdir : flag = 1
    //.... rmdir : flag = 2
    //.... cd : flag = 3
    //etc...

    if(flag == 1){
        struct node* temp = (struct node *)malloc(sizeof(struct node));
        strcpy(temp->name,bname[0]);
        temp->type = 'D';
        temp->childPtr = NULL;
        temp->siblingPtr = NULL;
        temp->parentPtr = parent;
        if(!parent->childPtr){ //if parent has no children, assign it a child
            parent->childPtr = temp;
        }
        else{  //if parent has children then put at end of children list
            previousNode->siblingPtr = temp;
        }
    }
    if(flag == 3){
        struct node* temp = (struct node *)malloc(sizeof(struct node));
        strcpy(temp->name,bname[0]);
        temp->type = 'F';
        temp->childPtr = NULL;
        temp->siblingPtr = NULL;
        temp->parentPtr = parent;
        if(!parent->childPtr){ //if parent has no children, assign it a child
            parent->childPtr = temp;
        }
        else{  //if parent has children then put at end of children list
            previousNode->siblingPtr = temp;
        }
    }

    return 0;
}

struct node* findDirectory(char *path, int flag)
{
    struct node *p = cwd;     //set ptr to cwd
    struct node *parPtr;      //declare parentPtr

    if(!(tokenize(path))){ 
        return p;
    }
    if (_ABS){      //if pathname is absolute/relative
        p = root;   //set p --> root
    }

    for(int i = 0; i < n;i++){
       p = searchChild(p, dname[i], flag);
       if(p == 0){
           return 0;
       }
       else if(p->type =='D'){
            if(flag == 4){
                if(strcmp(p->name,bname[0]) == 0){
                    prev = p;
                    exists = 1;
                }
            }
        }
        else{
            if(flag == 4){
                if(strcmp(p->name,bname[0]) == 0){
                    prev = p;
                    exists = 1;
                }
            }
        }
    }
    return p;
}

