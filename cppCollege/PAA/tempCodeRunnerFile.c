#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <algorithm> // Untuk next_permutation

// Jumlah titik distribusi
#define N 4

// Fungsi untuk menghitung jarak antara dua titik distribusi
int hitungJarak(int graph[N][N], int rute[], int n) {
    int jarak = 0;
    for (int i = 0; i < n - 1; i++) {
        jarak += graph[rute[i]][rute[i + 1]];
    }
    // Kembali ke titik distribusi awal
    jarak += graph[rute[n - 1]][rute[0]];
    return jarak;
}

// Fungsi untuk mencari rute terpendek
void cariRuteTerpendek(int graph[N][N]) {
    int rute[N];
    for (int i = 0; i < N; i++) {
        rute[i] = i;
    }
    int jarakMin = INT_MAX;

    // Cari semua permutasi rute
    do {
        int jarak = hitungJarak(graph, rute, N);
        if (jarak < jarakMin) {
            jarakMin = jarak;
        }
    } while (std::next_permutation(rute, rute + N));

    printf("Rute terpendek: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", rute[i]);
    }
    printf("%d\n", rute[0]); // Kembali ke titik distribusi awal
    printf("Total jarak: %d\n", jarakMin);
}

int main() {
    // Contoh graf berarah dengan bobot jarak antara titik distribusi
    int graph[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cariRuteTerpendek(graph);
    return 0;
}
