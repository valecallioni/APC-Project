//CONTROLLARE LETTURA FILE
#include "Stage.hpp"

void Stage::set_dependencies(const std::vector<id_type> v){
  dependencies = v;
};

void Stage::set_max (const std::vector<time_instant>& v){
  //max execution time in a stage
  time_instant temp = 0;
  for(auto t : v){
    if(t > temp){
      temp = t;
    }
  }
  max = temp;
}

void Stage::set_min (const std::vector<time_instant>& v){
  //min execution time in a stage
  time_instant temp = v[0];
  for(auto t : v){
    if(t < temp){
      temp = t;
    }
  }
  min = temp;
}

void Stage::set_avg (const std::vector<time_instant>& v){
  //avg execution time in a stage
  time_instant sum = 0;
  for(auto t : v){
    sum += t;
  }
  avg = sum/v.size();
}

void Stage::prints() const{
  std::cout  << '\n';
  std::cout << "Id stage: " << id_Stage << '\n' << " avg time: " << this->get_avg() << '\n';
  std::cout << "Number of tasks: " << n_tasks << '\n';
  // if(dependencies.empty()){
  //   std::cout << "No dependencies on other stages" << '\n';
  // }
  // else{
  //   std::cout << "dependencies on stages: " << '\n';
  //   for (size_t i = 0; i < dependencies.size(); i++) {
  //     std::cout << dependencies[i] << " ";
  //   }
  //   std::cout << '\n';
  // }
}

Stage& Stage::operator=(const Stage& stage){
  id_Stage = stage.get_ID();
  max = stage.get_max();
  min = stage.get_min();
  avg = stage.get_avg();
  n_tasks = stage.get_n_tasks();
  dependencies = stage.get_depend();
  return *this;
}
