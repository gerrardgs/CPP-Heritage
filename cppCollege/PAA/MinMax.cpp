#include <iostream>
#include <vector>
using namespace std;

// Struktur untuk menyimpan nilai minimum dan maksimum
struct MinMax {
    int minimum;
    int maximum;
};

// Fungsi untuk menemukan nilai minimum dan maksimum dari sebuah array
MinMax findMinMax(const vector<int>& arr, int low, int high) {
    MinMax result, left, right;
    int mid;

    // Jika hanya ada satu elemen dalam array
    if (low == high) {
        result.minimum = arr[low];
        result.maximum = arr[low];
        return result;
    }

    // Jika terdapat dua elemen dalam array
    if (high == low + 1) {
    if (arr[low] < arr[high]) {
        result.minimum = arr[low];
        result.maximum = arr[high];
    } else {
        result.minimum = arr[high];
        result.maximum = arr[low];
        }
        return result;
    }

    // Jika terdapat lebih dari dua elemen dalam array, bagi menjadi dua bagian
    mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Gabungkan hasil dari dua bagian
    result.minimum = min(left.minimum, right.minimum);
    result.maximum = max(left.maximum, right.maximum);
    return result;

}
int main() {
    vector<int> arr = {7, 3, 9, 2, 11, 5}; // Contoh array
    int n = arr.size();

    // Cari nilai minimum dan maksimum dalam array
    MinMax result = findMinMax(arr, 0, n - 1);
    
    // Tampilkan hasil
    cout << "Nilai Minimum: " << result.minimum << endl;
    cout << "Nilai Maksimum: " << result.maximum << endl;
    return 0;
}
