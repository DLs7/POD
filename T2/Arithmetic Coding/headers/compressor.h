#ifndef COMPRESSOR_DOT_H
#define COMPRESSOR_DOT_H

#include <stdexcept>

#include "byteio.h"
#include "bitio.h"

#ifdef LOG
#include <iomanip>
#include <iostream>
#endif

template<typename INPUT, typename OUTPUT, typename MODEL>
class compressor
{
  typedef typename MODEL::CODE_VALUE CODE_VALUE;
  typedef typename MODEL::prob prob;
public :
  compressor(INPUT &input, OUTPUT &output, MODEL &model ) 
  : m_input(input),
    m_output(output),
    m_model(model)
  {
  }
  int operator()()
  {
#ifdef LOG
    std::ofstream log("compressor.log");
    log << std::hex;
#endif
    int pending_bits = 0;
    CODE_VALUE low = 0;
    CODE_VALUE high = MODEL::MAX_CODE;
    for ( ; ; ) {
      int c = m_input.getByte();
      if ( c == -1 )
        c = 256;
#ifdef LOG
      log << std::hex << "0x" << std::setw(2) << std::setfill('0') << c;
      if ( c > 0x20 && c <= 0x7f )
        log << "(" << char(c) << ")";
      log << " 0x" << low << " 0x" << high << " => ";
#endif
      prob p = m_model.getProbability( c );
      CODE_VALUE range = high - low + 1;
      high = low + (range * p.high / p.count) - 1;
      low = low + (range * p.low / p.count);
#ifdef LOG
      log << "0x" << low << " 0x" << high << "\n";
#endif
      for ( ; ; ) {
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
#ifdef LOG
    log.close();
#endif
    return 0;
  }

  inline void put_bit_plus_pending(bool bit, int &pending_bits)
  {
    m_output.put_bit(bit);
    for ( int i = 0 ; i < pending_bits ; i++ )
      m_output.put_bit(!bit);
    pending_bits = 0;
  }
private :
  OUTPUT &m_output;
  INPUT &m_input;
  MODEL &m_model;
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
