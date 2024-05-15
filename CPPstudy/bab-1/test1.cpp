/******************************************************
Nama file: test1.cpp
*******************************************************/

#include <cstdio>	// agar C++ mengenal fungsi printf() dan scanf()

int main(void) {
  int x;

  /* menampilkan teks untuk informasi */
  printf("Masukkan bilangan bulat: "); 

  /* membaca nilai dari keyboard 
     dan menyimpannya ke dalam variabel x */
  scanf("%d", &x);

  /* menampilkan nilai yang telah dimasukkan */
  printf("Bilangan yang dimasukkan adalah %d", x);

  return 0;
}
