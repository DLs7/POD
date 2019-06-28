#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>

int main(int argc, char * argv[]) {
  double val = compress("abcdWXYZ"); //this will be more interesting
  std::cout << "Compressed value: " 
            << std::setprecision(15)
            << val << "\n";
  std::string result = decompress(val);
  std::cout << "Decompressed result: " << result << "\n";
  return 0;
}