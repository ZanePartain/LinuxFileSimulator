#include "mylib.c" //contains all library functions (like tokenize etc..)



int cd(char *pathname){
    struct node *ptrDir;
    exists = 0;
    n = 0;
    // if no pathname return to root
    if(strlen(pathname) == 0){
        cwd = root;
    }

    //check pathnae for ".." or "../../" etc..
    else if(pathname[0] == '.'){
        if(tokenize(pathname)){
            for(int i = 0; i < n; i++) //loop over dname and go back case: "../../"
            {
                if(strcmp(dname[0],"..") == 0){
                    cwd = cwd->parentPtr;
                }
            }
        }
    }

    //go look for directory from pathname
    else{
        ptrDir = findDirectory(pathname,2);

        if(exists != 1){
            //no directory by that name
            printf("_err: not a directory");
        }
    }
}

int mkdir(char *pathname){
    char tempPath[64];
    struct node *p;
    struct node prev;
    n = 0;
    int non_exist = 0;
    strcpy(tempPath,pathname);
    p = findDirectory(tempPath,0); 

    if(p==0){ //dir doesnt exist
       strcpy(tempPath,pathname);
       findDirectory(tempPath,1); //create dir
    }
    else{
        printf("_err: dir name already exists\n");
    }
   
}
int rmdir(char *pathname){
    struct node *ptrDir;

    ptrDir = findDirectory(pathname,4);

    if(exists!=1){
        //no directory by that name
        printf("_err: not a directory");
    }
    else{
        //is a directory name
        if(prev->type == 'D'){
            ptrDir = prev;                                      //set ptrDir to prev
            struct node *parent = prev->parentPtr;              //set parent ptr
            struct node *child = prev->parentPtr->childPtr;

            //delete only child!!
            if(child->siblingPtr == NULL){
                parent->childPtr = NULL;
                free(child);
            }
            //more than one child 
            else{
                while(child){
                    //delete head of list
                    if(strcmp(parent->childPtr->name, prev->name) == 0){
                        ptrDir = child;
                        parent->childPtr = child->siblingPtr;
                        free(ptrDir);
                        break;
                    }
                    //delete in middle or end of list
                    else{
                        if(strcmp(prev->name,child->name) == 0){
                            ptrDir->siblingPtr = child->siblingPtr;
                            free(child);
                            break;
                        }
                    }
                    ptrDir = child;             //previous child
                    child = child->siblingPtr;  //next child
                }
            }
           
        }
        else{
            printf("_err: rmdir (removes directories)");
        }
    }
}


int ls(char *pathname){
    struct node *p = cwd->childPtr;
    while(p){
        printf(" %s\t",p->name);
        p = p->siblingPtr;
    } 
}


int pwdRec(struct node *p){
    if(strcmp(p->parentPtr->name, "/") != 0){
        pwdRec(p->parentPtr);
    }
    if(strcmp(p->name, "/")){
        putchar('/');
    }
    printf("%s",p->name);
}
int pwd(char *pathname){
    printf("zaney@wsu-Linux-sim:~");
    struct node *p = cwd;
    pwdRec(p);
    putchar(' ');
}


