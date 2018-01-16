#ifndef JOB_H_
#define JOB_H_

#include <iostream>
#include <vector>
#include "Stage.hpp"


class Job{
public:
  typedef long int time_instant;
  typedef unsigned int id_type;

  Job (id_type j_id, std::string id_a, time_instant sub_time, time_instant compl_time)
    : id (j_id), id_app(id_a), submission_time (sub_time), completion_time (compl_time){};

  virtual ~Job() {};

  time_instant get_submission_time() const;
  time_instant get_completion_time() const;
  id_type get_ID() const;
  const std::vector<id_type>& get_id_stages() const {return id_stages;}
  const std::string& get_id_app() const {return id_app;}

  void set_submission_time (time_instant submission_time);
  void set_completion_time (time_instant completion_time);
  void set_id(id_type id_temp);
  void set_id_stages(const std::vector<id_type>& v);
  void printj() const;

  Job& operator=(const Job&);
private:
  id_type id;
  std::string id_app;
  time_instant submission_time;
  time_instant completion_time;
  std::vector<id_type> id_stages;
};

#endif /* JOB_H_ */
