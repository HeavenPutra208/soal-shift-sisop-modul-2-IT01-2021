# soal-shift-sisop-modul-2-IT06-2021
Penyelesaian Soal Shift 2 Sistem Operasi 2021\
Kelompok IT06
* Alessandro Tionardo (05311940000018)
* Heaven Happyna P F (0531940000026)
* Zuhairaja M T (05311940000033)

---
## Daftar Isi
* [Soal 1](#soal-1)
  * [Soal 1.a.](#soal-1a)
  * [Soal 1.b.](#soal-1b)
  * [Soal 1.c.](#soal-1c)
  * [Soal 1.d.](#soal-1d)
  * [Soal 1.e.](#soal-1e)
  * [Soal 1.f.](#soal-1f)
* [Soal 2](#soal-2)
  * [Soal 2.a.](#soal-2a)
  * [Soal 2.b.](#soal-2b)
  * [Soal 2.c.](#soal-2c)
  * [Soal 2.d.](#soal-2d)
  * [Soal 2.e.](#soal-2e)
* [Soal 3](#soal-3)
  * [Soal 3.a.](#soal-3a)
  * [Soal 3.b.](#soal-3b)
  * [Soal 3.c.](#soal-3c)
  * [Soal 3.d.](#soal-3d)
  * [Soal 3.e.](#soal-3e)
---

## Soal 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. 

Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.
### Soal 1.a
Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.

**Penyelesaian**\
Mula-mula, kami menentukan library yang kami gunakan, yaitu sebagai berikut:
```c
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
```

Kemudian, kami membuat ketiga folder yang diinginkan, yaitu `Musyik`, `Fylm`, dan `Pyoto` berupa `child process`:
```c
  if (child_id == 0) {
    char *argv[] = {"mkdir", "Musyik", "Fylm", "Pyoto",  NULL};
    execv("/bin/mkdir", argv);
  }
```
### Soal 1.b
untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga

**Penyelesaian**\
Setelah ketiga folder dibuat pada soal 1a, kemudian kami membuat code untuk mendownload zip yang disediakan pada gdrive dengan bantuan pointer arr `*argv[]` yang menggunakan format downloading yang disediakan (`wget --no-check-certificate "https://drive.google.com/uc?id=**ID-FILE**&export=download" -O **Nama_untuk_filenya.ext**`). Agar satu-persatu, maka untuk file foto dan film diberikan fungsi wait `((wait(&status)) > 0)`

```c
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
```

### Soal 1.c
Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload

**Penyelesaian**\
Untuk mengekstrak file zip yang telah didownload sebelumnya, maka di sini digunakan bantuan pointer arr `*argv[]` dengan perintah `unzip`:

```c
while(wait(NULL) > 0);
    child_id = fork();
    if (child_id == 0) {
      char *argv[] = {"unzip", "*.zip", NULL};
      execv("/usr/bin/unzip", argv);
    }
```

### Soal 1.d
memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

**Penyelesaian**\
Setelah file diunzip, kemudian hasil nya dimasukkan ke dalam masing-masing folder sesuai bentuk filenya():

```c
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
```

### Soal 1.e
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).

**Penyelesaian**\
Di sini kami menggunakan fungsi `localtime(&t)` untuk mendapatkan waktu sekarang, lalu kami menggunakan fungsi `strcmp` untuk mengecek apakah waktu sekarang sama dengan waktu 6 jam sebelum ulang tahun Stevany.\

```c
    while (1) {

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char now[80];
        strftime(now, 80, "%Y-%m-%d %H:%M:%S", tm);
        if(strcmp(now,"2021-04-09 16:22:00") == 0)
```

### Soal 1.f
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).

**Penyelesaian**\
Di sini kami menggunakan fungsi `localtime(&t)` untuk mendapatkan waktu sekarang, lalu kami menggunakan fungsi `strcmp` untuk mengecek apakah waktu sekarang sama dengan waktu  ulang tahun Stevany.\
```c
    while (1) {

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char now[80];
        strftime(now, 80, "%Y-%m-%d %H:%M:%S", tm);
        if(strcmp(now,"2021-04-09 22:22:00") == 0)
```

Dimisalkan sudah waktu ulang tahun Stevany, maka folder-folder yang dibuat Steven dimasukkan jadi satu sekaligus di zip dengan code berikut:
```c
	while(wait(NULL) > 0);
	child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"zip", "-r", " Lopyu_Stevany.zip", "Musyik", "Pyoto", "Fylm", NULL};
        execv("/usr/bin/zip", argv);
```

Dan semua folder-folder selain Lopyu_Stevany.zip akan didelete dengan `rm`:
```c
	while(wait(NULL) > 0);
    child_id = fork();
    	if (child_id == 0) {
    	char *argv[] = {"rm ", "-r", "Musyik", "Pyoto", "Fylm", NULL};
    	execv("/bin/rm", argv);
    }
```

### Screenshot
**Hasil Running Code**

<br>
<img height="500" src="https://github.com/HeavenPutra208/soal-shift-sisop-modul-2-IT06-2021/blob/main/img/no1-1.png" />
<br>
<br>
<img height="500" src="https://github.com/HeavenPutra208/soal-shift-sisop-modul-2-IT06-2021/blob/main/img/no1-2.png" />
<br>

### Kendala
* Kebingungan dalam mengeksekusi code yang diinginkan pada waktu spesifik

## Soal 2
### Kendala
* Kebingungan menentukan syntax yang sesuai untuk menghapus folder-folder yang tidak penting
* Kebingungan syntax dalam pengklasifikasian hewan-hewan ke folder yang sesuai
* Kebingungan membuat file .txt yang menyantumkan nama dan umur setiap hewan

## Soal 3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

### Soal 3.a.
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

**Penyelesaian**\
Untuk menyelesaikan 3a, kami mula-mula terpikirkan untuk membuat C program berupa daemon. Sebelumnya, kami memasukkan beberapa library daemon yang diperlukan. Beberapa library yang kami gunakan adalah:

```c
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
```

Lalu, kami menggunakan format template daemon yang disediakan di modul (kecuali branch if chdir). Nantinya, semua program akan dimasukkan ke dalam fungsi `main()`. Untuk mengatur pembuatan direktori setiap 40 detik, maka nilai 'sleep()' diubah menjadi 'sleep(40)'.

```c
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

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {

    sleep(40);
  }
}
```

Kemudian, kami mendeklarasikan variabel awal sebagai berikut:
```c
time_t t = time(NULL);
struct tm *tm = localtime(&t);
char now[80];
```

Kemudian, dideklarasikan juga code strftime sebagai formatting direktori yang diinginkan:
```c
strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);
```

Lalu baru dibuat sebuah direktori:
```
pid_t child_id;
child_id = fork();

if (child_id == 0) {
  char *argv[] = {"mkdir", now, NULL};
  execv("/bin/mkdir", argv);
}
```

Lalu, process akan di `fork()` dan *child process* akan melakukan `execv()` terhadap perintah `mkdir` dengan *argument* `now`. Sementara *parent process* tidak akan menunggu child process dan akan langsung `sleep()` selama 40 detik.
### Soal 3.b.
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

**Penyelesaian**\
Setelah membuat direktori pada soal 3a, pada 3b kami membuat child process untuk mendownload 10 gambar, di mana program main nya tidak menunggu 10 gambar terdownload dan langsung `sleep(40)`/sleep selama 40 detik setelah fungsi `fork()` berjalan. Pada picsum photos, kita dapat mengatur format pixel gamabar dengan memodifikasi link dengan format `(t%1000)+50)`.

```c
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
```

Child process/downloading gambar akan ter looping sebanyak 10 kali dan melakukan `sleep()` setiap 5 detik.

### Soal 3.c.
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

**Penyelesaian**\
Di sini, setelah child process dari soal 3b. selesai berjalan, maka kami meneruskan program dengan membuat file bernama `status.txt`:

```c
while(wait(NULL) > 0);
    child_id = fork();
    if(child_id == 0){

        char message[20] = "Download Success", ch;
        int i, key = 5;
        
... // program caesar cipher

       FILE  *status;
       char place[] = "/status.txt" ;
       char t[100];
       strcpy(t,now); 
       strcat(t,place);
       status = fopen(t , "w");
       fprintf(status, "%s",  message);
       fclose(status);
    }
```

Mengikuti permintaan soal, maka kami menyisipkan kode algoritma caesar cipher untuk mengenkripsi kalimat "download success". Berikut adalah algoritma caesar cipher yang kami gunakan:

```c
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
```

Setelah itu, kami melakukan zip terhadap folder yang ada, baru kemudian menghapus folder tersebut (Child process akan melakukan zip terhadap folder dan parent process akan menunggu child process selesai dan menghapus directory folder yang telah di zip):
```c
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
```

### Soal 3.d.
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

**Penyelesaian**\
Mula-mula, kami membuat sebuah file baru bernama `killer.c` (Deklarasi file ini dilakukan sebelum bagian loop utama daemon dan setelah mendapatkan **Session ID** (`sid`)):

```c
FILE *killer;
killer = fopen("killer.c", "w");
```

Selanjutnya, kami mendeklarasikan sebuah variabel `func` yang berisi program yang akan kami masukkan pada file `killer.c`. Lalu file `killer.c` akan kami inputkan dengan string yang sesuai untuk melakukan perintah `pkill` sesuai dengan ***Session ID*** (`sid`) dari program utama (Penggunaan ***Session ID*** agar seluruh *child process* juga ikut di **kill** melalui perintah `pkill`).\

```c
char *func = ""
    "#include <unistd.h>\n"
    "#include <wait.h>\n"
    "int main() {\n"
      "pid_t child_id = fork();\n"
      "if (child_id == 0) {\n"
        "char *argv[] = {\"pkill\", \"-9\", \"-s\", \"%d\", NULL};\n"
        "execv(\"/usr/bin/pkill\", argv);\n"
      "}\n"
      "while(wait(NULL) > 0);\n"
      "char *argv[] = {\"rm\", \"killer\", NULL};\n"
      "execv(\"/bin/rm\", argv);\n"
    "}\n";
    fprintf(killer, func, sid);
```

Lalu program killer tersebut akan menghapus dirinya sendiri. Cara tersebut dapat dilakukan dengan melakukan `fork()` dimana *child process* akan melakukan `killer` dan *parent process* akan menunggu *child process* dan melakukan `rm`. Lalu string tersebut diwrite kedalam `killer` dengan fungsi `fprintf()`. Lalu pointer file `killer` akan ditutup koneksinya menggunakan fungsi fclose().

```c
 fclose(killer);
```

Kemudian, program utama akan membuat child process untuk melakukan compile terhadap file killer.c menggunakan perintah gcc. Setelah itu program utama akan membuat child process kembali untuk melakukan remove terhadap file killer.c menggunakan perintah rm.

```c
pid = fork();
  if (pid == 0) {
    char *argv[] = {"gcc", "killer.c", "-o", "killer", NULL};
    execv("/usr/bin/gcc", argv);
  }
  while(wait(NULL) != pid);

  pid = fork();
  if (pid == 0) {
    char *argv[] = {"rm", "killer.c", NULL};
    execv("/bin/rm", argv);
  }
```

### Soal 3.e.
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

**Penyelesaian**\
Karena ada 2 mode, maka kami menggunakan `strcmp` untuk menyesuaikan format argumen yang dijalankan pada terminal. Argumen -z menggunakan format `fprintf(killer, func, sid)` untuk memberhentikan semua proses. Sedangkan, argumen -x menggunakan format `fprintf(killer, func, sid)` untuk memberhentikan program utama, namun proses di folder masih berjalan:

```c
  if (strcmp(argv[1], "-z") == 0) {
    char *func = ""
    "#include <unistd.h>\n"
    "#include <wait.h>\n"
    "int main() {\n"
      "pid_t child_id = fork();\n"
      "if (child_id == 0) {\n"
        "char *argv[] = {\"pkill\", \"-9\", \"-s\", \"%d\", NULL};\n"
        "execv(\"/usr/bin/pkill\", argv);\n"
      "}\n"
      "while(wait(NULL) > 0);\n"
      "char *argv[] = {\"rm\", \"killer\", NULL};\n"
      "execv(\"/bin/rm\", argv);\n"
    "}\n";
    fprintf(killer, func, sid);
  }

  if (strcmp(argv[1], "-x") == 0) {
    char *func = ""
    "#include <unistd.h>\n"
    "#include <wait.h>\n"
    "int main() {\n"
      "pid_t child_id = fork();\n"
      "if (child_id == 0) {\n"
        "char *argv[] = {\"kill\", \"-9\", \"%d\", NULL};\n"
        "execv(\"/bin/kill\", argv);\n"
      "}\n"
      "while(wait(NULL) > 0);\n"
      "char *argv[] = {\"rm\", \"killer\", NULL};\n"
      "execv(\"/bin/rm\", argv);\n"
    "}\n";
    fprintf(killer, func, getpid());
  }
```
### Screenshot
**Menggunakan argumen -z**
<br>
<img height="300" src="https://github.com/HeavenPutra208/soal-shift-sisop-modul-2-IT06-2021/blob/main/img/no3e-1.png" />
<br>
**Menggunakan argumen -x**
<br>
<img height="300" src="https://github.com/HeavenPutra208/soal-shift-sisop-modul-2-IT06-2021/blob/main/img/no3e-2.png" />
<br>
**Tidak Menggunakan argumen**
<br>
<img height="300" src="https://github.com/HeavenPutra208/soal-shift-sisop-modul-2-IT06-2021/blob/main/img/no3e-3.jpg" />
<br>
### Kendala
* Perlu memodifikasi sedikit pada format daemon yang ada pada modul
