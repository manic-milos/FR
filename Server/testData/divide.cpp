// Implementation of the Socket class.

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){

  ifstream wholeFile;
  ofstream trainFile;
  ofstream testFile;

  wholeFile.open ("whole.csv");
  trainFile.open ("train.csv", ios::out);
  testFile.open ("test.csv", ios::out);

  string line;
  string sId;
  string lastId;
  int i=0;

  int training;

  if(argc == 2)
  {
    istringstream ss1(argv[1]);
    ss1 >> training;
  }
  else
  {
    cout << argc << endl;
    training = 2;
  }

  while( getline(wholeFile, line) )
  {

    if(line.find("_p") != string::npos)
      continue;

    size_t found = line.find(";");
    sId = line.substr(found);

    if(lastId != sId)
    {
      i=0;
      lastId = sId;
    }

    if(i<training)      
      trainFile << line << endl;
    else
      testFile << line << endl;

    i++;
  }


  wholeFile.close();
  trainFile.close();
  testFile.close();



  return 0;
}