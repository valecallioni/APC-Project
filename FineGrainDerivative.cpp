#include "FineGrainDerivative.hpp"

void FineGrainDerivative::set_weights(Process &process, std::ofstream &ofs)
{
  weights.clear();
  for (unsigned int k=0; k<process.size(); k++)
    weights.push_back(process[k]->get_weight()/(process[k]->get_alpha()/double(process[k]->get_n_core()*(process[k]->get_n_core()-1))));

  std::sort(weights.begin(), weights.end());
  std::reverse(weights.begin(), weights.end());

  std::vector<unsigned int> order_idx;
  ofs << "Descending order of applications considering their weights \r\n";

  for (auto w:weights){
    for (unsigned int k=0; k<process.size(); k++){
      if (process[k]->get_weight()/(process[k]->get_alpha()/double(process[k]->get_n_core()*(process[k]->get_n_core()-1)))==w)
        order_idx.push_back(k+1);
    }
  }

  for (auto i:order_idx)
    ofs << "[" << i << "] ";
  ofs << "\r\n \r\n";
}

void FineGrainDerivative::find_min(Process &process, std::ofstream &ofs)
{
  unsigned int it = 0;
  unsigned int max_it = 10;
  if (process.total_real_time() < process.get_d()){
    for (auto w:weights){
      for (unsigned int k=0; k<process.size(); k++){
        if (process[k]->get_weight()/(process[k]->get_alpha()/double(process[k]->get_n_core()*(process[k]->get_n_core()-1)))==w){
          unsigned int u=0;
          while (process.total_real_time() < process.get_d()){
            process[k]->set_n_core(process[k]->get_n_core()-1);
            ofs << "Application " << k+1 << " nr. of cores: " << process[k]->get_n_core() << "\r\n";
            u++;
          }
          if(u>0)
            process[k]->set_n_core(process[k]->get_n_core()+1);
        }
      }
      ofs << "\r\n";
      set_weights(process, ofs);
    }
    ofs << "\r\n \r\n";
  }

  else {
    for (unsigned int k=0; k<process.size(); k++){
      if (process[k]->get_weight()/(process[k]->get_alpha()/double(process[k]->get_n_core()*(process[k]->get_n_core()-1)))==weights.back()){
        while (process.total_real_time() >= process.get_d() && it<=max_it){
          process[k]->set_n_core(process[k]->get_n_core()+1);
          ofs << "Application " << k+1 << " nr. of cores: " << process[k]->get_n_core() << "\r\n";
          it++;
        }
      }
      set_weights(process, ofs);
    }
    ofs << "\r\n \r\n";
    // if (it==max_it+1)
      // std::cout << "While loop ended, reached max number of iterations" << std::endl;
  }

}
