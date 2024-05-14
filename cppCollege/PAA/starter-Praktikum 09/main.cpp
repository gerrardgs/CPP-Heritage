#include <iostream>
#include <fstream>
#include <vector>
#include "json_parser.cpp"

using namespace std;

// Merge Sort
template<typename T, typename Comparator>
void mergeSort(vector<T> &arr, int left, int right, Comparator comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

template<typename T, typename Comparator>
void merge(vector<T> &arr, int left, int mid, int right, Comparator comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// sort 3 criteria
bool sortByTitle(const Book &a, const Book &b) {
    return a.judul < b.judul;
}

bool sortByAuthor(const Book &a, const Book &b) {
    return a.penulis < b.penulis;
}

bool sortByYear(const Book &a, const Book &b) {
    return a.tahun_terbit < b.tahun_terbit;
}

int main() {
    // Read data
    ifstream file("data.json");
    stringstream buffer;
    buffer << file.rdbuf();
    string jsonData = buffer.str();
    file.close();

    // Parse JSON data
    vector<Book> books = jsonToBooks(jsonData);

    // Sort based on criteria
    int choice;
    cout << "Pilih kriteria untuk mengurutkan (1: Judul, 2: Penulis, 3: Tahun Terbit): ";
    cin >> choice;

    switch (choice) {
        case 1:
            mergeSort(books, 0, books.size() - 1, sortByTitle);
            break;
        case 2:
            mergeSort(books, 0, books.size() - 1, sortByAuthor);
            break;
        case 3:
            mergeSort(books, 0, books.size() - 1, sortByYear);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            return 1;
    }

    // Display sorted
    cout << "Daftar buku setelah diurutkan:" << endl;
    cout << "[" << endl;
    for (const auto &book : books) {
        cout << "{ judul: \"" << book.judul << "\", penulis: \"" << book.penulis << "\", tahun_terbit: " << book.tahun_terbit << ", nomor_rak: \"" << book.nomor_rak << "\" }" << endl;
    }
    cout << "]" << endl;

    return 0;
}
