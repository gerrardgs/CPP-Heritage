/******************************************************
Nama file: cin_string1.cpp
*******************************************************/

#include <iostream>
#include <string>

int main() {   
   std::string nama;
   
   std::cout<<"Masukkan nama: ";
   
   // membaca satu baris string
   getline(std::cin, nama);
   
   std::cout<<"Hai "<<nama
            <<", selamat datang di pemrograman C++"
            <<std::endl;
   
   return 0;
}
