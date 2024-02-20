#include <iostream>
#include <fstream>

using namespace std;

int main() {
    char myChar;
    ifstream MyReadFile;

    MyReadFile.open("input.txt");

    if (!MyReadFile.is_open()) {
        cout << "Failed to open the file" << endl;
        return 1;
    }

    while (MyReadFile.get(myChar)) {
        if (myChar == '\n') {
            cout << "\\n";
        } else if (myChar == '\t'){
            cout << "\\t";
        }
        cout << myChar;
    }

    MyReadFile.close();
    return 0;
}
