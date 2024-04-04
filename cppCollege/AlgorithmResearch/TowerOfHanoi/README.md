### Program "TowerOfHanoi.cpp" Dapat Diakses Di Link Berikut Ini.
https://bit.ly/TowerOfHanoiGerrard

<br>

# PENJELASAN PROGRAM TOWER OF HANOI (USING cpp LANGUAGE)

- #include <iostream>: Menambahkan header iostream untuk operasi input/output seperti cout dan cin.
- #include <vector>: Menambahkan header vector untuk menggunakan struktur data vector. Vektor digunakan untuk menyimpan data dinamis dalam program.
- using namespace std: Mengizinkan penggunaan nama-nama fungsi dan variabel dari namespace std tanpa awalan std::. Hal ini membuat kode lebih ringkas.
- void tower_of_hanoi(int n, string source, string target, string auxiliary): Mendeklarasikan fungsi rekursif tower_of_hanoi dengan 4 parameter:
- n: Jumlah gelang yang ingin dipindahkan.
- source: Tiang sumber tempat gelang berada saat ini.
- target: Tiang tujuan tempat gelang ingin dipindahkan.
- auxiliary: Tiang bantu yang digunakan untuk memindahkan gelang.
- if (n == 1): Memeriksa apakah hanya ada 1 gelang. Jika ya, langsung pindahkan gelang dari source ke target.
- tower_of_hanoi(n - 1, source, auxiliary, target): Memanggil fungsi tower_of_hanoi secara rekursif untuk memindahkan n - 1 gelang teratas dari source ke auxiliary menggunakan tiang target sebagai bantu.
- cout << "Pindahkan gelang " << n << " dari " << source << " ke " << target << endl;: Mencetak instruksi untuk memindahkan gelang ke-n dari source ke target.
- tower_of_hanoi(n - 1, auxiliary, target, source): Memanggil fungsi tower_of_hanoi secara rekursif untuk memindahkan n - 1 gelang dari auxiliary ke target menggunakan tiang
- int main(): Menandai awal fungsi utama program. Fungsi ini mendefinisikan titik awal eksekusi program.
- int T;: Mendeklarasikan variabel T bertipe int untuk menyimpan jumlah ronde permainan Menara Hanoi.
- cout << "Masukkan jumlah ronde: ";: Mencetak prompt ke konsol untuk meminta pengguna memasukkan jumlah ronde permainan yang ingin dimainkan.
- cin >> T;: Membaca input dari pengguna dan menyimpannya dalam variabel T.
- vector<int> n_arr(T);: Mendeklarasikan variabel n_arr sebagai vektor bertipe int dengan ukuran T. Vektor ini akan digunakan untuk menyimpan jumlah gelang di setiap ronde.
- for (int ronde = 1; ronde <= T; ++ronde): Perulangan yang dijalankan sebanyak T kali, di mana ronde digunakan sebagai variabel loop untuk melacak ronde saat ini.
- cout << "Masukkan jumlah gelang di ronde " << ronde << ": ";: Mencetak prompt ke konsol untuk meminta pengguna memasukkan jumlah gelang di ronde ke-ronde.
- cin >> n_arr[ronde - 1]: Membaca input dari pengguna dan menyimpannya di elemen ronde - 1 dari vektor n_arr.
- for (int ronde = 1; ronde <= T; ++ronde): Perulangan yang dijalankan sebanyak T kali untuk menampilkan output untuk setiap ronde.
- cout << "Ronde " << ronde << ":" << endl;: Mencetak informasi ronde ke-ronde ke konsol.
- cout << "Langkah-langkah epik Anto dalam memindahkan gelang:" << endl;: Mencetak teks "Langkah-langkah epik Anto dalam memindahkan gelang:" ke konsol.
- fungsi tower_of_hanoi bertanggung jawab untuk memindahkan gelang Menara Hanoi. Parameter yang diberikan:
- n_arr[ronde - 1]: Mengambil nilai jumlah gelang di ronde ke-ronde dari vektor n_arr.
- "Base of Power": Nama tiang sumber tempat gelang berada pada awal ronde.
- "Tower of Triumph": Nama tiang tujuan tempat gelang harus dipindahkan.
- "Booster Platform": Nama tiang bantu yang digunakan untuk memindahkan gelang.
- "cout << endl" mencetak karakter baris baru ke konsol. Ini digunakan untuk memberi jarak antar ronde dan membuat output lebih mudah dibaca.
- "return 0" mengembalikan nilai 0 dan memberi tanda bahwa program telah selesai dijalankan dengan sukses

