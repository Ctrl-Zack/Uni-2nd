#include "console_menu.h"
#include "database_menu.h"

const char *file_name = "bin/database.bin";

const char *db_title = "\e[1mDATA STRUCTURE FINAL PROJECT\e[0m";
const int8_t menu_count = 6;
const char *menu_list[] = {
    " \e[4mM\e[24menambah data                       ",
    " Meng\e[4mu\e[24mbah data                       ",
    " Menampilkan semua data dengan inde\e[4mx\e[24m ",
    " Menampilkan semua data \e[4mt\e[24manpa index  ",
    " \e[4mH\e[24mapus data                          ",
    " \e[4mK\e[24meluar                              "
};

const char *add_title = "Pilih Opsi Tambah Data";
const int8_t add_op_count = 3;
const char *add_option[] = {
    "Generate nomor otomatis    ",
    "Input nomor manual         ",
    "Kembali                    "
};
