#ifndef  HELPER
#define HELPER

// #include "Schedule.hh"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <list>
#include <algorithm>
#include <chrono>
#include <ctime>

typedef std::chrono::milliseconds milli;
typedef std::chrono::time_point<std::chrono::system_clock> time_point;

namespace help {
  typedef unsigned int id_type;

  //legge l'id di dipendenza
  unsigned long read_id(std::string& s);

  // crea un vettore di vettori di stringhe da file
  void create_vector(const std::string& file_name, std::vector<std::vector<std::string> >& v);

  //controlla se la stringa di dipendenze è vuota
  bool check_empty(const std::string& s);

  unsigned int max(std::vector<double>&);

  unsigned int min(std::vector<double>&);

  void time_consumption(time_point start, time_point finish, std::ofstream &ofs);
}
#endif