int creat(char *pathname){
    char tempPath[64];
    struct node *p;
    struct node prev;
    n = 0;
    int non_exist = 0;
    strcpy(tempPath,pathname);


    p = findDirectory(tempPath,0); 

    if(p==0){     //file doesnt exist
       strcpy(tempPath,pathname);
       findDirectory(tempPath,3);
    }
    else{
        printf("_err: dir name already exists\n");
    }
}
int rm(char *pathname){
    struct node *ptrDir;

    ptrDir = findDirectory(pathname,4);

    if(exists!=1){
        //no directory by that name
        printf("_err: not a directory");
    }
    else{
        if(prev->type == 'F'){
            ptrDir = prev;                                   //set ptrDir to prev
            struct node *parent = prev->parentPtr;           //set parent ptr
            struct node *child = prev->parentPtr->childPtr;  //set child ptr

            while(ptrDir){
                ptrDir = ptrDir->siblingPtr;
            }

            ptrDir = prev; //set ptrDir back to prev

            //delete only child!!
            if(child->siblingPtr == NULL){
                parent->childPtr = NULL;
                free(child);
            }
            //more than one child 
            else{
                while(child){
                    //delete head of list
                    if(strcmp(parent->childPtr->name, prev->name) == 0){
                        ptrDir = child;
                        parent->childPtr = child->siblingPtr;
                        free(ptrDir);
                        break;
                    }
                    //delete in middle or end of list
                    else{
                        if(strcmp(prev->name,child->name) == 0){
                            ptrDir->siblingPtr = child->siblingPtr;
                            free(child);
                            break;
                        }
                    }
                    ptrDir = child;             //previous child
                    child = child->siblingPtr;  //next child
                }
            }
           
        }
        else{
            printf("_err: rmd (removes files)");
        }
    }
}

int reloadFiles(char *fileName){
    char type;
    char name[64];
    FILE *infile = fopen(fileName,"r");
    if(infile){
        fscanf(infile," %c %s ",&type, name); //bypass root
        while(!feof(infile)){
            fscanf(infile," %c %s ",&type, name);
            if(type == 'D'){
                mkdir(name);
            }
            else{
                creat(name);
            }
        }
    }
    else{
        printf("_err: cannot open file\n");
    }
    fclose(infile);
}
int reload(char *fileName){
    //reload default file tree from cmd quit
    if(strlen(fileName) == 0){
        reloadFiles("myfiles");
    }
    else{
        reloadFiles(fileName);
    }
}

int saveParentRec(FILE *outfile, struct node* curNode)
{
    if(strcmp(curNode->parentPtr->name, "/") != 0){
        saveParentRec(outfile,curNode->parentPtr);
    }
    if(strcmp(curNode->name, "/")){
        strcat(parentPath, "/");
    }
    if(curNode->type == 'D'){
        strcat(parentPath, curNode->name);

    }
}

int saveChild(FILE * outfile, struct node *curNode){

    while(curNode){
        memset(parentPath, '\0', sizeof(parentPath)); //reset global parentPath
        saveParentRec(outfile, curNode);              //set curNode's absolute parentPath
        //for directory
        if(curNode->type == 'D')
        { 
            fprintf(outfile, " %c %s\n",curNode->type, parentPath); //save parentPath
            saveChild(outfile, curNode->childPtr);                  //pass in directories child
        }
        //for file
        else{
            //save parentPath/file (file is a child)
            fprintf(outfile, " %c %s%s\n",curNode->type, parentPath, curNode->name);
        }
        curNode = curNode->siblingPtr;  //to next sibling
    }
}

int save(char *pathname){
    struct node *child;
    int nameLength = strlen(pathname);
    FILE *outfile;
    //save to 'myfiles' (default location) or save to user spec. loc.
    switch(nameLength){
        case 0:
            outfile = fopen("myfiles", "w+");
            break;
        default:
            outfile = fopen(pathname, "w+");
            break;
    }
    fprintf(outfile, " %c %s\n", root->type, root->name); //print root dir
    
    child = root->childPtr;        //set child ptr
    if(child){                     //if root has a child    
        saveChild(outfile, child); //save all of its children to outfile
    }

    fclose(outfile); //close outfile
}

int menu(char *pathname){
    printf("|~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~|\n");
    printf("  mkdir  rmdir   ls    pwd    creat\n");
    printf("  rm     reload  save  menu   quit \n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");

}


//GLOBAL
// function ptr to al the functions above that takes in a pathname char* param.
int (*funcptr[])(char *) = {(int(*)())mkdir,rmdir,ls,cd,pwd,creat,rm,
                            reload,save,menu};

