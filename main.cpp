#include "analyzer.h"

int main(int argc, char* argv[]) {
	
  string_t firstBranchName, secondBranchName = "";
  
  cout << "Enter the name of the first branch:" << endl;
  getline(cin, firstBranchName);
  
  cout << "Enter the name of the second branch:" << endl;
  getline(cin, secondBranchName);	
	
  PackagesAnalyzer analyzer(firstBranchName, secondBranchName);
  analyzer.initializeOutputStructure();
  analyzer.outInFile();
	
  return 0;
}
