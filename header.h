#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LIMIT 128

/*structures*/
struct node{
    char name[64];           //name of file/dir
    char type;               //node is F/D (file/dir)
    struct node *siblingPtr;
    struct node *childPtr;
    struct node *parentPtr;
};

/*global variables*/
struct node *root, *cwd, *prev;        //root '/' and cwd (curr. working dir) pointers
char line[LIMIT];               //user input command line
char command[16], pathname[64]; //command and pathname strings
char *dname[64], *bname[64]; 
char *cmdlib[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm",
                  "reload", "save", "menu","quit", NULL };
bool _ABS = false; //1 == absolute, 0 == relative (pathname)
int exists = 0;
char parentPath[200];
