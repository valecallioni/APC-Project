#ifndef __STAGE_HPP__
#define __STAGE_HPP__

#include <vector>
#include <iostream>

class Stage {

public:
  typedef long int time_instant;
  typedef unsigned int id_type;

  void set_max (const std::vector<time_instant>& v);
  void set_min (const std::vector<time_instant>& v);
  void set_avg (const std::vector<time_instant>& v);
  void setavg(const unsigned long int a) {avg = a;};
  void set_dependencies(const std::vector<id_type> v);

  const id_type get_ID() const {return id_Stage;}
  time_instant get_min() const {return min;}
  time_instant get_max() const {return max;}
  time_instant get_avg() const {return avg;}
  unsigned int get_n_tasks() const {return n_tasks;}
  const std::vector<id_type>& get_depend() const {return dependencies;}

  Stage (id_type id, unsigned int ntasks): id_Stage(id), n_tasks(ntasks){}

  void prints() const;

  Stage& operator=(const Stage& stage);

private:
  id_type id_Stage;
  time_instant max;
  time_instant min;
  time_instant avg;
  unsigned int n_tasks;
  std::vector<id_type> dependencies;

};
#endif
