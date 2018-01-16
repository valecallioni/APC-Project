#include "Application.hpp"
#include "helper.hpp"
#include "create_application.hpp"
#include "Job.hh"
#include "Stage.hpp"
#include "Process.hpp"
#include "FineGrain.hpp"
#include "FineGrainWeights.hpp"
#include "FineGrainDerivative.hpp"
#include "CoarseGrain.hpp"
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
#include <cstring>

typedef std::chrono::milliseconds milli;
typedef std::chrono::time_point<std::chrono::system_clock> time_point;

int main(int argc, char** argv) {
  //read csv files and create the applications

  std::ofstream buffer("Output.txt");

  Job::time_instant d;
  Process p;

  std::string ap, job, st, task, line, nc, deadline, weight;
  std::ifstream ifs(argv[1]);

  Application app;

  while (getline(ifs, line)) {
    std::istringstream iss(line);
    iss >> ap >> job >> st >> task >> nc >> deadline >> weight;

    std::vector<std::string> file_names;
    file_names.push_back(ap);
    file_names.push_back(job);
    file_names.push_back(st);
    file_names.push_back(task);
    file_names.push_back(nc);
    file_names.push_back(deadline);
    file_names.push_back(weight);

    app = c_app::create_app(file_names);
    p.push_back(app);
  }

  // we set the total deadline as 2 times the minimal one
  d = (2)*p.min_d_line();
  p.set_d(d);

  buffer << "The given problem has as minimum deadline " << d/2 << " milliseconds. \r\n \r\n";

  for (unsigned int k=0; k<p.size(); k++)
    buffer << "Application " << p[k]->get_id_app() << " will be considered as Application " << k+1 << "\r\n";

    buffer << "\r\n";

  // control is a boolean that is true if we can proceed with the minimum problem
  // if the deadline is big enough
  bool control;
  control = p.distribute_d_line();

  for (int i=0; i<argc; i++)
  std::cout << "argv[" << i << "]=" << argv[i] << std::endl;

  if (strcmp(argv[2], "weights") == 0 || strcmp(argv[2], "derivative") == 0){

    if (control){
      for (unsigned int k=0; k<p.size(); k++){
        buffer << "Application " << k+1 << " used " << p[k]->get_n_core_log() << " cores and the initial deadline is " << p[k]->get_d_line();
        p[k]->set_n_core(p[k]->get_alpha()/(p[k]->get_d_line()-p[k]->get_beta()));
        buffer << " that requires " << p[k]->get_n_core() << " nr. of cores." << "\r\n";
      }

      buffer << "\r\n";

      CoarseGrain coarse_grain(d);

      // after the coarse grain search, the min method calls the fine grain search
      // following the instructions given by the user
      coarse_grain.min(buffer, p, argv[2]);

      buffer << "\r\n";
      buffer << "Final results: \r\n";
      for (unsigned int k=0; k<p.size(); k++)
        buffer << "Application " << k+1 << " requires " <<  p[k]->get_n_core() << " nr. of cores." << "\r\n";

      buffer << "The final total cost is " << p.total_cost() << "\r\n";
      buffer << "Deadline: " << d << " and total_real_time: " << p.total_real_time() << "\r\n";
    }

    else
      buffer << "Deadline unfeasible! Program ended.";

  }

  else
    buffer << "Method inserted not valid. Program ended.";


  return 0;
}
