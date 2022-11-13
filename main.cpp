#include "ArgumentManager.h"
//#include "queue.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  //my_queue output;
/*
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
*/
  
    ifstream input("input1.txt");
    ofstream out("output1.txt");
  
  string inStr; // input string

  while (getline(input, inStr)) {
    if (inStr.size() != 0) {
        cout<<  inStr<<endl;
    }
  }
}