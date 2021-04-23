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

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Incorrect argument\n");
    return 1;
  }
  if (strcmp(argv[1], "-x") != 0 && strcmp(argv[1], "-z") != 0) {
    printf("Incorrect mode(choose -z or -x)\n");
    return 1;
  }

  pid_t pid, sid;        

  pid = fork();    

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }


  FILE *killer;
  killer = fopen("kill.sh", "w");

  if (strcmp(argv[1], "-z") == 0) {
    char *func = "\n"
    "#!/bin/bash\n"
    "/usr/bin/kill -9 \"%d\"\n"
    "/bin/rm kill.sh\n";
    fprintf(killer, func, sid);
  }

  if (strcmp(argv[1], "-x") == 0) {
    char *func = "\n"
    "#!/bin/bash\n"
    "/usr/bin/kill -9 \"%d\"\n"
    "/bin/rm kill.sh\n";
    fprintf(killer, func, getpid());
  }

  fclose(killer);

  pid = fork();
  if (pid == 0) {
    char *argv[] = {"chmod","+x","kill.sh", NULL};
    execv("/bin/chmod", argv);
  }
  while(wait(NULL) != pid);


  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char now[80];
    strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);

    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
      char *argv[] = {"mkdir", now, NULL};
      execv("/bin/mkdir", argv);
    }

    child_id = fork();
    if (child_id == 0) {

      for (int i = 0; i < 10; i++) {

        child_id = fork();
        if (child_id == 0) {

          t = time(NULL);
          tm = localtime(&t);
          char new[80], lokasi[160], link[80];
          strftime(new, 80, "%Y-%m-%d_%H:%M:%S", tm);
          sprintf(lokasi, "%s/%s", now, new);
          sprintf(link, "https://picsum.photos/%ld", ((t%1000)+50));
          char *argv[] = {"wget", "-O", lokasi, link, NULL};
          execv("/usr/bin/wget", argv);

        }

        sleep(5);

      }

    while(wait(NULL) > 0);
    child_id = fork();
    if(child_id == 0){

        char message[20] = "Download Success", ch;
        int i, key = 5;

        for(i = 0; message[i] != '\0'; ++i){
            ch = message[i];
            
            if(ch >= 'a' && ch <= 'z'){
                ch = ch + key;
                
                if(ch > 'z'){
                    ch = ch - 'z' + 'a' - 1;
                }
                
                message[i] = ch;
            }
            else if(ch >= 'A' && ch <= 'Z'){
                ch = ch + key;
                
                if(ch > 'Z'){
                    ch = ch - 'Z' + 'A' - 1;
                }
                
                message[i] = ch;
            }
        }
        FILE  *status;
        char place[] = "/status.txt" ;
        char t[100];
        strcpy(t,now); 
        strcat(t,place);
        status = fopen(t , "w");
        fprintf(status, "%s",  message);
        fclose(status);
    }

      while(wait(NULL) > 0);
      child_id = fork();
      if (child_id == 0) {
        char nama[80];
        sprintf(nama, "%s.zip", now);
        char *argv[] = {"zip", "-r", nama, now, NULL};
        execv("/usr/bin/zip", argv);

      }

      while(wait(NULL) != child_id);
      char *argv[] = {"rm", "-r", now, NULL};
      execv("/bin/rm", argv);

    }
    
    sleep(40);
  }
}
