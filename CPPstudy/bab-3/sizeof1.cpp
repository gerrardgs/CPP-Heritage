/******************************************************
Nama file: sizeof1.cpp
*******************************************************/

#include <iostream>

struct Struktur {
   char c;
   int i;
   float f;
};

class Kelas {
   double d;
public:
   Kelas() { d = 0.0; }
   void setD(double d) { this->d = d; }
   double getD() { return d; }
};

int main() {   
   Struktur s;
   Kelas k;   
   
   std::cout<<"sizeof s\t\t: "
            <<sizeof s
            <<" byte"<<std::endl;
   std::cout<<"sizeof k\t\t: "
            <<sizeof k
            <<" byte"<<std::endl;
   std::cout<<"sizeof(Struktur)\t: "
            <<sizeof(Struktur)
            <<" byte"<<std::endl;
   std::cout<<"sizeof(Kelas)\t\t: "
            <<sizeof(Kelas)
            <<" byte"<<std::endl;
   
   return 0; 
}
