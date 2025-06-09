#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

enum JenisPasien { ANAK_ANAK = 1, DEWASA, LANSIA };

const char* konversi_jenis_pasien(int kode) {
    switch(kode) {
        case ANAK_ANAK: return "Anak-anak";
        case DEWASA: return "Dewasa";
        case LANSIA: return "Lansia";
        default: return "Tidak diketahui";
    }
}

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
            strcpy(b->nama, "Custom");
            strcpy(b->jenis, "Lainnya");
            strcpy(b->bentuk_fisik, "Tidak diketahui");
            b->laju_degradasi = 4.0;
            b->densitas = 1.0;
            b->luas_permukaan = 10.0;
            b->estimasi_durasi_terapi = 20;
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
    int pilihan, interval_pemantauan, kode_pasien;

    tampilkan_header();

    printf("Masukkan nama pasien: ");
    fgets(biomat.nama_pasien, sizeof(biomat.nama_pasien), stdin);
    biomat.nama_pasien[strcspn(biomat.nama_pasien, "\n")] = 0;

    do {
        printf("\n=== Pilih Biomaterial ===\n");
        printf("1. PLA Scaffold\n");
        printf("2. Magnesium Alloy\n");
        printf("3. Chitosan Mesh\n");
        printf("4. Hydroxyapatite Composite\n");
        printf("5. Lainnya\n");
        printf("Masukkan pilihan (1-5): ");
        scanf("%d", &pilihan);
        getchar();
        if (pilihan >= 1 && pilihan <= 5) break;
        printf("Pilihan tidak valid. Coba lagi.\n");
    } while (1);
    pilih_biomaterial(&biomat, pilihan);

    do {
        printf("Masukkan massa awal (gram): ");
        scanf("%f", &biomat.massa_awal);
        getchar();
        if (biomat.massa_awal > 0) break;
        printf("Input tidak valid. Massa harus positif.\n");
    } while (1);

    do {
        printf("\n=== Pilih Aplikasi Medis ===\n");
        printf("1. Rekonstruksi Tulang\n");
        printf("2. Penyembuhan Luka\n");
        printf("3. Drug Delivery System\n");
        printf("4. Penambalan Kartilago\n");
        printf("Masukkan pilihan (1-4): ");
        scanf("%d", &pilihan);
        getchar();
        if (pilihan >= 1 && pilihan <= 4) break;
        printf("Pilihan tidak valid. Coba lagi.\n");
    } while (1);

    switch(pilihan) {
        case 1: strcpy(biomat.aplikasi, "Rekonstruksi Tulang"); break;
        case 2: strcpy(biomat.aplikasi, "Penyembuhan Luka"); break;
        case 3: strcpy(biomat.aplikasi, "Drug Delivery System"); break;
        case 4: strcpy(biomat.aplikasi, "Penambalan Kartilago"); break;
    }

    do {
        printf("Jenis pasien:\n1. Anak-anak\n2. Dewasa\n3. Lansia\nMasukkan pilihan (1-3): ");
        scanf("%d", &kode_pasien);
        getchar();
        if (kode_pasien >= 1 && kode_pasien <= 3) break;
        printf("Pilihan tidak valid. Silakan coba lagi.\n");
    } while (1);
    strcpy(biomat.jenis_pasien, konversi_jenis_pasien(kode_pasien));

    do {
        printf("Interval waktu antar pemantauan (hari): ");
        scanf("%d", &interval_pemantauan);
        getchar();
        if (interval_pemantauan > 0) break;
        printf("Input tidak boleh nol atau negatif. Coba lagi.\n");
    } while (1);

    printf("Catatan khusus dari peneliti (maks. 100 karakter): ");
    fgets(biomat.catatan_klinis, sizeof(biomat.catatan_klinis), stdin);
    biomat.catatan_klinis[strcspn(biomat.catatan_klinis, "\n")] = 0;

    histori_massa = (float *)malloc(MAX_HARI * sizeof(float));
    if (!histori_massa) {
        printf("Gagal alokasi memori.\n");
        return 1;
    }

    simulasi(&biomat, histori_massa, interval_pemantauan);

    char jawab;
    do {
        printf("\nTampilkan grafik histori degradasi? (y/n): ");
        scanf(" %c", &jawab);
        jawab = tolower(jawab);
        if (jawab == 'y' || jawab == 'n') break;
        printf("Input tidak valid. Harus 'y' atau 'n'.\n");
    } while (1);

    if (jawab == 'y') {
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