/******************************************************
Nama file: cin_numerik.cpp
*******************************************************/

#include <iostream>

int main() {   
   int i;
   double d;
   
   // menampilkan keterangan
   std::cout<<"Masukkan bilangan bulat: ";
   // membaca bilangan bulat
   std::cin>>i;
   
   // menampilkan keterangan
   std::cout<<"Masukkan bilangan riil: ";
   // membaca bilangan riil
   std::cin>>d;
      
   std::cout<<std::endl;
   std::cout<<"Anda memasukkan bilangan "
            <<i<<" dan "<<d<<std::endl;
   
   return 0;
}
