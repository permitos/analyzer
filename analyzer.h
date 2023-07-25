#pragma once
#ifndef ANALYZER
#define ANALYZER

#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

using namespace web; 
using namespace web::http;
using namespace web::http::client; 
using namespace concurrency::streams;
using namespace std;

class PackagesAnalyzer {

  inline static const string_t URI = "https://rdb.altlinux.org/api/";
  inline static const string_t RESPONSE = "/export/branch_binary_packages/";
  inline static const int CODE_SUCCESS = 200;
  
  http_client _client; // used to maintain a connection to an HTTP service
  
  json::value _jvFirstBranch;  // description of packages of the first branch
  json::value _jvSecondBranch; // description of packages of the second branch
  json::value _jvOutput;       // output description of packages
  
  json::value getBranch(string_t nameBranch); // getting branch handles by name
  
public:

  void initializeBranches(string_t fisrtNameBranch, string_t secondNameBranch); // branch handles initialization
  
  PackagesAnalyzer();
  PackagesAnalyzer(string_t fisrtNameBranch, string_t secondNameBranch);
  ~PackagesAnalyzer();
};

#endif // ANALYZER
