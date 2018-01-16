#ifndef Process_hpp
#define Process_hpp

#include <memory>
#include <utility>
#include "Application.hpp"
#include "create_application.hpp"

class Process
{
  std::vector<std::shared_ptr<Application>> applications;
  Job::time_instant d_line_tot;

public:
  Process(const Job::time_instant d):d_line_tot(d){};
  Process()=default;

  std::shared_ptr<Application> operator[](unsigned int);
  unsigned int size() const {return applications.size();};

  std::vector<std::shared_ptr<Application>>& get_app() { return applications; }
  Job::time_instant get_d() const {return d_line_tot;};
  void set_d(Job::time_instant deadline){ d_line_tot=deadline; };

  void push_back(Application&);

  // divide the deadline among the applications using the given order
  bool distribute_d_line();

  // find the correct applications to add or remove cores
  std::pair<unsigned int, unsigned int> delta(Job::time_instant D);

  // evaluate the old cost and the new one if the number of cores of the applications
  // found by the delta method is set
  std::pair<double, double> evaluate_costs(unsigned int max, unsigned int min) const;

  // set the number of cores
  void reset_core_dline(unsigned int max, unsigned int min, Job::time_instant D);

  double total_cost() const;
  Job::time_instant total_real_time() const;
  Job::time_instant min_d_line();
};

#endif
