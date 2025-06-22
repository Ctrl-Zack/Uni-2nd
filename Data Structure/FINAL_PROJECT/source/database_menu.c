#include "database_menu.h"


void saveData(DataKomponen d)
{
    FILE* fp = fopen(file_name, "ab+");
    if (!fp)
    {
        perror("Failed to open file");
        return;
    }

    fwrite(&d, sizeof(DataKomponen), 1, fp);
    
    fclose(fp);
}

void rewriteFile(FILE *fp, AVLNode *root)
{
    if (!root) return;
    rewriteFile(fp, root->left);
    fwrite(&root->data, sizeof(DataKomponen), 1, fp);
    rewriteFile(fp, root->right);
}

void syncFile(AVLNode *root)
{
    FILE* fp = fopen(file_name, "wb+");
    if (!fp) {
        perror("Failed to rewrite file");
        return;
    }
    
    rewriteFile(fp, root);
    
    fclose(fp);
}

void loadDatabase(AVL *records)
{
    FILE *fp = fopen(file_name, "rb+");
    if (!fp)
    {
        perror("Error loading database");
        return;
    }

    DataKomponen d;

    while (fread(&d, sizeof(DataKomponen), 1, fp)) avl_insert(records, d);

    fclose(fp);
}

void tambahData(AVL *records)
{
    clearScreen();
    printf("%s%s Tambah Data %s\n", C_BOLD, C_HIGHLIGHT, C_RESETATTR);
    
    DataKomponen newData;
    
    int8_t selected_add_option = -1;
    consoleMenu(add_option, add_op_count, &selected_add_option, add_title);
    generalConsoleInput(add_option, add_op_count, &selected_add_option, add_title);
    
    clearScreen();
    showCursor();
    if (selected_add_option == 0)
    {
        char nomor_buffer[MAX_NOKOMPONEN + 1];
        printf("Generate nomor otomatis\n");
        generateNextNumber(records, nomor_buffer);
        snprintf(newData.nomor, sizeof(newData.nomor), nomor_buffer);
    }
    else if (selected_add_option == 1)
    {
        uint16_t nomor;
        
        printf("Input nomor manual\n");
        
        printf("masukan nomor: ");
        scanf(" %hu", &nomor);
        snprintf(newData.nomor, sizeof(newData.nomor), "%06d", nomor);
    }
    else if (selected_add_option == 2)
    {
        hideCursor();
        clearScreen();
        return;
    }
    
    if (avl_find(records, newData.nomor)) printf("nomor komponen harus unik.\n");
    else
    {
        printf("masukan nama: ");
        scanf(" %25[^\n]", newData.nama);
        printf("masukan stok: ");
        scanf(" %d", &newData.stock);
        printf("masukan harga: ");
        scanf(" %lf", &newData.harga);
        
        avl_insert(records, newData);
    }
    
    printf("Press any key to continue...\n");
    hideCursor();
    getch();
    clearScreen();
}

void ubahData(AVL *records)
{
    clearScreen();
    showCursor();
    char nomor_komponen[MAX_NOKOMPONEN + 1];
    int16_t nomor;
    printf("%s%s Ubah Data %s\n", C_BOLD, C_HIGHLIGHT, C_RESETATTR);
    printf("Masukan nomor komponen yang ingin diubah (-1 untuk kembali ke menu utama): ");
    scanf(" %hd", &nomor);
    if (nomor >= 0) snprintf(nomor_komponen, sizeof(nomor_komponen), "%06d", nomor);
    else
    {
        hideCursor();
        clearScreen();
        return;
    }

    AVLNode *node = _search(records->_root, nomor_komponen);
    if (!node) printf("Data dengan nomor komponen (%s) tidak ditemukan.\n", nomor_komponen);
    else
    {
        printf("Data Sekarang : nomor:\n%s\nnama: %s\nstok: %d\nharga: %2f\n", 
                node->data.nomor, node->data.nama, node->data.stock, node->data.harga);
        printf("---------------------------------------------------\n");    
        printf("Masukan nama baru: ");
        scanf(" %[^\n]", node->data.nama);
        printf("Masukan stok baru: ");
        scanf(" %d", &node->data.stock);
        printf("Masukan harga baru: ");
        scanf(" %lf", &node->data.harga);
    
        syncFile(records->_root);        
    }

    printf("Press any key to continue...\n");
    getch();
    hideCursor();
    clearScreen();
}

void tampilkanIndex(AVL *records)
{
    clearScreen();
    printf("%s%s Tampilkan Data %s\n", C_BOLD, C_HIGHLIGHT, C_RESETATTR);
    if (!avl_isEmpty(records))
    {
        printf("+-----------+-------------------------------+---------------------+---------------------+\n");
        printf("|%10s |%30s |%20s |%20s |\n", "nomor", "nama", "harga (Ribuan)", "stock");
        printf("+-----------+-------------------------------+---------------------+---------------------+\n");
        indexedInorder(records->_root);
    }
    else printf("tidak ada data untuk ditampilkan.\n");
    printf("Press any key to continue...\n");
    getch();
    clearScreen();
}

void tampilkanTanpaIndex(AVL *records)
{
    clearScreen();
    printf("%s%s Data Tanpa Index %s\n", C_BOLD, C_HIGHLIGHT, C_RESETATTR);
    if (!avl_isEmpty(records))
    {
        printf("+-------------------------------+---------------------+---------------------+\n");
        printf("|%30s |%20s |%20s |\n", "nama", "harga (Ribuan)", "stock");
        printf("+-------------------------------+---------------------+---------------------+\n");
        noIndexInorder(records->_root);
    }
    else printf("tidak ada data untuk ditampilkan.\n");
    printf("Press any key to continue...\n");
    getch();
    clearScreen();
}

void hapusData(AVL *records)
{
    clearScreen();
    showCursor();
    char nomor_komponen[MAX_NOKOMPONEN + 1];
    int16_t nomor;
    printf("%s%s Hapus Data %s\n", C_BOLD, C_HIGHLIGHT, C_RESETATTR);
    printf("Masukan nomor komponen yang ingin dihapus (-1 untuk kembali ke menu utama): ");
    scanf(" %hd", &nomor);
    if (nomor >= 0) snprintf(nomor_komponen, sizeof(nomor_komponen), "%06d", nomor);
    else
    {
        hideCursor();
        clearScreen();
        return;
    }
    
    if (avl_find(records,nomor_komponen))
    {
        avl_remove(records, nomor_komponen);
        printf("Komponen nomor (%s) berhasil dihapus.\n", nomor_komponen);
    }
    else printf("Komponen nomor (%s) tidak ditemukan.\n", nomor_komponen);
    
    syncFile(records->_root);
    
    printf("Press any key to continue...\n");
    getch();
    hideCursor();
    clearScreen();
}