<br>

# DOKUMENTER OUTPUT PROGRAM:
![Screenshot 2024-04-03 224355](https://github.com/gerrardgs/CPP-Heritage/assets/114888829/80be9b5e-d02d-457e-a43a-8a715c8c4ee2)

<br>

# CPP PROGRAM "TOWER OF HANOI"
```cpp
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

```

<br>

# Problem Statement
Anto adalah seorang gamer handal yang sangat menyukai game seru bernama "Tower of Hanoi: Quest for Victory." Dalam game ini, Anto harus menyelesaikan serangkaian tantangan yang melibatkan memindahkan gelang-gelang dengan ukuran berbeda dari satu tiang ke tiang lainnya untuk mencapai kemenangan! Tiang pertama, yang disebut "Base of Power," berisi gelang-gelang ajaib yang berkilauan. Tantangannya adalah memindahkan semua gelang dari "Base of Power" ke "Tower of Triumph," yaitu tiang ketiga yang menandakan kemenangan! Namun, ada satu aturan penting yang harus diikuti oleh Anto:
- Hanya satu gelang yang boleh dipindahkan pada satu waktu.
- Gelang yang lebih besar tidak boleh diletakkan di atas gelang yang lebih kecil.
- Untuk membantunya, Anto dapat menggunakan "Booster Platform," yaitu tiang kedua yang berfungsi sebagai tempat transit untuk memindahkan gelang.
Sekarang, Anto membutuhkan bantuanmu! Bisakah kamu membantu Anto menyelesaikan "Tower of Hanoi: Quest for Victory" dengan memindahkan gelang-gelang ke "Tower of Triumph"?


Input:
- Input pertama adalah sebuah bilangan bulat T (1≤T≤5), yang merupakan jumlah ronde yang ingin dimainkan oleh Anto.
- Setiap ronde berisi sebuah bilangan bulat n (1≤n≤8), yang merupakan jumlah gelang awal di "Base of Power."

Output:
- Tampilkan langkah-langkah epik Anto dalam memindahkan gelang-gelang menuju kemenangan untuk setiap ronde.
- Setiap langkah pemindahan harus ditampilkan dalam format "Pindahkan gelang [nomor gelang] dari [asal] ke [tujuan]."

Contoh:
<br> Input Contoh:
<br> 2
<br> 3
<br> 2

Output Contoh:
<br> Ronde 1:
<br> Langkah-langkah epik Anto dalam memindahkan gelang:
<br> Pindahkan gelang 1 dari Base of Power ke Tower of Triumph
<br> Pindahkan gelang 2 dari Base of Power ke Booster Platform
<br> Pindahkan gelang 1 dari Tower of Triumph ke Booster Platform
<br> Pindahkan gelang 3 dari Base of Power ke Tower of Triumph
<br> Pindahkan gelang 1 dari Booster Platform ke Base of Power
<br> Pindahkan gelang 2 dari Booster Platform ke Tower of Triumph
<br> Pindahkan gelang 1 dari Base of Power ke Tower of Triumph
<br>
<br> Ronde 2:
<br> Langkah-langkah epik Anto dalam memindahkan gelang:
<br> Pindahkan gelang 1 dari Base of Power ke Booster Platform
<br> Pindahkan gelang 2 dari Base of Power ke Tower of Triumph
<br> Pindahkan gelang 1 dari Booster Platform ke Tower of Triumph

<br>

# Agoritma Penyelesaian Masalah
1. Baca jumlah ronde T.
2. Untuk setiap ronde:
   a. Baca jumlah gelang awal n.
   b. Panggil fungsi rekursif `tower_of_hanoi(n, "Base of Power", "Tower of Triumph", "Booster Platform")`.
3. Fungsi rekursif `tower_of_hanoi(n, source, target, auxiliary)` mengikuti langkah-langkah berikut:
   a. Jika n == 1, pindahkan gelang dari sumber ke tujuan.
   b. Jika tidak:
      i. Pindahkan n-1 gelang dari sumber ke bantuan menggunakan tujuan sebagai peg bantuan.
      ii. Pindahkan gelang ke-n dari sumber ke tujuan.
      iii. Pindahkan n-1 gelang dari bantuan ke tujuan menggunakan sumber sebagai peg bantuan.
4. Tampilkan langkah-langkah untuk setiap ronde.
