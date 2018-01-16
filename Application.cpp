#include "Application.hpp"

void Application::set_id(const std::string& id){
  id_application = id;
}

void Application::add_job(Job j){
  jobs.push_back(j);

}

void Application::add_stage(Stage s){
  stages.push_back(s);
}

Job::time_instant Application::execution_time_avg() const{
  //return the approximate execution time_instant
  //this method uses the following formula: sum of wave * stage average time
  Job::time_instant sum = 0;
  for(auto s : stages){
    if(s.get_n_tasks() % n_core != 0){
      sum += s.get_avg();
    }
    unsigned coeff = s.get_n_tasks()/n_core;
    sum += coeff * s.get_avg();
  }
  return sum;
}
Job::time_instant Application::execution_time_avg(unsigned int n) const{
  //return the approximate execution time_instant
  //this method uses the following formula: sum of wave * stage average time
  Job::time_instant sum = 0;
  for(auto s : stages){
    if(s.get_n_tasks() % n != 0){
      sum += s.get_avg();
    }
    unsigned coeff = s.get_n_tasks()/n;
    sum += coeff * s.get_avg();

  }
  return sum;
}

void Application::print() const{
  std::cout << "Application name: " << id_application << '\n';
  std::cout << "dead: " << deadline << '\n';
}

void Application::print_job() const{
  print();
  for(auto j : jobs){
    j.printj();
  }
}

void Application::print_stage() const{
  // print();
  //print_job();
  for(auto s : stages){
    s.prints();
  }
}

Application& Application::operator=(const Application& app){
  id_application = app.get_id_app();
  submission_time = app.get_submission_time();
  deadline = app.get_deadline();
  jobs = app.get_jobs();
  stages = app.get_stages();
  alpha = app.get_alpha();
  beta = app.get_beta();
  n_core = app.get_n_core();
  n_core_log = app.get_n_core_log();
  real_execution_time = app.get_real_execution_time();
  weight = app.get_weight();
  return *this;
}

void Application::set_alpha_beta(unsigned int n1, unsigned int n2){
  if (n1 == n2){
    std::cerr << "n1 = n2" << '\n';
    return;
  }
  if(n1 > n2){
    Job::time_instant r1 = execution_time_avg(n2);
    Job::time_instant r2 = execution_time_avg(n1);
    alpha = double(r1-r2) * n1 * n2/(n1-n2);
    beta = double(r1) - alpha/n2;
  }else{
    Job::time_instant r1 = execution_time_avg(n1);
    Job::time_instant r2 = execution_time_avg(n2);
    alpha = double(r1-r2) * n1 * n2/(n2-n1);
    beta = double(r1) - alpha/n1;
  }
  //std::cout << "!real_execution_time: " << real_execution_time << '\n';
  //std::cout << "ex_avg: " << execution_time_avg() << '\n';
  //std::cout << "diff: "<< real_execution_time - execution_time_avg() << '\n';
  //beta += double(real_execution_time - execution_time_avg());
}

void Application::set_n1(const Job::time_instant D){
  n1 = alpha/(d_line+D-beta);
}

void Application::set_n2(const Job::time_instant D){
  n2 = alpha/(d_line-D-beta);
}

void Application::controlRD(){
  if (d_line > execution_time_avg()){
    while (d_line > execution_time_avg()){
      set_n_core(n_core-1);
    }
    set_n_core(n_core+1);
  }
}

unsigned int Application::max_tasks() const
{
  unsigned int max = 0;
  for (auto s:stages){
      if (max < s.get_n_tasks())
        max = s.get_n_tasks();
  }

  return max;
}
