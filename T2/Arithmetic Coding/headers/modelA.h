#ifndef MODEL_A_DOT_H
#define MODEL_A_DOT_H

#include <iostream>
#include <stdexcept>
#include "model_metrics.h"

template<typename CODE_VALUE_ = unsigned int, 
         int CODE_VALUE_BITS_ = (std::numeric_limits<CODE_VALUE_>::digits + 3) / 2,
         int FREQUENCY_BITS_ = std::numeric_limits<CODE_VALUE_>::digits - CODE_VALUE_BITS_>
struct modelA : public model_metrics<CODE_VALUE_, CODE_VALUE_BITS_, FREQUENCY_BITS_> 
{

  typedef model_metrics<CODE_VALUE_, CODE_VALUE_BITS_, FREQUENCY_BITS_> metrics;
  typedef typename metrics::prob prob;
  typedef CODE_VALUE_ CODE_VALUE;

  using metrics::MAX_CODE;
  using metrics::MAX_FREQ;
  using metrics::CODE_VALUE_BITS;
  using metrics::ONE_FOURTH;
  using metrics::ONE_HALF;
  using metrics::THREE_FOURTHS;
  
  CODE_VALUE cumulative_frequency[258];
  bool m_frozen;
  unsigned long long m_bytesProcessed;
  
  static_assert( MAX_FREQ > 257, "Not enough code bits to represent the needed symbol library" );

  modelA() { reset(); }

  void reset()
  {
    for ( int i = 0 ; i < 258 ; i++ )
      cumulative_frequency[i] = i;

    m_bytesProcessed = 0;
    m_frozen = false;
  }

  virtual void frozen()
  {
    std::cout << "Frozen at: " << m_bytesProcessed << "\n";
  }
  
  void inline update(int c)
  {
    for ( int i = c + 1 ; i < 258 ; i++ )
      cumulative_frequency[i]++;

    if ( cumulative_frequency[257] >= MAX_FREQ ) {
      m_frozen = true;
      frozen();
    }

  }

  prob getProbability(int c)
  {
    prob p = { cumulative_frequency[c], cumulative_frequency[c+1], cumulative_frequency[257] };
    
    if ( !m_frozen ) 
      update(c);
    
    return p;
  }

  prob getChar(CODE_VALUE scaled_value, int &c)
  {
    for ( int i = 0 ; i < 257 ; i++ )
      if ( scaled_value < cumulative_frequency[i+1] ) {
        c = i;
        prob p = {cumulative_frequency[i], cumulative_frequency[i+1],cumulative_frequency[257]};
        
        if (!m_frozen)
          update(c);

        return p;
      }

      throw std::logic_error("error");
  }

  CODE_VALUE getCount() { return cumulative_frequency[257]; }
};

#endif
