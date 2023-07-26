cmake_minimum_required(VERSION 3.0)
project(libanalyzer) 
find_package(cpprestsdk REQUIRED)                
add_library(analyzer SHARED analyzer.cpp)   
add_executable(main main.cpp)           
include (GenerateExportHeader)          
GENERATE_EXPORT_HEADER(analyzer           
    BASE_NAME analyzer
    EXPORT_MACRO_NAME analyzer_EXPORTS
    EXPORT_FILE_NAME analyzer_EXPORTS.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)
target_link_libraries(main analyzer
                      analyzer cpprestsdk::cpprest)
