#include <iostream>
#include <vector>  // Include header untuk penggunaan std::vector

using namespace std;

// Fungsi rekursif untuk memindahkan gelang
void tower_of_hanoi(int n, string source, string target, string auxiliary) {
  if (n == 1) {
    cout << "Pindahkan gelang 1 dari " << source << " ke " << target << endl;
    return;
  }
  tower_of_hanoi(n - 1, source, auxiliary, target);
  cout << "Pindahkan gelang " << n << " dari " << source << " ke " << target << endl;
  tower_of_hanoi(n - 1, auxiliary, target, source);
}

int main() {
  int T; // Jumlah ronde
  cout << "Masukkan jumlah ronde: ";
  cin >> T;

  // Menyimpan input jumlah gelang untuk setiap ronde
  vector<int> n_arr(T);  // Deklarasi vektor setelah header <vector> di-include

  // Meminta input jumlah gelang untuk setiap ronde
  for (int ronde = 1; ronde <= T; ++ronde) {
    cout << "Masukkan jumlah gelang di ronde " << ronde << ": ";
    cin >> n_arr[ronde - 1];
  }

  // Menampilkan output untuk setiap ronde
  for (int ronde = 1; ronde <= T; ++ronde) {
    cout << "Ronde " << ronde << ":" << endl;
    cout << "Langkah-langkah epik Anto dalam memindahkan gelang:" << endl;

    tower_of_hanoi(n_arr[ronde - 1], "Base of Power", "Tower of Triumph", "Booster Platform");

    cout << endl;
  }

  return 0;
}
-