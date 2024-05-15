/******************************************************
Nama file: test.c
*******************************************************/

#include <stdio.h>

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
