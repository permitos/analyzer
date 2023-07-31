## Utility description

This "name" utility is designed to process packages and generates a json file with a description of these packages and performs the following tasks:
1) receives lists of binary packages of 2 branches;
2) makes a comprasion of the received package lists and outputs JSON which will display: 
   - all packages that are in the 1st but not int the 2nd;
   - all packages that are in the 2nd but not in the 1st;
   - all packages whose version-release is greater in the 1st than in the 2nd;
 
Packages are received from: https://rdb.altlinux.org/api/ (method "/export/branch_binary_packages/{branch}")
In the output JSON file, the descriptions "first-packages", "second-packages" and "third-packages" match the conditions described above.

## Installation

# Ubuntu/Debian

In order to run this utility you must first install cpprestsdk:
```
sudo apt-get install libcpprest-dev
```

# Deepin

Follow to install these packages:
```
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install gcc-c++
sudo apt-get install libcpprest-devel
sudo apt-get install zlib-devel
sudo apt-get install boost-filesystem-devel
```

## Launch

Than build the shared library using "CMake":
```
cmake .
make
```

Finally copy the generated shared library as follows:
```
sudo cp libanalyzer.so /usr/lib
sudo ldconfig
```

Run the utility by executing the command:
```
./main
```
