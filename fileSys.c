
/* Zane Partain*/
/*
* header file for all stdlibs
* definitions used, structs and global vars for fileSys.c program.
*/
#include "cmd.c"


int FindCommand(char *cmd){
    //look through global 'cmdlib' for 'cmd' param.
    for(int i = 0; cmdlib[i] != NULL; i++){
        if(strcmp(cmd, cmdlib[i]) == 0){
            return i; //return index loc. of cmd 
        }
    }
    return -1; //'cmd' not in 'cmdlib'
}

void RunCommand(int cmd, char pathname[64]){
    // call the correct command using 'cmd' param
    switch (cmd) 
        {
            case 0: funcptr[cmd](pathname); break;
            case 1: funcptr[cmd](pathname); break;
            case 2: funcptr[cmd](pathname); break;
            case 3: funcptr[cmd](pathname); break;
            case 4: funcptr[cmd](pathname); break;
            case 5: funcptr[cmd](pathname); break;
            case 6: funcptr[cmd](pathname); break;
            case 7: funcptr[cmd](pathname); break;
            case 8: funcptr[cmd](pathname); break;
            case 9: funcptr[cmd](pathname); break;
            case 10: break;
            default: printf("err_: unkwn command\n");
                break;
        }
}


int main(int argc, char* argv, char* env){
    Initialize(); //init. root directory
    int cmd = 0; //stores cur. user command          
    do{
        pwd("none");
        fgets(line, LIMIT, stdin);                 // read line
        line[strlen(line)-1] = 0;                  // elim. null char
        sscanf(line, "%s %s", command, pathname);  // parse line into command/pathname
        cmd = FindCommand(command);                // find index loc. of command
        RunCommand(cmd,pathname);
        memset(&pathname,'\0',sizeof(pathname));
        putchar('\n');
    }while(cmd != 10);
    save("myfiles");
}