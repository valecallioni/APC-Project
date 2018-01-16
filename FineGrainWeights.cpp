#include "FineGrainWeights.hpp"

void FineGrainWeights::set_weights(Process &process, std::ofstream &ofs)
{
  weights.clear();
  for (unsigned int k=0; k<process.size(); k++)
    weights.push_back(process[k]->get_weight());

  std::sort(weights.begin(), weights.end());
  std::reverse(weights.begin(), weights.end());

  std::vector<unsigned int> order_idx;
  ofs << "Descending order of applications considering their weights \r\n";

  for (auto w:weights){
    for (unsigned int k=0; k<process.size(); k++){
      if (process[k]->get_weight()==w)
        order_idx.push_back(k+1);
    }
  }

  for (auto i:order_idx)
    ofs << "[" << i << "] ";
  ofs << "\r\n \r\n";

}

void FineGrainWeights::find_min(Process &process, std::ofstream &ofs)
{
  unsigned int it = 0;
  unsigned int max_it = 1000;

  // if we have room, we remove one core at a time starting from the one that cost the more
  if (process.total_real_time() < process.get_d()){
    for (auto w:weights){
      for (unsigned int k=0; k<process.size(); k++){
        if (process[k]->get_weight()==w){
          unsigned int u=0;
          while (process.total_real_time() < process.get_d() && it<=max_it){
            process[k]->set_n_core(process[k]->get_n_core()-1);
            u++;
            it++;
            ofs << "Application " << k+1 << " nr. of cores: " << process[k]->get_n_core() << "\r\n";
          }
          if(u>0)
            process[k]->set_n_core(process[k]->get_n_core()+1);
        }
      }
    }
    ofs << "\r\n \r\n";
  }

  // otherwise, we have to we add one core at a time (the one that cost less)

  else {
    it = 0;
    for (unsigned int k=0; k<process.size(); k++){
      if (process[k]->get_weight()==weights.back()){
        while (process.total_real_time() >= process.get_d() && it<=max_it){
          process[k]->set_n_core(process[k]->get_n_core()+1);
          it++;
          ofs << "Application " << k+1 << " nr. of cores: " << process[k]->get_n_core() << "\r\n";
        }
      }
    }
    ofs << "\r\n \r\n";
  }

}
