#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

bool checkCharRange(int val){
  return ((val >= 65 && val <= 90) ||(val >= 97 && val <= 122));
}

void resetString(string& s){
  s = "";
}

void printMap(map<string, set<int> >){
  
  for (it = invertedIndex.begin(); it != invertedIndex.end(); it++){

    cout << it->first << ":";

    for(set<int>::iterator setIt = it->second.begin(); setIt != it->second.end(); ++setIt){
      cout << " " << *setIt;
    } 

    cout << endl;

  }
}

int main(int argc, char **argv) {
  
  if(argc != 2){
    return 1;
  }

  const char* fileToOpen = argv[1];  
  const char* subfile;
  
  string str, subStr, wordStr;

  ifstream inFile, subInFile;

  map<string,set<int> > invertedIndex;
  map<string, set<int> >::iterator it;

  set<int> temp;
  
  int subFileNumber = 0;
  
  inFile.open(fileToOpen);

  while(getline(inFile, str)){

    subfile = str.c_str();
    subInFile.open(subfile);

    while(getline(subInFile, subStr)){

      for (int i = 0; i < subStr.size(); i++){

	if (checkCharRange((int)subStr[i])){

	  wordStr += subStr[i];

	} else if (wordStr.length() > 0){

	  temp = invertedIndex[wordStr];
	  temp.insert(subFileNumber);
	  invertedIndex[wordStr] = temp;
	  resetString(wordStr);
	  
	} else {

	  resetString(wordStr); 

	}	
      }      

      if(wordStr.length() > 0){
	resetString(wordStr);
      }
      
      if (subInFile.is_open()){
	subFileNumber++;
      }
      
      subInFile.close();
    }
  }
  
  return 0;
  
}
