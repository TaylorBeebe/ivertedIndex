#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;

/* @Pre: we've gotten a character and need to check if it is a letter
 * @Param: the integer value of the character
 * @Post: return true if the integer is within range of letter values
 */
bool checkCharRange(int val){
  return ((val >= 65 && val <= 90) ||(val >= 97 && val <= 122));
}

/* @Pre: string has been mapped and needs to be cleared
 * @Param: reference to string to be cleared
 * @Post: string is empty
 */
void resetString(string& s){
  s = "";
}

/* @Pre: results are in, need to print
 * @Param: takes the map to be printed
 * @Post: creates iterator to go through the keys and one to go through
 *        sets. Prints: key: <n1> <n2> ... <nm>
 */
void printMap(map<string,set<int> > m){

  map<string,set<int> >::iterator it;
  
  for (it = m.begin(); it != m.end(); it++){

    cout << it->first << ":";

    for(set<int>::iterator setIt = it->second.begin(); setIt != it->second.end(); ++setIt){
      cout << " " << *setIt;
    } 

    cout << endl;

  }
}

/* @Pre: there is a valid string that needs to be added to the map
 * @Param: a map to add to, a string key, and an int to be added to the set
 * @Post: key/value is added to the map
 */
void addToMap(map<string, set<int> >& mapToAddTo, string stringToAdd, int fileAppeared) {
  set<int> temp = mapToAddTo[stringToAdd];
  temp.insert(fileAppeared);
  mapToAddTo[stringToAdd] = temp;
}

int main(int argc, char **argv) {

  //make sure there is one argument
  if(argc != 2){
    return 1;
  }

  //used to call open()
  const char* fileToOpen = argv[1];  
  const char* subfile;

  //str: gets lines from input.txt
  //subStr: gets lines from files input.txt references
  //holds word currently being built
  string str, subStr, wordStr;

  //inFile: input.txt
  //subInFile: names of files referenced in input.txt
  ifstream inFile, subInFile;

  //map to hold words and files found in
  map<string,set<int> > invertedIndex;

  //file currently on
  int subFileNumber = 0;
  
  inFile.open(fileToOpen);

  //go through each line in input.txt and try to open the file
  while(getline(inFile, str)){

    subfile = str.c_str();
    subInFile.open(subfile);

    //go through each line in each file referenced by input.txt
    while(getline(subInFile, subStr)){

      //walk through each character in the line
      for (int i = 0; i < subStr.size(); i++){

	//check if the character is a letter.
	//if it is, add it to the word being built
	if (checkCharRange((int)subStr[i])){
	  wordStr += subStr[i];
	}

	//if the current character isn't a letter, check if a
	//string has been built that needs to be put in the map
	else if (wordStr.length() > 0){
	  addToMap(invertedIndex, wordStr, subFileNumber);
	  resetString(wordStr);
	}

	//otherwise, just clear the string as a catch-all
	else {
	  resetString(wordStr); 
	}
      }      
    }

    //after going through all lines of the file, make sure
    //it actually opened and increment the file number
    if (subInFile.is_open()){
      subFileNumber++;
    }

    //if there is a lingering string that hasn't been mapped,
    //do that now and clear the string
    if(wordStr.length() > 0){
      addToMap(invertedIndex, wordStr, subFileNumber - 1);
      resetString(wordStr);
    }
    
    //make sure to close the file
    subInFile.close();
  }

  //print the results
  printMap(invertedIndex);

  return 0;
  
}
