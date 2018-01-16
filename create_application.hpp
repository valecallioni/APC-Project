#ifndef CREATE_APP
#define CREATE_APP

#include "Application.hpp"
#include "helper.hpp"
#include "Job.hh"
#include "Stage.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
#include <list>

namespace c_app{
  //creazione di app
  Application create_app(const std::vector<std::string>& file_names);

}
#endif
