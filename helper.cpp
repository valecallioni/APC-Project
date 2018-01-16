#include "helper.hpp"

namespace help {
  bool check_empty(const std::string& s){
    //controlla se la stringa di dipendenze è vuota
    if(s[0] == '[' && s[1] == ']')
      return true;
    return false;
  }

  unsigned long read_id(std::string& s){
    //legge l'id di dipendenza eliminando le parentesi
    std::string copy;
    for (unsigned i = 0; i < s.size(); i++) {
      if(isdigit(s[i])){
        copy += s[i];
      }
    }
    return std::atol(copy.c_str());
  }

  void create_vector(const std::string& file_name, std::vector<std::vector<std::string> >& v){
    //legge il file riga per riga. Ogni riga viene memorizzata come vector di string e inserita in un vector di righe.
    std::ifstream in(file_name);
    if (in){
      std::string line;
      while (getline(in, line)) { //legge la riga
          std::stringstream sep(line);
          v.push_back(std::vector<std::string>()); //inserisco in v una riga vuota da riempire
          std::string string_name;
          while (getline(sep, string_name, ',')){ //legge tutte le parole usando come separatore la virgola
              v.back().push_back(string_name);
          }
      }
    }
  }

  unsigned int max(std::vector<double> &f1){
    unsigned int max = 0;
    for (unsigned int i=0; i<f1.size()-1; i++){
      if (f1[i]<f1[i+1])
        max = i+1;
      else
        std::swap(f1[i],f1[i+1]);
    }
    return max;
  }

  unsigned int min(std::vector<double> &f2){
    unsigned int min = 0;
    for (unsigned int i=0; i<f2.size()-1; i++){
      if (f2[i]>f2[i+1])
        min = i+1;
      else
        std::swap(f2[i],f2[i+1]);
    }
    return min;
  }

  void time_consumption(time_point start, time_point finish, std::ofstream &ofs)
  {
    std::chrono::duration<double> elapsed_seconds = finish - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t (finish);
    ofs << "Finished computation at " << std::ctime (&end_time)
              << " elapsed time: " << elapsed_seconds.count() << " s"
              << "\r\n";
  }

}
