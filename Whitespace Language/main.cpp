// https://en.wikipedia.org/wiki/Whitespace_(programming_language)
// https://codernet.ru/articles/drugoe/whitespace_yazyik_programmirovaniya_s_samyim_neobyichnyim_sintaksisom/

// ' ' = 0
// '\t' = 1

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    char myChar;
    string result_butes;
    ifstream MyReadFile;

    MyReadFile.open("input.txt");

    if (!MyReadFile.is_open()) {
        cout << "Failed to open the file" << endl;
        return 1;
    }

    while (MyReadFile.get(myChar)) {
        if (myChar == '\n') {
            cout << "\\n";
            result_butes += '\n';
        } else if (myChar == '\t'){
            cout << "\\t";
            result_butes += '1';
        } else if (myChar == ' '){
            cout << "\\s";
            result_butes += '0';
        }
        cout << myChar;
    }

    MyReadFile.close();



    cout << "\n\nResult:\n" << result_butes << endl;

    return 0;
}
