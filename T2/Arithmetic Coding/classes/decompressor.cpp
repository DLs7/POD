#include <iostream>
#include <fstream>

#include "modelA.h"
#include "decompressor.h"

int main(int argc, char* argv[])
{
  if ( argc < 3 ) {
    std::cout << "Missing arguments.\n";
    std::cout << "Example: decompressor \"compressed_file.txt\" \"decompressed_file.txt\"\n";
    return -1;
  }
  try {
    std::ifstream input(argv[1], std::ifstream::binary);
    std::ofstream output(argv[2], std::ofstream::binary);
    modelA<int, 16, 14> cmodel;
    cmodel.dump("cmodel", std::clog);

    decompress(input, output, cmodel);
    return 0;
  }
  catch (std::exception &ex)
  {
    return -1;
  }
  
}
