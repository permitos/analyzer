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
