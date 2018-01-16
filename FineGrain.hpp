#ifndef FineGrain_hpp
#define FineGrain_hpp

#include <vector>
#include <algorithm>
#include <memory>
#include "Process.hpp"
#include "Job.hh"

class FineGrain{
protected:
  std::vector<double> weights;
public:

  FineGrain()=default;

  const std::vector<double>& get_weights() const{ return weights; };

  virtual void set_weights(Process&, std::ofstream &ofs) = 0;

  virtual void find_min(Process&, std::ofstream &ofs) = 0;

};

#endif
