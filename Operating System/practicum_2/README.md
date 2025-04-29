[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9LcL5VTQ)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221000 | Student 3 Name |

# Praktikum Modul 2 _(Module 2 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - Trabowo & Peddy Movie Night](/task-1/)

- [Task 2 - Organize and Analyze Anthony's Favorite Films](/task-2/)

- [Task 3 - Cella’s Manhwa](/task-3/)

- [Task 4 - Pipip's Load Balancer](/task-4/)

### Laporan Resmi Praktikum Modul 2 _(Module 2 Lab Work Report)_

Tulis laporan resmi di sini!

_Write your lab work report here!_

# task-1 Trabowo & Peddy Movie Night
### a. Ekstraksi File ZIP
```c
    char *filename = "trabowo.zip";
```
> buat string untuk nama file zip yang akan didowndload
```c
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "wget -q -O %s \"https://drive.usercontent.google.com/u/0/uc?id=1nP5kjCi9ReDk5ILgnM7UCnrQwFH67Z9B&export=download\"", filename);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    wait(NULL);
```
> Buat child process baru dengan `fork()` dan jalankan command wget dengan fungsi `execlp()`. Gunakan `wait(NULL)` untuk menunggu process child selesai (memastikan file zip sudah terdownload sebelum melakukan operasi-operasi lainnya) sebelum melanjutkan parent process.\
Jalankan command `wget -q -O <nama_file> <link_download>` untuk mendownload file film. `-q -O` artinya adalah menjalankan `wget` secara quiet dan mendownloadnya dengan nama file yang lain.\
Gunakan string `cmd` dan gunakan `snprintf` untuk melakukan formatting pada string `cmd`.
```c
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "unzip -q %s", filename);
        execlp("sh", "sh", "-c", cmd, NULL);
    }
    wait(NULL);
```
> Buat child process baru dengan `fork()` dan jalankan command `unzip` dengan fungsi `execlp()` untuk melakukan unzip pada file zip yang sudah didownload sebelumnya. Tetap gunakan `wait(NULL)` untuk memastikan file telah terunzip sebelum menghapusnya.\
`unzip -q <nama_file>` untuk menjalankan command unzip dalam quiet mode.
```c
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "rm -rf %s", filename);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
```
> Buat child process baru dengan `fork()` dan jalankan command `rm -rf <nama_file>` untuk menghapus file zip.

Output:\
![task-1 a](Operating%20System/practicum_2/picture/trabowo_a.png)

### b. Pemilihan Film Secara Acak
```c
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "find ./film -maxdepth 1 -type f | shuf -n 1 | awk -F'/' '{ print \"Film for Trabowo & Peddy: \" $3 }'");
    execlp("sh", "sh", "-c", cmd, NULL);
```
> Jalankan command bash dengan fungsi `execlp()`.\
`find ./film -maxdepth 1 -type f`\
untuk mencari file pada directory film dengan maksimal depth 1, artinya tidak akan mencari file dalam subdirectory.\
`shuf -n 1`\
untuk melakukan shufle dan mengambil hanya 1 file saja.\
contoh outputnya: `./film/18_it_horror.jpg`\
`awk -F'/' '{ print \"Film for Trabowo & Peddy: \" $3 }'`\
gunakan awk untuk mengubah formatnya, print string yang ada di soal, lalu $3 karena nama filenya ada di field ke-3 yang dipisahkan oleh delimiter berupa `/`.

Output:\
![task-1 b](Operating%20System/practicum_2/picture/trabowo_b.png)

### c. Memilah Film Berdasarkan Genre
```c
#define NFNAME 64
#define NFILES 50

const char *dirname = "./film";

void mkdir();
void f_list(char files[][NFNAME], int *idx);
void mv_log(char *fname, char *genre, int who);
void f_folder(char files[][NFNAME], int start, int end, int who);
void f_worker(char files[][NFNAME], int idx);
int f_count(char *genre);
void total(int cnt[]);

int main() {
    char files[NFILES][NFNAME];
    int idx = 0, cnt[4] = {0};  // [0]=cnt_horror ; [1]=cnt_animasi ; [2]=cnt_drama ; [3]=cnt_max

    mkdir();
    f_list(files, &idx);
    f_worker(files, idx);

    cnt[0] = f_count("FilmHorror");
    cnt[3] = (cnt[0] > cnt[3]) ? cnt[0] : cnt[3];
    cnt[1] = f_count("FilmAnimasi");
    cnt[3] = (cnt[1] > cnt[3]) ? cnt[1] : cnt[3];
    cnt[2] = f_count("FilmDrama");
    cnt[3] = (cnt[2] > cnt[3]) ? cnt[2] : cnt[3];

    total(cnt);

    return 0;
}
```
> Fungsi `main()` akan memanggil fungsi `mkdir()` terlebih dahulu untuk membuat directory yang diperlukan, lalu memanggil fungsi `f_list()` unduk mendapatkan list file, dan dilanjutkan dengan menjalankan kedua worker untuk memindahkan file ke dalam directory sesuai dengan genrenya. Setelah itu, cari genre dengan jumlah terbanyak, lalu panggil fungsi `total()` untuk membuat file `total.txt`\
Di sini ada 7 fungsi yang masing-masing berfungsi untuk:\
`mkdir()` bukan fungsi dari library di C, fungsi ini gunanya untuk membuat 3 subdirectory dalam directory `./film`. yaitu FilmHorror FilmAnimasi FilmDrama.\
`f_list()` fungsi untuk mendapatkan list file yang terurut berdasarkan nomor film.\
`mv_log` fungsi untuk melakukan pemindahan file dan melakukan logging untuk setiap file yang dipindah.\
`f_folder` fungsi untuk melakukan iterasi pada file dan memilahnya sesuai dengan genre film (memanggil fungsi `mv_log` dengan parameter sesuai genre film).\
`f_worker` fungsi untuk menjalankan 2 worker sekaligus (Peddy dan Trabowo :3).\
`f_count` fungsi untuk menghitung jumlah dari masing-masing genre.\
`total` fungsi untuk membuat file `total.txt`.\

```c
void mkdir() {
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd %s && mkdir -p FilmHorror FilmAnimasi FilmDrama", dirname);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    wait(NULL);
}
```
> Fungsi ini akan menjalankan command  `mkdir` dengan menggunakan `execlp` pada process baru untuk membuat 3 folder yang diminta pada soal, yaitu FilmHorror, FilmAnimasi, dan FilmDrama


```c
void f_list(char files[][NFNAME], int *idx) {
    int fd[2];
    pipe(fd);

    if(fork() == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd %s && ls -1 *.jpg | sort -V", dirname);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    } else {        
        close(fd[1]);
        char buff[NFILES * NFNAME + NFILES];
        ssize_t nbytes = read(fd[0], buff, sizeof(buff) - 1);
        buff[nbytes] = '\0';
        close(fd[0]);

        char *token = strtok(buff, "\n");
        while(token && *idx < NFILES) {
            strncpy(files[(*idx)++], token, NFNAME);
            token = strtok(NULL, "\n");
        }
    }
    wait(NULL);
}
```
> Fungsi ini gunanya untuk mendapatkan list-list nama file yang terurut dan menyimpannya pada sebuah array of string. Cara kerjanya adalah dengan menjalankan command `cd ./film && ls -1 *.jpg | sort -V` pada child process untuk mendapatkan nama-nama file secara terurut berdasarkan nomor versi, lalu pipe hasil outputnya kedalam input dari parent process dengan fungsi `read()`, setelah buffer didapatkan, maka pisahkan ke dalam masing-masing index pada array dengan menggunakan token berupa `\n` yang merepresentasikan baris baru.

```c
void mv_log(char *fname, char *genre, int who) {
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd %s && mv -n %s ./%s", dirname, fname, genre);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    wait(NULL);

    if(fork() == 0) {
        char cmd[512];
        char *name;
        name = (who == 0) ? "Peddy" : "Trabowo";
        snprintf(cmd, sizeof(cmd), "echo \"[$(date +'%%d-%%m-%%Y %%H:%%M:%%S')]\" %s: %s telah dipindahkan ke %s >> recap.txt", name, fname, genre);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    wait(NULL);
}
```
> Fungsi di atas gunanya adalah untuk memindahkan file sekaligus membuat log filenya setelah pemindahan file berhasil dilakukan. Pada fungsi  tersebut terdapat dua process, process pertama akan menjalankan command mv untuk memindahkan file berdasarkan folder genrenya. Setelah memastikan process pertama sudah berjalan secara lancar, process kedua akan menjalankan command untuk membuat log yang akan di append ke file recap.txt. Variable `who` akan merepresentasikan siapa workernya, apakah Peddy atau Trabowo, jika who bernilai 0, maka direpresentasikan sebagai Peddy dan jika who bernilai 1, maka direpresentasikan sebagai Trabowo.

```c
void f_folder(char files[][NFNAME], int start, int end, int who) {
    for (start; start < end; start++) {     
        if(strstr(files[start], "_animasi")) mv_log(files[start], "FilmAnimasi", who);
        else if(strstr(files[start], "_drama")) mv_log(files[start], "FilmDrama", who);
        else if(strstr(files[start], "_horror")) mv_log(files[start], "FilmHorror", who);
    }
}
```
> Fungsi tersebut gunanya untuk melakukan iterasi pada nama-nama files yang akan dipindahkan sekaligus melakukan sortir berdasarkan genrenya yang selanjutnya proses pemindahan dan juga pembuatan log filenya akan dijalankan oleh fungsi `mv_log` sebelumnya. Fungsi ini melakukan iterasi dari start dan end yang berbeda, tergantung dengan workernya, Jika workernya adalah 0 (Peddy), maka dia akan melakukan iterasi dari index 0 sampai dengan setengah dari jumlah files, sedangkan jika workernya adalah 1 (Trabowo), maka dia akan melakukan iterasi dari index tengah sampai akhir.

```c
void f_worker(char files[][NFNAME], int idx) {
    if(fork() == 0) {
        f_folder(files, 0, idx / 2, 0);
        exit(0);
    }
    
    if(fork() == 0) {
        f_folder(files, idx / 2, idx, 1);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
}
```
> Fungsi ini adalah fungsi untuk menjalankan dua worker secara bersamaan, 0 merepresentasikan Peddy, dan 1 merepresentasikan Trabowo.

```c
int f_count(char *genre) {
    int film, fd[2];

    pipe(fd);

    if(fork() == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd %s/%s && ls -1 | wc -l", dirname, genre);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }

    wait(NULL);
    
    char buff[10];
    ssize_t nbytes = read(fd[0], buff, sizeof(buff) - 1);
    buff[nbytes] = '\0';
    film = atoi(buff);
    
    close(fd[0]);
    close(fd[1]);

    return film;
}
```
> Fungsi `f_count()` di atas berfungsi untuk menghitung jumlah film dari masing-masing genre, langkah kerjanya adalah dengan membuat sebuah child process yang akan menjalankan command `cd %s/%s && ls -1 | wc -l` untuk mendapatkan jumlah baris file dari suatu genre. Outputnya tidak akan ditampilkan di terminal, melainkan akan dipipe sebagai input pada parent process yang bisa didapat dengan fungsi `read()`. Setelah mendapat string dari jumlah filmnya, ubah stringnya menjadi integer dengan fungsi `atoi()` dan return hasilnya.

```c
void total(int cnt[]) {
    if(fork() == 0) {
        char genre[NFILES];
        if(cnt[3] == cnt[0]) strcpy(genre, "horror");
        if(cnt[3] == cnt[1]) strcpy(genre, "animasi");
        if(cnt[3] == cnt[2]) strcpy(genre, "drama");
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "echo \"Jumlah film horror: %d\nJumlah film animasi: %d\nJumlah film drama: %d\nGenre dengan jumlah film terbanyak: %s\" > total.txt", cnt[0], cnt[1], cnt[2], genre);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    wait(NULL);
}
```
> Fungsi `total()` akan membuat sebuah file `total.txt` dengan jumlah yang sudah didapatkan dari fungsi `f_count()`. `cnt[3]` adalah index yang menyimpan nilai dari jumlah file terbanyak dari semua genre. `cnt[3]` akan dibandingkan dengan `cnt[2], cnt[1], dan cnt[0]` yang masing-masing indexnya merupakan banyaknya film pada masing-masing genre. Jika `cnt[3]` (maksimum)-nya sesuai dengan salah satu index, maka string `genre[]` akan dicopy dengan nama dari genre yang sesuai.

Output:\
![task-1 c folder](Operating%20System/practicum_2/picture/trabowo_c_folder.png)
![task-1 c recap](Operating%20System/practicum_2/picture/trabowo_c_recap.png)
![task-1 c total](Operating%20System/practicum_2/picture/trabowo_c_total.png)

### d. Pengarsipan Film
```c
int main() {
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd ./film && zip -rq FilmAnimasi.zip ./FilmAnimasi && rm -rf FilmAnimasi");
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }

    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd ./film && zip -rq FilmDrama.zip ./FilmDrama && rm -rf FilmDrama");
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
    
    if(fork() == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd ./film && zip -rq FilmHorror.zip ./FilmHorror && rm -rf FilmHorror");
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }
}
```
> Buat 3 child process yang berjalan secara bersamaan (overlapping) yang mana masing-masing commandnya akan melakukan zip setiap directory pada directory film sesuai dengan genrenya lalu menghapus directory genrenya.

Output:\
![task-1 d](Operating%20System/practicum_2/picture/trabowo_d.png)

# task-3 Cella’s Manhwa
```c
#define MXLINK 4096
#define MXBUFF 2048
#define MXLINE 64
#define MANHWA 4

typedef struct {
    int  rls;
    char lnk[MXBUFF];
    char hrn[MXLINE];
} Waifu;

const char *dirM = "Manhwa";
const char *dirA = "Archive";
const char *dirH = "Heroines";
const char *dirI = "Images";

void make_dir(const char *);
void Summoning_the_Manhwa_Stats(char*, int [MANHWA], char [][MXLINE], char [][MXLINE], int);
void Seal_the_Scrolls(char [][MXLINE], char [][MXLINE]);
void *Making_the_Waifu_Gallery(void *);
void Zip_Save_Goodbye(char *[], char [][MXLINE], char [][MXLINE]);

void make_dir(const char *dir) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s", dir);
    execlp("sh", "sh", "-c", cmd, NULL);
}

int main() {
    char *IDmanhwa[] = {"168827", "147205", "169731", "175521"};
    char *LKmanhwa[] = {
        "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRlmdSSDhJBbCgGHwNfAJVi0rq07v7TXu_nlw&s",
        "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQt7950IuqfQTjUQrWilemifRXTZ_lWDEAFyA&s",
        "https://d1ed0vta5mrb00.cloudfront.net/chapters/753123785/thumbnails/01b8de86-08f9-4075-8091-f7f330f3c191.jpg",
        "https://cdn.anime-planet.com/manga/primary/darling-why-cant-we-divorce-novel-1.jpg?t=1741355035"
    };
    char *HRmanhwa[] = {"Lia", "Artezia", "Adelia", "Ophelia"};
    char FILEname[MANHWA][MXLINE];
    char ZIPname[MANHWA][MXLINE];
    int Release[MANHWA];

    pid_t pid[3];

    pid[0] = fork();
    if(pid[0] == 0) {
        make_dir(dirM);
        exit(0);
    }
    
    pid[1] = fork();
    if(pid[1] == 0) {
        make_dir(dirA);
        exit(0);
    }

    pid[2] = fork();
    if(pid[2] == 0) {
        make_dir(dirH);
        exit(0);
    }

    for (int i = 0; i < 3; i++) {
        waitpid(pid[i], NULL, 0);
    }
        
    for (int i = 0; i < MANHWA; i++) Summoning_the_Manhwa_Stats(IDmanhwa[i], Release, FILEname, ZIPname, i);
    
    Seal_the_Scrolls(FILEname, ZIPname);
    
    pthread_t tid[MANHWA];
    for (int i = 0; i < MANHWA; i++) {
        Waifu *args = malloc(sizeof(*args));
        strncpy(args->lnk, LKmanhwa[i], MXBUFF);
        strncpy(args->hrn, HRmanhwa[i], MXLINE);
        args->rls = Release[i];
        pthread_create(&tid[i], NULL, Making_the_Waifu_Gallery, args);
        pthread_join(tid[i], NULL);
    }

    Zip_Save_Goodbye(HRmanhwa, FILEname, ZIPname);

    return 0;
}
```
> Terdapat array-array yang berfungsi untuk menyimpan nilai dari data-data yang diperlukan untuk fungsi-fungsi pada subtask a-d, index pada semua array merepresentasikan salah satu judul Manhwa, sesuai pada soal.\
index 0 -> Mistaken as the Monster Duke's Wife\
index 1 -> The Villainess Lives Again\
index 2 -> No, I Only Charmed the Princess!\
index 3 -> Darling, Why Can't We Divorce?\
IDmanhwa menyimpan data dari ID manhwa yang nantinya digunakan untuk `curl` ke API, LKmanhwa menyimpan link-link untuk download file gambar dari masing-masing heroine manhwa, HRmanhwa menyimpan nama-nama heroine, FILEname menyimpan nama file dengan format yang sudah ditentukan [judul versi bahasa Inggris (tanpa karakter khusus dan spasi diganti dengan underscore)], ZIPname menyimpan nama file ZIP sesuai dengan format yang sudah ditentukan (diambil dari huruf kapital nama file), Release menyimpan release date dari masing-masing manhwa.\
Selanjutnya, fungsi main akan membuat 3 process baru yang masing-masing berfungsi untuk membuat folder Manhwa, Archive, dan Heroines.\
Setelah ketiga process selesai dijalankan, selanjutnya masuk ke soal A.

### a. Summoning the Manhwa Stats
```c
void Summoning_the_Manhwa_Stats(char *IDcode, int Release[MANHWA], char FILEname[MANHWA][MXLINE], char ZIPname[MANHWA][MXLINE], int indexRelease) {
    char attr[MXLINE][MXLINE];
    int idx = 0, fd[2];
    pipe(fd);

    if(fork() == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "curl -s https://api.jikan.moe/v4/manga/%s | jq -r '.data as $d | \"\\($d.title_english)\n\\($d.status)\n\\($d.published.from | split(\"T\")[0])\", ($d.genres | map(.name) | join(\", \")), ($d.themes | map(.name) | join(\", \")), ($d.authors | map(.name) | join(\", \"))'", IDcode);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    } else {
        close(fd[1]);
        char buff[MXBUFF];
        ssize_t nbytes = read(fd[0], buff, sizeof(buff) - 1);
        buff[nbytes] = '\0';
        close(fd[0]);

        char *token = strtok(buff, "\n");
        while(token && idx < MXLINE) {
            strncpy(attr[idx++], token, MXLINE);
            token = strtok(NULL, "\n");
        }

        int j = 0, k = 0, len = strlen(attr[0]);
        char out[MXLINE], ZIP[MXLINE];
        for (int i = 0; i < len; i++) {
            if(isalnum(attr[0][i])) {
                out[j++] = attr[0][i];
            } else if(attr[0][i] == ' ') {
                out[j++] = '_';
            }
            if(isupper(attr[0][i])) ZIP[k++] = attr[0][i];
        }
        out[j] = '\0';
        ZIP[k] = '\0';

        char tmp[3];
        strncpy(tmp, attr[2] + 5, 2);
        tmp[2] = '\0';
        Release[indexRelease] = atoi(tmp);
        strncpy(FILEname[indexRelease], out, MXLINE);
        strncpy(ZIPname[indexRelease], ZIP, MXLINE);

        if(fork() == 0) {
            char cmd[1024];
            snprintf(cmd, sizeof(cmd), 
            "printf \"Title: %s\\nStatus: %s\\nRelease: %s\\nGenre: %s\\nTheme: %s\\nAuthor: %s\\n\" > ./%s/%s.txt",
            attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], dirM, out);
            execlp("sh", "sh", "-c", cmd, NULL);
            exit(0);
        }
        wait(NULL);
    }
    wait(NULL);
}
```
> Fungsi untuk menjalankan soal A, sebenarnya sekaligus untuk mengambil data-data yang diperlukan ke dalam array yang sudah disebutkan sebelumnya. Cara kerjanya adalah dengan membuat child process yang akan menjalankan command `curl` ke API dan akan dipipe ke command `jq -r '<...>'` untuk melakukan parsing dan mengambil raw datanya tanpa formatting JSON sekaligus memformat ulang outputnya menjadi newline tiap datanya. Contoh output commandnya:\
Darling, Why Can't We Divorce?\
Publishing\
2024-10-02\
Fantasy, Romance\
Isekai, Villainess\
Cha, Sohee, Studio Inus\
Output di atas tidak akan ditampilkan pada terminal, akan tetapi outputnya akan dipipe sebagai input untuk parent process nantinya.\
Pada parent process, sebuah buffer akan mengambil data yang dipipe dari child process dengan fungsi `read()`, hasilnya akan dimasukkan ke dalam array of string yang bernama attr, yang masing-masing indexnya akan menampung masing-masing line dari data seperti contoh di atas. Setelah itu, Untuk mendapatkan FILEname dari masing-masing manhwa, ambil data dari line pertama, yang merupakan judul, dan cek dengan fungsi `isalnum()` untuk menghilangkan special character, dan ganti juga space dengan underscore. Untuk mendapatkan nama ZIPname, cek dengan `isupper()`. Untuk mendapatkan release date, gunakan data dari line ke-3 dan gunakan strncpy untuk mencopy bagian bulannya saja (index ke 5-6), lalu gunakan fungsi `atoi()` untuk mengubah string menjadi integer.\
Setelah semua data penting diambil, maka langkah selanjutnya adalah jalankan tujuan utama dari subtask a ini. Jalankan process baru untuk menjalankan command `printf <...>` untuk memformat ulang data-data pada attr ke dalam format yang diminta soal.

### b. Seal the Scrolls
```c
void Seal_the_Scrolls(char FILEname[MANHWA][MXLINE], char ZIPname[MANHWA][MXLINE]) {    
    for (int i = 0; i < MANHWA; i++) {
        if(fork() == 0) {
            char cmd[512];
            snprintf(cmd, sizeof(cmd), "zip -q ./%s/%s.zip ./%s/%s.txt", dirA, ZIPname[i], dirM, FILEname[i]);
            execlp("sh", "sh", "-c", cmd, NULL);
            exit(0);
        }
        wait(NULL);
    }    
}
```
> Fungsi ini akan membuat process baru untuk masing-masing manhwanya untuk menjalankan perintah `zip` dengan melakukan iterasi menggunakan for-loop.

### c. Making the Waifu Gallery
```c
void *Making_the_Waifu_Gallery(void *args) {
    Waifu *parameter = args;

    char cmdDir[MXBUFF];
    snprintf(cmdDir, sizeof(cmdDir), "cd ./%s && mkdir -p %s && cd ..", dirH, parameter->hrn);
    system(cmdDir);

    for (int i = 1; i <= parameter->rls; i++) {
        char cmd[MXLINK];
        snprintf(cmd, sizeof(cmd), "mkdir -p ./%s/%s && curl -s -o ./%s/%s/%s_%d.jpg \"%s\"", dirH, parameter->hrn, dirH, parameter->hrn, parameter->hrn, i, parameter->lnk);
        system(cmd);
    }

    free(parameter);
    return NULL;
}
```
> Fungsi ini dijalankan dengan menggunakan thread. Akan menjalankan dua command bash, command pertama akan membuat subdirectory pada directory Heroines sesuai dengan nama Heroines dari masing-masing manhwa. Selanjutnya akan menjalankan for loop yang akan berjalan sebanyak release date dari masing-masing manhwa. command yang akan dijalankan adalah `curl -s -o ./Heroines/<nama_heroines>/<nama_heroines_index>.jpg <link_download>` untuk mendownload file gambar heroines.

### d. Zip. Save. Goodbye
```c
void Zip_Save_Goodbye(char *HRmanhwa[], char FILEname[MANHWA][MXLINE], char ZIPname[MANHWA][MXLINE]) {
    for (int i = 0; i < MANHWA; i++) {
        if(fork() == 0) {
            char cmd[512];
            snprintf(cmd, sizeof(cmd), "mkdir -p ./%s/%s && cd %s && zip -q -r ../%s/%s/%s_%s.zip %s", dirA, dirI, dirH, dirA, dirI, ZIPname[i], HRmanhwa[i], HRmanhwa[i]);
            execlp("sh", "sh", "-c", cmd, NULL);
            exit(0);
        }
    }
    for (int i = 0; i < MANHWA; i++) wait(NULL);
    
    for (int i = 0; i < MANHWA; i++) {
        if(fork() == 0) {
            char cmd[512];
            snprintf(cmd, sizeof(cmd), "find ./%s/%s -type f | sort | while read -r file; do rm \"$file\"; done", dirH, HRmanhwa[i]);
            execlp("sh", "sh", "-c", cmd, NULL);
            exit(0);
        }
    }
    for (int i = 0; i < MANHWA; i++) wait(NULL);
}
```
> Fungsi ini akan melakukan iterasi untuk setiap manhwa, pada for loop pertama, akan membuat process-process yang akan menjalankan command untuk membuat subdirectory Images jika belum ada dan melakukan `zip -q -r <nama_zip> <nama_folder>` untuk zip file dalam mode quiet dan secara rekursif. Setelah semua process zip selesai, maka lakukan iterasi lagi pada for loop kedua untuk menghapus file-file pada folder Heroines secara terurut dengan abjad, masing-masing iterasi akan menjalankan command `find ./Heroines/<nama_heroines> -type f | sort | while read -r file; do rm "$file\; done`. Command tersebut akan mencari file dalam directory `./Heroines/<nama_heroines>` dan akan disort berdasarkan abjad, lalu outputnya dipipe ke while loop yang akan membaca masing-masing linenya dan menghapusnya satu-persatu.

Output:\
![task-3 solver](Operating%20System/practicum_2/picture/solver.png)
![task-3 solver manhwa](Operating%20System/practicum_2/picture/solver_manhwa.png)