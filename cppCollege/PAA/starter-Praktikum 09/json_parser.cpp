#include <vector>
#include <sstream>
#include "struct_book.cpp"

using namespace std;

vector<Book> jsonToBooks(const string &jsonData)
{
    vector<Book> books;
    istringstream iss(jsonData);

    string line;
    while (getline(iss, line))
    {
        if (line.find('{') != string::npos)
        {
            Book book;
            while (getline(iss, line))
            {
                if (line.find("Judul") != string::npos)
                {
                    size_t pos = line.find(":");
                    book.judul = line.substr(pos + 3, line.length() - pos - 4);
                }
                else if (line.find("Penulis") != string::npos)
                {
                    size_t pos = line.find(":");
                    book.penulis = line.substr(pos + 3, line.length() - pos - 4);
                }
                else if (line.find("Tahun Terbit") != string::npos)
                {
                    size_t pos = line.find(":");
                    book.tahun_terbit = stoi(line.substr(pos + 2));
                }
                else if (line.find("Nomor Rak") != string::npos)
                {
                    size_t pos = line.find(":");
                    book.nomor_rak = line.substr(pos + 3, line.length() - pos - 4);
                }
                else if (line.find('}') != string::npos)
                {
                    books.push_back(book);
                    break;
                }
            }
        }
    }

    return books;
}
