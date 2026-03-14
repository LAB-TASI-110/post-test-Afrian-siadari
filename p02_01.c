#include <stdio.h>
#include <string.h>

typedef struct {
    char kota[10];
    float berat_butet;
    float berat_ucok;
    float total_berat;
    long long total_ongkir;
    long long total_bayar;
    char promo[150];
} DataPengiriman;

int main() {
    DataPengiriman kiriman[100];
    int jumlah_data = 0;
    char input_kota[10];

    while (scanf("%s", input_kota) == 1) {
        if (strcmp(input_kota, "END") == 0) {
            break;
        }
        strcpy(kiriman[jumlah_data].kota, input_kota);
        scanf("%f", &kiriman[jumlah_data].berat_butet);
        jumlah_data++;
    }

    printf("\n");
    for (int i = 0; i < jumlah_data; i++) {
        kiriman[i].berat_ucok = kiriman[i].berat_butet * 1.5;
        kiriman[i].total_berat = kiriman[i].berat_butet + kiriman[i].berat_ucok;

        long long tarif_per_kg = 0;
        int is_luar_pulau = 0;

        if (strcmp(kiriman[i].kota, "MDN") == 0) {
            tarif_per_kg = 8000;
        } else if (strcmp(kiriman[i].kota, "BLG") == 0) {
            tarif_per_kg = 5000;
        } else if (strcmp(kiriman[i].kota, "JKT") == 0) {
            tarif_per_kg = 12000;
            is_luar_pulau = 1;
        } else if (strcmp(kiriman[i].kota, "SBY") == 0) {
            tarif_per_kg = 13000;
            is_luar_pulau = 1;
        }

        kiriman[i].total_ongkir = (long long)(kiriman[i].total_berat * tarif_per_kg);
        kiriman[i].total_bayar = kiriman[i].total_ongkir;
        
        int diskon_10 = 0;
        if (kiriman[i].total_berat > 10.0) {
            kiriman[i].total_bayar = kiriman[i].total_ongkir - (kiriman[i].total_ongkir * 10 / 100);
            diskon_10 = 1;
        }

        if (diskon_10 == 1 && is_luar_pulau == 1) {
            strcpy(kiriman[i].promo, "Diskon ongkir 10% dan Asuransi gratis");
        } else if (diskon_10 == 1) {
            strcpy(kiriman[i].promo, "Diskon ongkir 10%");
        } else if (is_luar_pulau == 1) {
            strcpy(kiriman[i].promo, "Asuransi gratis");
        } else {
            strcpy(kiriman[i].promo, "Tidak ada promo");
        }

        printf("Struk Pembayaran\n");
        printf("Kota tujuan: %s\n", kiriman[i].kota);
        printf("Berat paket Butet: %.2f kg\n", kiriman[i].berat_butet);
        printf("Berat paket Ucok: %.2f kg\n", kiriman[i].berat_ucok);
        printf("Total berat: %.2f kg\n", kiriman[i].total_berat);
        
        if (kiriman[i].total_bayar == kiriman[i].total_ongkir) {
            printf("Total ongkos kirim: Rp %lld\n", kiriman[i].total_ongkir);
        } else {
            printf("Total ongkos kirim: Rp %lld (Harga asli: Rp %lld)\n", kiriman[i].total_bayar, kiriman[i].total_ongkir);
        }
        
        printf("Informasi promo yang diperoleh: %s\n", kiriman[i].promo);
        printf("\n");
    }

    return 0;
}