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

void PackagesAnalyzer::initializeOutputStructure_DifferentPackages(bool isFirst) {

  if(isFirst)
    initializeOutputStructure_DifferentPackages(_jvFirstBranch, _jvSecondBranch, "first_packages");
  else
    initializeOutputStructure_DifferentPackages(_jvSecondBranch, _jvFirstBranch, "second_packages");
}

void PackagesAnalyzer::initializeOutputStructure_DifferentPackages(json::value firstBranch, json::value secondBranch, string_t nameFieldPackages) {

  auto packagesFirst = firstBranch.at("packages").as_array();
  auto packagesSecond = secondBranch.at("packages").as_array();
  map<string_t, json::value> jvSecondMap;
  vector<string_t> jvFields = {"name", "arch", "release", "version"};
  
  // ADD METHOD getDescriptionPackage(vector<string_t>, json::value)
  
  /*for(json::value jv : packagesSecond)
    jvSecondMap[getDescriptionPackage(jvFields, jv)] = jv;
    
  for (json::value jv : packagesFirst) {
      if (jvSecondMap.find(getDescriptionPackage(jvFields, jv)) == jvSecondMap.end()) 
        _jvOutput[nameFieldPackages][_jvOutput[nameFieldPackages].size()] = jv;
  }*/
}
