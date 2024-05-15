/******************************************************
Nama file: cin_string.cpp
*******************************************************/

#include <iostream>
#include <string>	// std::string

int main() {   
   std::string nama;
   
   std::cout<<"Masukkan nama: ";
   // membaca string
   std::cin>>nama;
   
   std::cout<<"Hai "<<nama
            <<", selamat datang di pemrograman C++"
            <<std::endl;
   
   return 0;
}
