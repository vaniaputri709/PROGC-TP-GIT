#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HARI 30
#define AMBANG 0.2 // 20%

struct Biomaterial {
    char nama_pasien[50];
    char nama[30];
    char jenis[30];
    float massa_awal;
    float laju_degradasi;
    float densitas;
    float luas_permukaan;
    char bentuk_fisik[30];
    char aplikasi[50];
    char jenis_pasien[20];
    int estimasi_durasi_terapi;
    char catatan_klinis[100];
};

const char* level_degradasi(float persentase) {
    if (persentase < 20) return "Biomaterial masih stabil";
    else if (persentase < 70) return "Degradasi wajar";
    else if (persentase < 80) return "Tindak lanjut klinis disarankan";
    else return "Kondisi kritis, evaluasi segera";
}

const char* rekomendasi_klinis(float persentase) {
    if (persentase < 20) return "Lanjutkan terapi tanpa intervensi.";
    else if (persentase < 70) return "Lakukan pemantauan rutin.";
    else if (persentase < 80) return "Pertimbangkan pemeriksaan radiologis atau darah.";
    else return "Hentikan terapi & lakukan evaluasi lanjutan segera.";
}

void tampilkan_bar(float persen) {
    int panjang = (int)(persen / 10);
    for (int i = 0; i < panjang; i++) printf("#");
    for (int i = panjang; i < 10; i++) printf(" ");
    printf(" (%.0f%%)", persen);
}

void pilih_biomaterial(struct Biomaterial *b, int pilihan) {
    switch(pilihan) {
        case 1:
            strcpy(b->nama, "PLA Scaffold");
            strcpy(b->jenis, "Polylactic Acid");
            strcpy(b->bentuk_fisik, "Porous Scaffold");
            b->laju_degradasi = 5.0;
            b->densitas = 1.25;
            b->luas_permukaan = 12.0;
            b->estimasi_durasi_terapi = 21;
            break;
        case 2:
            strcpy(b->nama, "Magnesium Alloy");
            strcpy(b->jenis, "Metal");
            strcpy(b->bentuk_fisik, "Rod Implant");
            b->laju_degradasi = 8.0;
            b->densitas = 1.74;
            b->luas_permukaan = 8.0;
            b->estimasi_durasi_terapi = 14;
            break;
        case 3:
            strcpy(b->nama, "Chitosan Mesh");
            strcpy(b->jenis, "Natural Polymer");
            strcpy(b->bentuk_fisik, "Mesh Sheet");
            b->laju_degradasi = 3.0;
            b->densitas = 1.30;
            b->luas_permukaan = 15.0;
            b->estimasi_durasi_terapi = 30;
            break;
        case 4:
            strcpy(b->nama, "Hydroxyapatite Composite");
            strcpy(b->jenis, "Ceramic");
            strcpy(b->bentuk_fisik, "Granule");
            b->laju_degradasi = 1.5;
            b->densitas = 2.3;
            b->luas_permukaan = 6.0;
            b->estimasi_durasi_terapi = 60;
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }
}

void pilih_aplikasi_medis(char *tujuan) {
    int pilih;
    printf("\n=== Pilih Aplikasi Medis ===\n");
    printf("1. Rekonstruksi Tulang\n");
    printf("2. Penyembuhan Luka\n");
    printf("3. Drug Delivery System\n");
    printf("4. Penambalan Kartilago\n");
    printf("Masukkan pilihan (1-4): ");
    scanf("%d", &pilih);
    getchar();
    switch(pilih) {
        case 1: strcpy(tujuan, "Rekonstruksi Tulang"); break;
        case 2: strcpy(tujuan, "Penyembuhan Luka"); break;
        case 3: strcpy(tujuan, "Drug Delivery System"); break;
        case 4: strcpy(tujuan, "Penambalan Kartilago"); break;
        default:
            printf("Pilihan tidak valid. Menggunakan default: Penyembuhan Luka\n");
            strcpy(tujuan, "Penyembuhan Luka");
            break;
    }
}

