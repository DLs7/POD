#include <iostream>
#include <fstream>

#include "modelA.h"
#include "compressor.h"

int main(int argc, char* argv[])
{
  if ( argc < 3 ) {
    std::cout << "Missing arguments.\n";
    std::cout << "Example: compressor \"file.txt\" \"compressed_file.txt\"\n";
    return -1;
  }

  try {
    std::ifstream input(argv[1], std::ifstream::binary);
    std::ofstream output(argv[2], std::ofstream::binary);
    modelA<int, 16, 14> cmodel;
  
    compress(input, output, cmodel);
    return 0;
    
  } catch (std::exception &ex) {
    return -1;
  }
}
