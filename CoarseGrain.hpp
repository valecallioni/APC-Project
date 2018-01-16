#ifndef CoarseGrain_hpp
#define CoarseGrain_hpp

#include "Application.hpp"
#include "helper.hpp"
#include "create_application.hpp"
#include "Job.hh"
#include "Stage.hpp"
#include "Process.hpp"
#include "FineGrain.hpp"
#include "FineGrainWeights.hpp"
#include "FineGrainDerivative.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
#include <list>
#include <memory>
#include <chrono>
#include <ctime>

typedef std::chrono::milliseconds milli;
typedef std::chrono::time_point<std::chrono::system_clock> time_point;

class CoarseGrain{
  Job::time_instant d; // deadline
  Job::time_instant D; // delta
  Job::time_instant tol = 1000;
  unsigned int diff1=2, diff2=2;
  unsigned int it = 0;
  unsigned int max_it = 5;
  FineGrain* fine_grain;

public:
  CoarseGrain(Job::time_instant deadline);
  void min(std::ofstream &ofs, Process &p, std::string argv);

};

#endif
