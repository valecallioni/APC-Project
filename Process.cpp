#include "Process.hpp"

void Process::push_back(Application &app)
{
  app.set_alpha_beta(15,10);
  std::shared_ptr<Application> temp(new Application(app));
  applications.push_back(temp);
}

std::shared_ptr<Application> Process::operator[](unsigned int i)
{
  for (unsigned int k=0; k<applications.size(); k++){
    if (k==i)
      return applications[i];
  }
}

bool Process::distribute_d_line()
{
  bool control = true;

  if (d_line_tot <= min_d_line())
    control = false;

  else {
    Job::time_instant sum = 0;
    std::vector<Job::time_instant> temps;

    int i = 1;
    for (auto a: applications){
      Job::time_instant temp = 0;
      for (auto s:a->get_stages()){
        temp += s.get_avg() * s.get_n_tasks();
      }
      sum += temp;
      temps.push_back(temp);
      // std::cout << "Application " << i << " takes " << temp << " milliseconds" << std::endl;
      i++;

    }

    for (unsigned i=0; i<applications.size(); i++){
      applications[i]->set_d_line(d_line_tot*(float(temps[i])/float(sum)));
      // std::cout << "Application " << i << " : " << applications[i]->get_d_line() << std::endl;
    }
  }
  return control;
}

std::pair<unsigned int, unsigned int> Process::delta(Job::time_instant D)
{
    std::vector<double> f1, f2;

    for (unsigned int i=0; i<applications.size(); i++){
      applications[i]->set_n1(D);
      applications[i]->set_n2(D);
      // std::cout << "Application " << i+1 << " n1: " << applications[i]->get_n1() << " n2: " << applications[i]->get_n2() << std::endl;
      f1.push_back(applications[i]->get_weight()*double(applications[i]->get_n_core()-applications[i]->get_n1()));
      f2.push_back(applications[i]->get_weight()*double(-applications[i]->get_n_core()+applications[i]->get_n2()));
    }

    // std::cout << "Saves with more time :\n";
    // for (auto x:f1)
    //   std::cout << x << std::endl;
    //
    // std::cout << "Costs with less time :\n";
    // for (auto x:f2)
    //   std::cout << x << std::endl;

    unsigned int max = help::max(f1);
    unsigned int min = help::min(f2);

    if (max == min){
      std::vector<double> f1_copy(f1);
      unsigned int k = 0;
      for (auto it=f1_copy.begin(); it!=f1_copy.end(); it++){
        if (k==max){
          it=f1_copy.erase(it);
          return std::make_pair(help::max(f1_copy),min);
        }
        k++;
      }
    }

    // std::cout << "Max: " << max << " Min: " << min << std::endl;

    return std::make_pair(max,min);
}

std::pair<double, double> Process::evaluate_costs(unsigned int max, unsigned int min) const
{
  double old_cost=0, new_cost=0;
  for (unsigned int i=0; i<applications.size(); i++){
    old_cost += applications[i]->get_weight()*double(applications[i]->get_n_core());
    if (i == max)
      new_cost += applications[i]->get_weight()*double(applications[i]->get_n1());
    else {
      if (i == min)
        new_cost += applications[i]->get_weight()*double(applications[i]->get_n2());
      else
        new_cost += applications[i]->get_weight()*double(applications[i]->get_n_core());
    }
  }
  return std::make_pair(old_cost, new_cost);
}

void Process::reset_core_dline(unsigned int max, unsigned int min, Job::time_instant D)
{
  if (applications[max]->get_n1()>0 && applications[min]->get_n2()){
    applications[max]->set_n_core(applications[max]->get_n1());
    applications[max]->set_d_line(applications[max]->get_d_line()+D);
    applications[min]->set_n_core(applications[min]->get_n2());
    applications[min]->set_d_line(applications[min]->get_d_line()-D);
  }
}

double Process::total_cost() const
{
  double sum=0;
  for (unsigned int i=1; i<applications.size()+1; i++)
    sum += applications[i-1]->get_weight()*double(applications[i-1]->get_n_core());
  
  return sum;
}

Job::time_instant Process::total_real_time() const
{
  Job::time_instant sum = 0;
  for (auto a:applications)
    sum += a->execution_time_avg();
  return sum;
}

Job::time_instant Process::min_d_line()
{
  for (auto a:applications)
    a->set_n_core(a->max_tasks());

  return total_real_time();
}
