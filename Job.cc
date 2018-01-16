#include "Job.hh"

Job::time_instant Job::get_completion_time() const{
  return completion_time;
}

Job::time_instant Job::get_submission_time() const{
  return submission_time;
}

Job::id_type Job::get_ID() const{
  return id;
}

void Job::set_completion_time (time_instant t){
  completion_time = t;
}

void Job::set_submission_time (time_instant t){
  submission_time = t;
}

void Job::set_id_stages(const std::vector<id_type>& v){
  id_stages = v;
}

void Job::printj() const{
  std::cout << "id job: " << id << '\n' << " submission_time " << submission_time << '\n'
            << " completion_time " << completion_time << '\n';
}

Job& Job::operator=(const Job& j){
  id = j.get_ID();
  id_app = j.get_id_app();
  submission_time = j.get_submission_time();
  completion_time = j.get_completion_time();
  id_stages = j.get_id_stages();
  return *this;
};
