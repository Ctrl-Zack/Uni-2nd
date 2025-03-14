/*
# Task
    Buatlah program menu yang berisi data-data KTP penduduk yang
    disimpan dalam array struct 1 dimensi dan dapat dilakukan
    penambahan data, pencarian data, penampilan data dan
    penghapusan data.

    Create a menu program that contains resident ID card data that
    is stored in a 1-dimensional struct array and can be used
    to add data, search for data, display data and delete data.
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILENAME "database_ktp.txt"
#define MAX_DATA 256
#define NIK_LEN 16
#define NAME_LEN 60
#define ADMINISTRATIVE_LEN 64
#define ADDRESS_LEN 128
#define RELIGION_LEN 18
#define JOB_LEN 32

typedef struct {
    unsigned short day;
    unsigned short month;
    unsigned short year;
} Date;

typedef struct {
    unsigned short RT;
    unsigned short RW;
    char village[ADMINISTRATIVE_LEN + 1];
    char district[ADMINISTRATIVE_LEN + 1];
    char Addr[ADDRESS_LEN + 1];
} Address;

typedef struct {
    char NIK[NIK_LEN + 1];
    char full_name[NAME_LEN + 1];
    char gender;
    char blood_type[4];
    char place_of_birth[ADMINISTRATIVE_LEN + 1];
    Date date_of_birth;
    Address address;
    char religion[RELIGION_LEN + 1];
    char marital_status[16];
    char job[JOB_LEN + 1];
} KTP;

void prompt(KTP data[], short *record_count);
void load_data(KTP data[], short *record_count);
void save_database(const KTP data[], const short *record_count);
void display(const KTP data[], const short record_count);
void display_specific_record(const KTP data[], const short record_line);
void create(short *record_count);
void delete(KTP data[], short *record_count);
short find_data_line(const char* NIK);

int main() {
    KTP citizen_data[MAX_DATA];
    short record_count;
    load_data(citizen_data, &record_count);
    prompt(citizen_data, &record_count);
    return 0;
}

void prompt(KTP data[], short *record_count) {
    char prt;
    
    do {
        printf("\033[H\033[J");
        puts("+----------------------------+");
        puts("|          MENU KTP          |");
        puts("+----------------------------+");
        puts("| 1. Tambah Data             |");
        puts("| 2. Cari Data               |");
        puts("| 3. Tampilkan Data          |");
        puts("| 4. Hapus Data              |");
        puts("| 5. Keluar                  |");
        puts("+----------------------------+");
        
        scanf(" %c", &prt);
        switch(prt) {
            case '1':
            create(record_count);
            load_data(data, record_count); // re-load database
            break;
            case '2':
            char NIK[NIK_LEN + 1];
            puts("Masukkan NIK dari data yang ingin dicari: ");
            scanf(" %16s", NIK);
            short data_line = find_data_line(NIK);
            display_specific_record(data, data_line);
            load_data(data, record_count); // re-load database
            break;
            case '3':
            display(data, *record_count);
            load_data(data, record_count); // re-load database
            break;
        case '4':
            delete(data, record_count);
            load_data(data, record_count); // re-load database
            break;
        default:
            break;
        }
    } while(prt != '5');
}

void load_data(KTP data[], short *record_count) {
    *record_count = 0;

    FILE *db = fopen(DATABASE_FILENAME, "r+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    char buffer[1024];
    const char tok[2] = ",";
    char *token;
    char *endPtr;
    
    while(fgets(buffer, 1024, db) != NULL) {
        // NIK
        token = strtok(buffer, tok);
        strcpy(data[*record_count].NIK, token);
        
        // full_name
        token = strtok(NULL, tok);
        strncpy(data[*record_count].full_name, token, NAME_LEN);
        
        // place_of_birth
        token = strtok(NULL, tok);
        strncpy(data[*record_count].place_of_birth, token, ADMINISTRATIVE_LEN);
        
        // date_of_birth
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.day = (unsigned short)strtold(token, &endPtr);
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.month = (unsigned short)strtold(token, &endPtr);
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.year = (unsigned short)strtold(token, &endPtr);
        
        // gender
        token = strtok(NULL, tok);
        data[*record_count].gender = *token;
        
        // blood type
        token = strtok(NULL, tok);
        strncpy(data[*record_count].blood_type, token, 3);
        
        // address
        token = strtok(NULL, tok);
        strncpy(data[*record_count].address.Addr, token, ADDRESS_LEN);
        token = strtok(NULL, tok);
        data[*record_count].address.RT = (unsigned short)strtod(token, &endPtr);
        token = strtok(NULL, tok);
        data[*record_count].address.RW = (unsigned short)strtod(token, &endPtr);
        token = strtok(NULL, tok);
        strncpy(data[*record_count].address.village, token, ADMINISTRATIVE_LEN);
        token = strtok(NULL, tok);
        strncpy(data[*record_count].address.district, token, ADMINISTRATIVE_LEN);        
        
        // religion
        token = strtok(NULL, tok);
        strncpy(data[*record_count].religion, token, RELIGION_LEN);
        
        // marital status
        token = strtok(NULL, tok);
        strncpy(data[*record_count].marital_status, token, 15);
        
        // job
        token = strtok(NULL, tok);
        strncpy(data[*record_count].job, token, JOB_LEN);
        
        
        (*record_count)++;
    }

    fclose(db);
}

void save_database(const KTP data[], const short *record_count) {
    FILE *db = fopen(DATABASE_FILENAME, "w+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    // print updated data to the database
    for(short i = 0; i < *record_count; i++) {
        fprintf(db, "%s,%s,%s,%hi,%hi,%hi,%c,%s,%s,%hi,%hi,%s,%s,%s,%s,%s\n",
            data[i].NIK,
            data[i].full_name,
            data[i].place_of_birth,
            data[i].date_of_birth.day,
            data[i].date_of_birth.month,
            data[i].date_of_birth.year,
            data[i].gender,
            data[i].blood_type,
            data[i].address.Addr,
            data[i].address.RT,
            data[i].address.RW,
            data[i].address.village,
            data[i].address.district,
            data[i].religion,
            data[i].marital_status,
            data[i].job
        );
    }
    
    fclose(db);
}

void display(const KTP data[], const short record_count) { 
    printf("\033[H\033[J");
    for(short i = 0; i < record_count; i++) {    
        puts("============================================");
        printf("%hi)\n\tNIK: %s\n\tNama Lengkap: %s\n\tTTL: %s,%hi-%hi-%hi\n\tJenis Kelamin: %c,\tGolongan Darah: %s\n\tAlamat: %s\n\tRT/RW: %hi/%hi\n\tKel/Desa: %s\n\tKecamatan: %s\n\tAgama: %s\n\tStatus Pernikahan: %s\n\tPekerjaan: %s\n",
            i + 1,
            data[i].NIK,
            data[i].full_name,
            data[i].place_of_birth,
            data[i].date_of_birth.day,
            data[i].date_of_birth.month,
            data[i].date_of_birth.year,
            data[i].gender,
            data[i].blood_type,
            data[i].address.Addr,
            data[i].address.RT,
            data[i].address.RW,
            data[i].address.village,
            data[i].address.district,
            data[i].religion,
            data[i].marital_status,
            data[i].job
        );
        puts("============================================");
    }
    
    printf("Total : %hi records\n", record_count);
    puts("Press any key to go back to the main menu...");
    getch();
}

void display_specific_record(const KTP data[], const short record_line) {
    printf("\033[H\033[J");
    puts("============================================");
    printf("\tNIK: %s\n\tNama Lengkap: %s\n\tTTL: %s,%hi-%hi-%hi\n\tJenis Kelamin: %c,\tGolongan Darah: %s\n\tAlamat: %s\n\tRT/RW: %hi/%hi\n\tKel/Desa: %s\n\tKecamatan: %s\n\tAgama: %s\n\tStatus Pernikahan: %s\n\tPekerjaan: %s\n",
        data[record_line].NIK,
        data[record_line].full_name,
        data[record_line].place_of_birth,
        data[record_line].date_of_birth.day,
        data[record_line].date_of_birth.month,
        data[record_line].date_of_birth.year,
        data[record_line].gender,
        data[record_line].blood_type,
        data[record_line].address.Addr,
        data[record_line].address.RT,
        data[record_line].address.RW,
        data[record_line].address.village,
        data[record_line].address.district,
        data[record_line].religion,
        data[record_line].marital_status,
        data[record_line].job
    );
    puts("============================================");
    
    puts("Press any key to go back to the main menu...");
    getch();
}


void create(short *record_count) {
    printf("\033[H\033[J");
    
    (*record_count)++;
    if(*record_count >= MAX_DATA) {
        (*record_count)--;
        puts("Kapasitas database penuh.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }
    
    KTP newRecord = {0};
    
    puts("Buat Data KTP Baru.");
    
    // NIK
    printf("NIK: ");
    scanf(" %s", newRecord.NIK);
    newRecord.NIK[NIK_LEN] = '\0';
    if(find_data_line(newRecord.NIK) != -1) {
        puts("NIK sudah terdaftar.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }
    
    // full name
    printf("Nama Lengkap: ");
    scanf(" %[^\n]s", newRecord.full_name);
    newRecord.full_name[NAME_LEN] = '\0';
    
    // Place of birth
    printf("Tempat Lahir: ");
    scanf(" %[^\n]s", newRecord.place_of_birth);
    newRecord.place_of_birth[ADMINISTRATIVE_LEN] = '\0';
    
    // Date of birth
    printf("Tanggal Lahir: (D-M-Y)\n");
    scanf(" %hi-%hi-%hi", &newRecord.date_of_birth.day, &newRecord.date_of_birth.month, &newRecord.date_of_birth.year);
    
    // gender
    do {
        printf("Jenis Kelamin: (M/F)\n");
        scanf(" %c", &newRecord.gender);
    } while (newRecord.gender != 'M' && newRecord.gender != 'm' && newRecord.gender != 'F' && newRecord.gender != 'f');
    
    
    // blood type
    unsigned short blood_type_num;
    do {
        printf("Golongan darah: (1-8)\n1) A+\n2) B+\n3) AB+\n4) O+\n5) A-\n6) B-\n7) AB-\n8) O-\n");
        scanf(" %hi", &blood_type_num);
    } while (blood_type_num < 1 || blood_type_num > 8);
    
    switch (blood_type_num) {
        case 1:
        strcpy(newRecord.blood_type, "A+");
        break;
        case 2:
        strcpy(newRecord.blood_type, "B+");
        break;
        case 3:
        strcpy(newRecord.blood_type, "AB+");
        break;
        case 4:
        strcpy(newRecord.blood_type, "O+");
        break;
        case 5:
        strcpy(newRecord.blood_type, "A-");
        break;
        case 6:
        strcpy(newRecord.blood_type, "B-");
        break;
        case 7:
        strcpy(newRecord.blood_type, "AB-");
        break;
        case 8:
        strcpy(newRecord.blood_type, "O-");
        break;
        default:
        break;
    }
    
    // address
    printf("Alamat: ");
    scanf(" %[^\n]s", newRecord.address.Addr);
    newRecord.address.Addr[ADDRESS_LEN] = '\0';
    
    // rt
    printf("RT: ");
    scanf(" %hi", &newRecord.address.RT);
    
    // rw
    printf("RW: ");
    scanf(" %hi", &newRecord.address.RW);
    
    // village
    printf("Kel/Desa: ");
    scanf(" %[^\n]s", newRecord.address.village);
    newRecord.address.village[ADMINISTRATIVE_LEN] = '\0';
    
    // district
    printf("Kecamatan: ");
    scanf(" %[^\n]s", newRecord.address.district);
    newRecord.address.district[ADMINISTRATIVE_LEN] = '\0';
    
    // religion
    printf("Agama: ");
    scanf(" %[^\n]s", newRecord.religion);
    newRecord.religion[RELIGION_LEN] = '\0';
    
    // marital status
    unsigned short marital_status_num;
    do {
        printf("Status Pernikahan: (1-4)\n1) Belum Kawin\n2) Kawin\n3) Cerai Hidup\n4) Cerai Mati\n");
        scanf(" %hi", &marital_status_num);
    } while (marital_status_num < 1 || marital_status_num > 4);
    
    switch (marital_status_num) {
        case 1:
        strcpy(newRecord.marital_status, "Belum Kawin");
        break;
        case 2:
        strcpy(newRecord.marital_status, "Kawin");
        break;
        case 3:
        strcpy(newRecord.marital_status, "Cerai Hidup");
        break;
        case 4:
        strcpy(newRecord.marital_status, "Cerai Mati");
        break;
        default:
        break;
    }
    
    // job
    printf("Pekerjaan: ");
    scanf(" %[^\n]s", newRecord.job);
    newRecord.job[JOB_LEN] = '\0';
    
    FILE *db = fopen(DATABASE_FILENAME, "a+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    // append new record to the database
    fprintf(db, "%s,%s,%s,%hi,%hi,%hi,%c,%s,%s,%hi,%hi,%s,%s,%s,%s,%s\n",
        newRecord.NIK,
        newRecord.full_name,
        newRecord.place_of_birth,
        newRecord.date_of_birth.day,
        newRecord.date_of_birth.month,
        newRecord.date_of_birth.year,
        newRecord.gender,
        newRecord.blood_type,
        newRecord.address.Addr,
        newRecord.address.RT,
        newRecord.address.RW,
        newRecord.address.village,
        newRecord.address.district,
        newRecord.religion,
        newRecord.marital_status,
        newRecord.job
    );
    
    fclose(db);
}


void delete(KTP data[], short *record_count) {
    char NIK[NIK_LEN + 1];
    
    printf("\033[H\033[J");
    puts("Hapus Data KTP.");
    printf("Masukkan NIK dari data yang akan dihapus: ");
    scanf("%s", NIK);

    short record_line = find_data_line(NIK);

    if(record_line == -1) {
        puts("NIK tidak ditemukan.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    display_specific_record(data, record_line);

    // update all records index
    for (int i = record_line; i < *record_count - 1; i++) {
        data[i] = data[i + 1];
    }
    
    (*record_count)--;
    save_database(data, record_count);

    puts("Data berhasil dihapus.");
    puts("Press any key to go back to the main menu...");
    getch();
}

short find_data_line(const char* NIK) {
    short record_line = 0;
    
    FILE *db = fopen(DATABASE_FILENAME, "r+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    char buffer[1024];
    const char tok[2] = ",";
    char *token;

    while(fgets(buffer, 1024, db) != NULL) {
        token = strtok(buffer, tok);
        if(strcmp(token, NIK) == 0) {
            fclose(db);
            return record_line;
        }
        record_line++;
    }

    fclose(db);
    return -1;
}