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
    printf("4. Gelatin Hydrogel\n");
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
