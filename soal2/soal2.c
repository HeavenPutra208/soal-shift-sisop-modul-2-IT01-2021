#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(){
    pid_t child_id = fork();

    child_id = fork();

    //extract
    while(wait(NULL) > 0);
    if(child_id == 0){
        char *argv[] = {"unzip", "pets.zip", "-d", "home/traveller/modul2/petshop/", NULL};
        execv("/usr/bin/unzip", argv)
    }
}
