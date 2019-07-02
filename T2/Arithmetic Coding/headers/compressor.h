#ifndef COMPRESSOR_DOT_H
#define COMPRESSOR_DOT_H

#include <stdexcept>

#include "byteio.h"
#include "bitio.h"

template<typename INPUT, typename OUTPUT, typename MODEL>
class compressor
{

  typedef typename MODEL::CODE_VALUE CODE_VALUE;
  typedef typename MODEL::prob prob;

public :

  compressor (INPUT &input_, OUTPUT &output_, MODEL &model_) 
  : input(input_),
    output(output_),
    model(model_) 
    {}

  int operator()()
  {
    int pending_bits = 0;
    
    CODE_VALUE low = 0;
    CODE_VALUE high = MODEL::MAX_CODE;
    
    while (true) {
      int c = input.getByte();
      
      if ( c == -1 )
        c = 256;
            
      prob p = model.getProbability( c );
      
      CODE_VALUE range = high - low + 1;
      
      high = low + (range * p.high / p.count) - 1;
      low = low + (range * p.low / p.count);
      
      while (true) {
        
        if ( high < MODEL::ONE_HALF )
          put_bit_plus_pending(0, pending_bits);
        
        else if ( low >= MODEL::ONE_HALF )
          put_bit_plus_pending(1, pending_bits);
        
        else if ( low >= MODEL::ONE_FOURTH && high < MODEL::THREE_FOURTHS ) {
          pending_bits++;
          low -= MODEL::ONE_FOURTH;  
          high -= MODEL::ONE_FOURTH;  
        
        } else
          break;
        
        high <<= 1;
        high++;
        
        low <<= 1;
        
        high &= MODEL::MAX_CODE;
        low &= MODEL::MAX_CODE;

      }

      if ( c == 256 )
        break;
    }

    pending_bits++;
    
    if ( low < MODEL::ONE_FOURTH )
      put_bit_plus_pending(0, pending_bits);
    
    else
      put_bit_plus_pending(1, pending_bits);
        
    return 0;
  }

  inline void put_bit_plus_pending(bool bit, int &pending_bits)
  {
    output.put_bit(bit);
    
    for ( int i = 0 ; i < pending_bits ; i++ )
      output.put_bit(!bit);
    
    pending_bits = 0;
  }

private :
  OUTPUT &output;
  INPUT &input;
  MODEL &model;
};

template<typename INPUT, typename OUTPUT, typename MODEL>
int compress(INPUT &source, OUTPUT &target, MODEL &model)
{
  input_bytes<INPUT> in(source);
  output_bits<OUTPUT> out(target);

  compressor<input_bytes<INPUT>, output_bits<OUTPUT>, MODEL> c(in,out, model);
  
  return c();
}

#endif
