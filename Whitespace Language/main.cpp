// https://en.wikipedia.org/wiki/Whitespace_(programming_language)
// https://codernet.ru/articles/drugoe/whitespace_yazyik_programmirovaniya_s_samyim_neobyichnyim_sintaksisom/
// https://www.ascii-code.com/
// ' ' = 0
// '\t' = 1

#include <iostream>
#include <fstream>

using namespace std;

string find_Chars_in_String(string bytes){
    string result;
    int i = 0;

    while(true){
      if(bytes[i] == '\0'){
        return result;
      }
    }
    return "Error";
}


string getText(string bytes){
  int i,j, start = 0, end, line_length;
  string result;

  for(i = 0; i < bytes.length(); i++){
	if(bytes[i] == '\n'){
		end = i-1;

		line_length = end - start;
		if(line_length >= 8){

			cout << "good " << start << " " << end << endl <<  "Line = "<< line_length  << endl;
			cout << "\n\n START = " << bytes[start]  << endl;


			for(j=start; j <= end; j++){
				cout << bytes[j];
			}


			cout << "\n STOP = " <<  bytes[end] << endl;
		}

		j=i;
		while(j != bytes.length() - 1){
			if(bytes[j] != '\n'){
				start = j;
				break;
			}
			j++;
		}

	}
  }

  return result;
}


int main() {
    char myChar;
    string result_butes;
    string bytes;
    ifstream MyReadFile;


    MyReadFile.open("input.txt");

    if (!MyReadFile.is_open()) {
        cout << "Failed to open the file" << endl;
        return 1;
    }

    while (MyReadFile.get(myChar)) {
        if (myChar == '\n') {
            cout << "\\n";
            result_butes += "\n";
        } else if (myChar == '\t'){
            cout << "\\t";
            result_butes += "1";
        } else if (myChar == ' '){
            cout << "\\s";
            result_butes += "0";
        }
        cout << myChar;
    }

    MyReadFile.close();


    cout << "\n\nResult:\n" << result_butes << endl;

    cout << "\n\nResult: "<< getText(result_butes) << endl;

//    find_Chars_in_String("test");

    return 0;
}
