#include <iostream>
#include <fstream>
using namespace std;

class Writer {
    fstream fs;
    public:
        Writer(string fileToOpen = "a.txt", ios_base::openmode fileMode = fstream::in | fstream::out | fstream::app) {
            fs.open(fileToOpen, fileMode);
        }
        ~Writer() {
            fs.close();
        }
        Writer& operator<<(const string &toWrite) {
            fs.write(toWrite.c_str(), toWrite.length());
            return *this;
        }
        Writer& operator<<(char toWrite) {
            fs.write(&toWrite, 1);
            return *this;
        }
};

int main() {

    Writer w;

    w << "johnny boy" << '\n';


    return 0;
}



