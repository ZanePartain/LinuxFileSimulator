#include "mylib.c" //contains all library functions (like tokenize etc..)



int cd(char *pathname){
    struct node *ptrDir;
    exists = 0;
    if(strlen(pathname) == 0){
        cwd = root;
    }
    else if(strcmp(pathname, "..") == 0){
        cwd = cwd->parentPtr;
    }

    else{
        ptrDir = findDirectory(pathname,2);

        if(exists != 1){
            //no directory by that name
            printf("_err: not a directory");
        }
        else{
            //is a directory name
            printf("\ncwd: %s type = %c\n", cwd->name, cwd->type);
        }
    }
}

int mkdir(char *pathname){
    struct node *p;
    struct node prev;
    n = 0;
    int non_exist = 0;

    p = findDirectory(pathname,0); 

    if(p==0){     //dir doesnt exist
       findDirectory(pathname,1);
    }
    else{
        printf("_err: dir name already exists\n");
    }
   
}
int rmdir(char *pathname){
    struct node *ptrDir;

    ptrDir = findDirectory(pathname,2);

    if(ptrDir==0){
        //no directory by that name
        printf("_err: not a directory");
    }
    else{
        //is a directory name
        printf("\ncwd: %s type = %c\n", cwd->name, cwd->type);
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
    struct node *p;
    struct node prev;
    n = 0;
    int non_exist = 0;

    p = findDirectory(pathname,0); 

    if(p==0){     //file doesnt exist
       findDirectory(pathname,3);
    }
    else{
        printf("_err: dir name already exists\n");
    }
}
int rm(char *pathname){
    printf("In my_rm (%s)\n",pathname);
}

int reload(char *pathname){
    printf("In my_reload (%s)\n",pathname);
}

int save(char *pathname){
    printf("In my_save (%s)\n",pathname);
}

int menu(char *pathname){
    printf("|~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~|\n");
    printf("  mkdir  rmdir   ls    pwd    creat\n");
    printf("  rm     reload  save  menu   quit \n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");

}

int quit(char *pathname){
    printf("In my_quit (%s)\n",pathname);
}

//GLOBAL
// function ptr to al the functions above that takes in a pathname char* param.
int (*funcptr[])(char *) = {(int(*)())mkdir,rmdir,ls,cd,pwd,creat,rm,
                            reload,save,menu,quit};

