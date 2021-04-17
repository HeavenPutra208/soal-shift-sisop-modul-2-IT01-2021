#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main() {
  pid_t pid, sid;

  pid = fork();     

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    
  pid_t child_id;
  child_id = fork();
  int status;

  if (child_id == 0) {
    char *argv[] = {"mkdir", "Musyik", "Fylm", "Pyoto",  NULL};
    execv("/bin/mkdir", argv);
  }

  child_id = fork();
    if (child_id == 0) {
      char *argv[] = {"Wget --no-check-certificate ", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip",  NULL};
      execv("/usr/bin/wget", argv);
    }

	child_id = fork();
	if (child_id == 0) {
	  while ((wait(&status)) > 0);
      char *argv[] = {"Wget --no-check-certificate ", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip",  NULL};
      execv("/usr/bin/wget", argv);
    }

	child_id = fork();
	if (child_id == 0) {
	  while ((wait(&status)) > 0);
      char *argv[] = {"Wget --no-check-certificate ", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip",  NULL};
      execv("/usr/bin/wget", argv);
    }
  
  while(wait(NULL) > 0);
    child_id = fork();
    if (child_id == 0) {
      char *argv[] = {"unzip", "*.zip", NULL};
      execv("/usr/bin/unzip", argv);
    }

  	while(wait(NULL) > 0);
    child_id = fork();
    	if (child_id == 0) {
    	char *argv[] = {"mv", "MUSIK", "Musyik", NULL};
    	execv("/bin/mv", argv);
    }
	
	while(wait(NULL) > 0);
    child_id = fork();
    	if (child_id == 0) {
    	char *argv[] = {"mv", "FOTO", "Pyoto", NULL};
    	execv("/bin/mv", argv);
    }
	
	while(wait(NULL) > 0);
    child_id = fork();
    	if (child_id == 0) {
    	char *argv[] = {"mv", "FILM", "Fylm", NULL};
    	execv("/bin/mv", argv);
    }

	while(wait(NULL) > 0);
	child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"zip", "-r", " Lopyu_Stevany.zip", "Musyik", "Pyoto", "Fylm", NULL};
        execv("/usr/bin/zip", argv);

    }

	while(wait(NULL) > 0);
    child_id = fork();
    	if (child_id == 0) {
    	char *argv[] = {"rm ", "-r", "Musyik", "Pyoto", "Fylm", NULL};
    	execv("/bin/rm", argv);
    }
	



    sleep(30);
  }
}

