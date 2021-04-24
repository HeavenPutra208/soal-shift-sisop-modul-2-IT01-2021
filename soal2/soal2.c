#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>

pid_t child_id;
int status;

void mkfolder(char *nama){

    char hewan[20];
    sprintf(hewan, "%s", nama);
	child_id = fork();
    if (child_id == 0) {
	    while ((wait(&status)) > 0);
        char *argv[] = {"mkdir", hewan, NULL};
        execv("/bin/mkdir", argv);
    }

}

void move(char *fold, char *nama, char *reg){
    
    char hewan[20];
    sprintf(hewan, "%s", fold);
    char *name[20];
    sprintf(name, "%s.jpg", nama);
    char *regular[100];
    sprintf(regular, "%s", reg);

    while ((wait(&status)) > 0);
    child_id = fork();
    if (child_id == 0) {
    	char *argv[] = {"mv", regular, name, NULL};
    	execv("/bin/mv", argv);
    }

	while ((wait(&status)) > 0);
    child_id = fork();
    if (child_id == 0) {
    	char *argv[] = {"mv", name, hewan, NULL};
    	execv("/bin/mv", argv);
    }

}

void detail(char *fold, char *nama, char *umur){
    while ((wait(&status)) > 0);
    child_id = fork();
    if (child_id == 0) {
        FILE  *keterangan;
        char t[100];
        sprintf(t, "%s/keterangan.txt", fold);
        keterangan = fopen(t , "a");
        fprintf(keterangan, "nama : %s\numur : %s\n\n", nama, umur);
        fclose(keterangan);
        exit(EXIT_SUCCESS);
    }
}

void input(char *nama){

  char regular[100];
  sprintf(regular, "%s", nama);
  DIR *dir = opendir(nama);
  char *cek;
  char *ket[3];
  int i;
  cek = strtok (nama,"_;");
  while (cek != NULL)
  {
      for ( i = 0; i < 3; i++)
      {
        ket[i] = cek;
        cek = strtok (NULL, "_;");
      }
    char *folder = ket[0];
    char *nama = ket[1];
    char *age = ket[2];
    char *umur = strtok(age, ".");

    mkfolder(folder);
    move(folder, nama, regular);
    detail(folder, nama, umur);
  }
  closedir(dir);
}

int main(){

    chdir("/home/aless/modul2/");

    child_id = fork();
    if (child_id == 0) {
    char *argv[] = {"unzip", "pets.zip", "-d", "petshop", NULL};
    execv("/usr/bin/unzip", argv);
    }

    // Buat baca directory
    struct dirent *dp;
    // Ngebuka directory
    DIR *dir = opendir("petshop");

    if (!dir) {
        exit(EXIT_FAILURE);
    }

    chdir("petshop");

    while(wait(NULL) > 0);
    child_id = fork();
        if (child_id == 0) {
        char *argv[] = {"rm ", "-r", "apex_cheats", "musics", "unimportant_files", NULL};
        execv("/bin/rm", argv);
    }    

    while(wait(NULL) > 0);
    while (dp = readdir(dir)) {
        if (strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0) {
            input(dp->d_name);
        }
    }

    return 0;
    
}
