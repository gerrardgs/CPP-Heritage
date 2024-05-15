/******************************************************
Nama file: alamat_pointer.cpp
*******************************************************/

#include <iostream>

int main() {
   int a {10};
   
   int *p {&a};	// pointer p menunjuk ke alamat dari variabel a
   
   std::cout<<"Nilai a\t\t\t:"<<a<<std::endl;
   std::cout<<"Alamat variabel a\t:"<<&a<<std::endl;
   std::cout<<"Nilai *p\t\t:"<<*p<<std::endl;
   std::cout<<"Nilai p\t\t\t:"<<p<<std::endl;
   std::cout<<"Alamat pointer p\t:"<<&p<<std::endl;
   
   return 0;
}