void simulasi(struct Biomaterial *b, float *histori, int interval_pemantauan) {
    float massa = b->massa_awal;
    float massa_sebelumnya = massa;
    float target_massa_minimum = b->massa_awal * AMBANG;
    int hari = 0;

    printf("\n=== SIMULASI DEGRADASI ===\n");

    while (hari < MAX_HARI) {
        massa -= massa * b->laju_degradasi / 100.0;
        histori[hari] = massa;

        float persen_sisa = (massa / b->massa_awal) * 100.0;
        float penurunan = massa_sebelumnya - massa;

        printf("Hari ke-%2d | Massa: %.2f g [", hari + 1, massa);
        tampilkan_bar(persen_sisa);
        printf("]");

        if (penurunan > (b->massa_awal * 0.10)) printf(" Penurunan tajam!");
        if (massa <= target_massa_minimum) {
            printf(" Di bawah batas aman!\n");
            break;
        }

        printf("\n");
        massa_sebelumnya = massa;
        hari++;
        if (hari % interval_pemantauan != 0) continue;
    }

    float degradasi_total = b->massa_awal - massa;
    float persen_total = (degradasi_total / b->massa_awal) * 100.0;
    const char* status = level_degradasi(persen_total);
    const char* rekomendasi = rekomendasi_klinis(persen_total);

    printf("\n=== RINGKASAN PENILAIAN PENELITI BIOMATERIAL ===\n");
    printf("Nama Pasien       : %s\n", b->nama_pasien);
    printf("Biomaterial       : %s (%s)\n", b->nama, b->jenis);
    printf("Aplikasi Medis    : %s\n", b->aplikasi);
    printf("Jenis Pasien      : %s\n", b->jenis_pasien);
    printf("Massa Awal        : %.2f g\n", b->massa_awal);
    printf("Massa Akhir       : %.2f g\n", massa);
    printf("Penurunan Total   : %.2f g (%.1f%%)\n", degradasi_total, persen_total);
    printf("Status Klinis     : %s\n", status);
    printf("Rekomendasi Tindakan: %s\n", rekomendasi);
    printf("Estimasi Durasi Terapi: %d hari\n", b->estimasi_durasi_terapi);
    printf("Catatan Peneliti  : %s\n", b->catatan_klinis);
}

void tampilkan_header() {
    printf("====================================================\n");
    printf("         SIMULATOR DEGRADASI BIOMATERIAL 2.0        \n");
    printf("     Evaluasi Keamanan oleh Vania, Caca, Athal     \n");
    printf("====================================================\n");
}

int main() {
    struct Biomaterial biomat;
    float *histori_massa;
    int pilihan;
    int interval_pemantauan;

    tampilkan_header();

    printf("Masukkan nama pasien: ");
    fgets(biomat.nama_pasien, sizeof(biomat.nama_pasien), stdin);
    biomat.nama_pasien[strcspn(biomat.nama_pasien, "\n")] = 0;

    printf("\n=== Pilih Biomaterial ===\n");
    printf("1. PLA Scaffold\n");
    printf("2. Magnesium Alloy\n");
    printf("3. Chitosan Mesh\n");
    printf("4. Hydroxyapatite Composite\n");
    printf("Masukkan pilihan (1-4): ");
    scanf("%d", &pilihan);
    getchar();
    pilih_biomaterial(&biomat, pilihan);

    printf("Masukkan massa awal (gram): ");
    scanf("%f", &biomat.massa_awal);
    getchar();

    pilih_aplikasi_medis(biomat.aplikasi);

    printf("Jenis pasien (Anak-anak / Dewasa / Lansia): ");
    fgets(biomat.jenis_pasien, sizeof(biomat.jenis_pasien), stdin);
    biomat.jenis_pasien[strcspn(biomat.jenis_pasien, "\n")] = 0;

    printf("Interval waktu antar pemantauan (hari): ");
    scanf("%d", &interval_pemantauan);
    getchar();

    printf("Catatan khusus dari peneliti (maks. 100 karakter): ");
    fgets(biomat.catatan_klinis, sizeof(biomat.catatan_klinis), stdin);
    biomat.catatan_klinis[strcspn(biomat.catatan_klinis, "\n")] = 0;

    histori_massa = (float *)malloc(MAX_HARI * sizeof(float));
    if (!histori_massa) {
        printf("Gagal alokasi memori.\n");
        return 1;
    }

    simulasi(&biomat, histori_massa, interval_pemantauan);

    printf("\nTampilkan grafik histori degradasi? (y/n): ");
    char jawab;
    scanf(" %c", &jawab);
    if (jawab == 'y' || jawab == 'Y') {
        printf("\n=== HISTORI GRAFIK DEGRADASI ===\n");
        for (int i = 0; i < MAX_HARI; i++) {
            if (histori_massa[i] == 0.0) break;
            float persen = (histori_massa[i] / biomat.massa_awal) * 100.0;
            printf("Hari %2d: ", i + 1);
            tampilkan_bar(persen);
            printf("\n");
        }
    }

    free(histori_massa);
    printf("\nTerima kasih telah menggunakan simulator biomaterial.\n");
    return 0;
}