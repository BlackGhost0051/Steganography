// Made by Black Ghost | 2024

// ' ' = 0
// '\t' = 1

#include <iostream>
#include <fstream>

using namespace std;


string getText(string bytes){
  int i,j,k, start = 0, end, line_length;
  string result;

  for(i = 0; i < bytes.length(); i++){
    if(bytes[i] == '\n'){
      end = i-1;

      line_length = end - start;
      if(line_length >= 8){
  
        char c = 0; //
        int byte_start = end - 7; // last 8 bits

        for(j=byte_start; j <= end; j++){
      
          // cout << bytes[j];
          c = (c << 1) | (bytes[j] - '0');
        }
        // cout << "\nSumbol: " << c << endl;
        result += c;
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
      result_butes += "\n";
    } else if (myChar == '\t'){
      result_butes += "1";
    } else if (myChar == ' '){
      result_butes += "0";
    }
  }

  MyReadFile.close();


  cout << "====  Start input text  ====\n" << result_butes << "====  End input text  ===="<< endl;

  cout << "\nResult = " << getText(result_butes) << endl;


  return 0;
}
