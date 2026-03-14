#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Untuk fungsi Sleep() di Windows

// --- Struktur Data ---
typedef struct {
    int id;
    char nama[50];
    char kategori[30];
    int harga;
    int stok;
} ItemMenu;

typedef struct {
    int id_menu;
    int jumlah;
    int subtotal;
} ItemPesanan;

// --- Data Dummy Menu ---
ItemMenu database_menu[] = {
    {1, "Nasi Goreng Spesial", "Makanan", 15000, 20},
    {2, "Mie Ayam Bakso", "Makanan", 12000, 15},
    {3, "Ayam Geprek", "Makanan", 13000, 30},
    {4, "Es Teh Manis", "Minuman", 4000, 50},
    {5, "Kopi Susu Gula Aren", "Minuman", 10000, 25},
    {6, "Air Mineral", "Minuman", 3000, 100},
    {7, "Roti Bakar Coklat", "Camilan", 8000, 10}
};
int jumlah_menu = sizeof(database_menu) / sizeof(database_menu[0]);

// --- Fungsi Khusus: Menghitung Total Stok per Kategori ---
int hitungTotalStokKategori(const char* kategori_diminta) {
    int total_stok = 0;
    for (int i = 0; i < jumlah_menu; i++) {
        // Membandingkan string (case-insensitive sederhana untuk contoh ini)
        if (strcmpi(database_menu[i].kategori, kategori_diminta) == 0) {
            total_stok += database_menu[i].stok;
        }
    }
    return total_stok;
}

// --- Tampilan Menu ---
void tampilkanMenu() {
    printf("\n=== DAFTAR MENU KAFETARIA ===\n");
    printf("%-5s %-25s %-15s %-10s %-5s\n", "ID", "Nama Menu", "Kategori", "Harga", "Stok");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < jumlah_menu; i++) {
        printf("%-5d %-25s %-15s Rp%-8d %-5d\n", 
            database_menu[i].id, 
            database_menu[i].nama, 
            database_menu[i].kategori, 
            database_menu[i].harga, 
            database_menu[i].stok);
    }
    printf("-----------------------------------------------------------------\n");
}

// --- Sistem Pembayaran E-Wallet (Simulasi Webhook) ---
void prosesPembayaranEWallet(int total_tagihan) {
    int pilihan_ewallet;
    printf("\n=== METODE PEMBAYARAN (E-WALLET ONLY) ===\n");
    printf("1. GoPay\n2. OVO\n3. ShopeePay\n4. Dana\n");
    printf("Pilih E-Wallet (1-4): ");
    scanf("%d", &pilihan_ewallet);

    char nama_ewallet[20];
    switch(pilihan_ewallet) {
        case 1: strcpy(nama_ewallet, "GoPay"); break;
        case 2: strcpy(nama_ewallet, "OVO"); break;
        case 3: strcpy(nama_ewallet, "ShopeePay"); break;
        case 4: strcpy(nama_ewallet, "Dana"); break;
        default: strcpy(nama_ewallet, "QRIS Default"); break;
    }

    printf("\n[SISTEM] Membuka aplikasi %s dan membuat tagihan sebesar Rp%d...\n", nama_ewallet, total_tagihan);
    Sleep(2000); // Simulasi jeda server
    printf("[SISTEM] Menunggu konfirmasi pembayaran (Simulasi Webhook)...\n");
    
    // Simulasi loading
    for(int i=0; i<3; i++) {
        printf(".\n");
        Sleep(1000);
    }

    printf("\n==========================================\n");
    printf(">> PEMBAYARAN BERHASIL DITERIMA VIA %s <<\n", nama_ewallet);
    printf("==========================================\n");
}

// --- Alur Utama ---
int main() {
    int pilihan_utama;
    char kategori_cari[30];
    
    // Variabel Pre-Order
    ItemPesanan keranjang[10];
    int jumlah_pesanan = 0;
    int total_harga_pesanan = 0;
    char waktu_pengambilan[10];

    while (1) {
        printf("\n=== SISTEM PRE-ORDER KAFETARIA KAMPUS ===\n");
        printf("1. Lihat Menu\n");
        printf("2. Cek Total Stok Berdasarkan Kategori\n");
        printf("3. Buat Pre-Order Baru\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");
        scanf("%d", &pilihan_utama);

        if (pilihan_utama == 1) {
            tampilkanMenu();
        } 
        else if (pilihan_utama == 2) {
            printf("\nMasukkan nama kategori (Makanan / Minuman / Camilan): ");
            scanf("%s", kategori_cari);
            int total = hitungTotalStokKategori(kategori_cari);
            printf("-> Total ketersediaan stok untuk kategori '%s' adalah: %d item.\n", kategori_cari, total);
        } 
        else if (pilihan_utama == 3) {
            jumlah_pesanan = 0;
            total_harga_pesanan = 0;
            int id_pesan, qty_pesan, lagi = 1;

            tampilkanMenu();
            printf("\n--- Proses Pre-Order ---\n");
            
            while(lagi == 1) {
                printf("Masukkan ID Menu yang ingin dipesan: ");
                scanf("%d", &id_pesan);
                printf("Masukkan Jumlah: ");
                scanf("%d", &qty_pesan);

                // Cari harga berdasarkan ID
                int harga_satuan = 0;
                int idx_menu = -1;
                for (int i = 0; i < jumlah_menu; i++) {
                    if (database_menu[i].id == id_pesan) {
                        harga_satuan = database_menu[i].harga;
                        idx_menu = i;
                        break;
                    }
                }

                if (idx_menu != -1) {
                    keranjang[jumlah_pesanan].id_menu = id_pesan;
                    keranjang[jumlah_pesanan].jumlah = qty_pesan;
                    keranjang[jumlah_pesanan].subtotal = harga_satuan * qty_pesan;
                    total_harga_pesanan += keranjang[jumlah_pesanan].subtotal;
                    
                    // Kurangi stok sementara di memori
                    database_menu[idx_menu].stok -= qty_pesan; 
                    jumlah_pesanan++;
                }

                printf("Tambah item lain? (1=Ya, 0=Tidak): ");
                scanf("%d", &lagi);
            }

            printf("\nJam berapa pesanan akan diambil? (format HH:MM, cth: 12:15): ");
            scanf("%s", waktu_pengambilan);

            printf("\n--- Ringkasan Pre-Order ---\n");
            printf("Waktu Pengambilan: %s WIB\n", waktu_pengambilan);
            printf("Total Tagihan: Rp%d\n", total_harga_pesanan);
            
            prosesPembayaranEWallet(total_harga_pesanan);

            printf("\n[NOTIFIKASI] Pre-Order sukses! Pesanan otomatis masuk ke Kitchen Display System (Dapur).\n");
            printf("Silakan ambil pesanan Anda pada jam %s di loket Pre-Order kafetaria.\n", waktu_pengambilan);
        } 
        else if (pilihan_utama == 4) {
            printf("Terima kasih telah menggunakan sistem kafetaria.\n");
            break;
        }
    }

    return 0;
}