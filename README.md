## Utility description

This "name" utility is designed to process packages and generates a json file with a description of these packages and performs the following tasks:
1) receives lists of binary packages of 2 branches;
2) makes a comprasion of the received package lists and outputs JSON which will display: 
   - all packages that are in the 1st but not int the 2nd;
   - all packages that are in the 2nd but not in the 1st;
   - all packages whose version-release is greater in the 1st than in the 2nd;
 
Packages are received from: https://rdb.altlinux.org/api/ (method "/export/branch_binary_packages/{branch}")

## Installation and launch

In order to run this utility you must first install cpprestsdk:
```
sudo apt-get install libcpprest-dev
```

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
