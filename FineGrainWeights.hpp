#ifndef FineGrainWeights_hpp
#define FineGrainWeights_hpp

#include "FineGrain.hpp"

class FineGrainWeights: public FineGrain{
public:

  FineGrainWeights()=default;

  // weights of applications are the cost of a single core and they are
  // ordered in descending order
  void set_weights(Process&, std::ofstream &ofs);

  // if we have room (total real time is less than the deadline) we add one
  // core at a time following the order of the weights, otherwise we remove
  // one core at a time from the application that has the last weight
  void find_min(Process&, std::ofstream &ofs);
};

#endif
