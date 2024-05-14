#include <stdio.h>
#include <string.h>

// FUNGSI - MENGGABUNGKAN STRING 
// Merge function to merge two sorted strings
void merge(char str[], int l, int m, int r) { // PARAMETER - ARRAY STRING, INDEKS AWAL, INDEKS TENGAH, DAN INDEKS AKHIR
    int i, j, k;
    int n1 = m - l + 1; // UKURAN SUBARRAY KIRI
    int n2 = r - m; // UKURAN SUBARRAY KANAN

    // Create temporary strings to hold subarray
    char L[n1 + 1], R[n2 + 1]; // MEMBAGI 2 MENJADI ARRAY STRING ~ KIRI DAN KANAN

    // Copy data to temporary strings L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = str[l + i];
    L[i] = '\0'; // Add null terminator to mark the end of the L string

    for (j = 0; j < n2; j++)
        R[j] = str[m + 1 + j];
    R[j] = '\0'; // Add null terminator to mark the end of the R string

    // Merge the temporary strings back into str[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            str[k] = L[i];
            i++;
        } else {
            str[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        str[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        str[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function for string
void mergeSort(char str[], int l, int r) { // PARAMETER - ARRAY STRING, INDEKS AWAL, DAN INDEKS AKHIR
    if (l < r) { 
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(str, l, m);
        mergeSort(str, m + 1, r);

        // Merge the sorted halves
        merge(str, l, m, r);
    } // FUNGSI MERGE SORT YANG SECARA REKURSIF MEMBAGI ARRAY MENJADI SUBARRAY HINGGA MENJADI 1, LALU MENGGABUNG DENGAN MEMANGGIL FUNGSI MERGE 
}

// MENERIMA INPUT, MENGURUTKAN STRING, DAN MENAMPILKAN OUTPUT
int main() {
    char str[100][100];
    int n, i;

    // Input
    printf("Enter the number of strings (max 100): ");
    scanf("%d", &n);
    printf("Enter %d strings:\n", n);
    for (i = 0; i < n; i++)
        scanf("%s", str[i]);

    // Sorting each string using Merge Sort
    for (i = 0; i < n; i++)
        mergeSort(str[i], 0, strlen(str[i]) - 1);

    // Output
    printf("\nSorted strings:\n");
    for (i = 0; i < n; i++)
        printf("%s\n", str[i]);

    return 0;
}
