#include <iostream>
#include <fstream>
#include <iostream>

#include "output.hpp"

std::string ReadFile(std::string path) {
    using namespace std;
    ifstream inputfile;
    int length;
    char * buffer;
    inputfile.open (path.c_str(), ios::binary );

    // get length of file:
    inputfile.seekg (0, ios::end);
    length = inputfile.tellg();
    inputfile.seekg (0, ios::beg);

    // allocate memory:
    buffer = new char [length];

    // read data as a block:
    inputfile.read(buffer,length);

    inputfile.close();
    string contetns = buffer; 
    delete[] buffer;
    return contetns;
}