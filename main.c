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