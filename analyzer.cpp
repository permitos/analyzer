#include "analyzer.h"

PackagesAnalyzer::PackagesAnalyzer(): _client(URI) {

  cout << "Start of the program.";
}

PackagesAnalyzer::~PackagesAnalyzer() {}

PackagesAnalyzer::
        PackagesAnalyzer(string_t fisrtNameBranch, string_t secondNameBranch):
        PackagesAnalyzer() {
  initializeBranches(fisrtNameBranch, secondNameBranch);                 
}

void PackagesAnalyzer::
     initializeBranches(string_t fisrtNameBranch, string_t secondNameBranch) {

  cout << " Receiving packages:" << endl;

  _jvFirstBranch = getBranch(fisrtNameBranch);
  _jvSecondBranch = getBranch(secondNameBranch);
  
  cout << "Packages have been received." << endl;
}

json::value PackagesAnalyzer::getBranch(string_t nameBranch) {
  
  pplx::task<http_response> response = _client.request(
		web::http::methods::GET, RESPONSE + nameBranch);

  pplx::task<json::value> jv = response.then([=]
	(pplx::task<http_response> task) {
	
	http_response response = task.get();

	if (response.status_code() != CODE_SUCCESS) {
	  cout << ("ERROR: CODE- " + to_string(response.status_code()));
	  exit(1);
	}
	
	std::cout << "SUCCESS CODE-" +  to_string(CODE_SUCCESS) << 
	             " {branch-name -> " << nameBranch << "}" <<endl;

	return (pplx::task<json::value>) response.extract_json();
  });
  
  jv.wait();
  return jv.get();
}

void PackagesAnalyzer::initializeOutputStructure() {

  cout << "Performing the first step of the analysis. Step 1/3" << endl;
  initializeOutputStructure_DifferentPackages(true);
  
  cout << "Performing the second step of the analysis. Step 2/3" << endl;
  initializeOutputStructure_DifferentPackages(false);
  
  cout << "Performing the third step of the analysis. Step 3/3" << endl;
  initializeOutputStructure_ReleaseVersion();
  
  cout << "Data analysis successfully completed." << endl;
}

void PackagesAnalyzer::initializeOutputStructure_DifferentPackages(bool isFirst) {

  if(isFirst)
    initializeOutputStructure_DifferentPackages(_jvFirstBranch, _jvSecondBranch, "first_packages");
  else
    initializeOutputStructure_DifferentPackages(_jvSecondBranch, _jvFirstBranch, "second_packages");
}

void PackagesAnalyzer::initializeOutputStructure_ReleaseVersion() {
  
  auto packagesFirst = _jvFirstBranch.at("packages").as_array();
  auto packagesSecond = _jvSecondBranch.at("packages").as_array();
  map<string_t, json::value> jvSecondMap;
  vector<string_t> jvFieldsName = {"name", "arch"};
  vector<string_t> jvFieldsVersion = {"release", "version"};
  
  for(json::value jv : packagesSecond)
    jvSecondMap[getDescriptionPackage(jvFieldsName, jv)] = jv;
    
  for (json::value jv : packagesFirst) {
  
    string_t nameFirstPackage = getDescriptionPackage(jvFieldsName, jv);
      
    if (jvSecondMap.find(nameFirstPackage) != jvSecondMap.end()) {
         
    json::value secondPackage = jvSecondMap[nameFirstPackage];
        
    if(getDescriptionPackage(jvFieldsVersion, jv) > getDescriptionPackage(jvFieldsVersion, secondPackage)) 
      _jvOutput["third_packages"][_jvOutput["third_packages"].size()] = jv;
    }
  }
}

void PackagesAnalyzer::initializeOutputStructure_DifferentPackages(json::value firstBranch, json::value secondBranch, string_t nameFieldPackages) {

  auto packagesFirst = firstBranch.at("packages").as_array();
  auto packagesSecond = secondBranch.at("packages").as_array();
  map<string_t, json::value> jvSecondMap;
  vector<string_t> jvFields = {"name", "arch", "release", "version"};
  
  for(json::value jv : packagesSecond)
    jvSecondMap[getDescriptionPackage(jvFields, jv)] = jv;
    
  for (json::value jv : packagesFirst) {
      if (jvSecondMap.find(getDescriptionPackage(jvFields, jv)) == jvSecondMap.end()) 
        _jvOutput[nameFieldPackages][_jvOutput[nameFieldPackages].size()] = jv;
  }
}

string_t PackagesAnalyzer::getDescriptionPackage(vector<string_t> fields, json::value jv) {

  string_t description = "";
  
  for(string_t field: fields) {
    description += jv.at(field).as_string() + " ";
  }
  
  return description;
}

void PackagesAnalyzer::outInFile() {

  cout << "The analyzed data is uploaded to a file..." << endl;

  ofstream out("result_analysis_packages.txt");
  
  if(out.is_open()) {
  
    out << _jvOutput.serialize() << endl;
    cout << "Packet analysis results were written to file \"result_analysis_packages.txt\"" << endl;
  }
  else
    cout << "Failed to write to file!" << endl;
  
  out.close();
}


