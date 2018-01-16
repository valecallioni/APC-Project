#include "create_application.hpp"

Application c_app::create_app(const std::vector<std::string>& file_names){

  typedef std::vector<std::vector<std::string> > read_type;

  read_type temp;
  const std::string& file_name = file_names[0];
  help::create_vector(file_name, temp);

  Application App;
  App.set_id(temp[1][0]);
  //App.set_submission_time(std::stoul(temp[1][1]));
  App.set_submission_time(0);

  App.set_deadline(std::stoul(file_names[5]));
  //std::cout << "ex time: " << std::stoul(temp[2][1])-std::stoul(temp[1][1]) << '\n';
  App.set_n_core_log(std::stoi(file_names[4]));

  App.set_weight(std::stod(file_names[6]));

  //App.print();
  Job::time_instant ret = std::stoul(temp[2][1])-std::stoul(temp[1][1]);
  // std::cout << "ret: "<< ret << '\n';
  App.set_real_execution_time(ret);

  //App.print_ret();
  //std::cout << "real_execution_time: " << std::stoul(temp[2][1])-std::stoul(temp[1][1])<< '\n';
  //JOB
  std::map<Job::id_type, unsigned long int> sub_time, compl_time;
  std::map<Job::id_type, std::vector<Job::id_type> > id_stages;

  read_type temp1;
  help::create_vector(file_names[1], temp1);

  Job::id_type id;
  unsigned long int sub, comp;

  for (unsigned i = 1; i < temp1.size(); i++) {
    unsigned sz=temp1[i].size();
    id = std::atoi(temp1[i][0].c_str());

    if(temp1[i][1] != "NOVAL"){
      sub = std::stoul(temp1[i][1]);
      sub_time.insert({id, sub});
    }

    if (temp1[i][sz-1] != "NOVAL") {
      comp = std::stoul(temp1[i][sz-1]);
      compl_time.insert({id, comp});
    }

    std::vector<Job::id_type> vec;
    for(unsigned j = 2; j < sz-1; j++){
      vec.push_back(help::read_id(temp1[i][j]));
    }
    id_stages.insert({id, vec});
  }

  /*for(auto i : id_stages){
    std::cout << "id jobs: " << i.first << "stage dependencies: " << '\n';
    for(auto j = 0; j < i.second.size(); j++){
      std::cout << i.second[j] << '\n';
    }
    std::cout << '\n';
  }*/

  for(auto it : sub_time){
    Job job_temp(it.first, temp[1][0],  it.second, compl_time.find(it.first)->second);
    job_temp.set_id_stages(id_stages.find(it.first)->second);
    App.add_job(job_temp);
    //job_temp.printj();
  }

  //App.print_job();

  //STAGE
  read_type temp2;
  help::create_vector(file_names[2], temp2);

  unsigned int task;
  for (unsigned i = 1; i < temp2.size(); i++) {
    unsigned sz = temp2[i].size();
    id = std::atoi(temp2[i][0].c_str());
    task = std::atoi(temp2[i][3].c_str());
    Stage stage_temp(id, task);
    std::vector<Job::id_type> vec;

    if(!help::check_empty(temp2[i][2])){
      for(unsigned j = 2; j < sz-3; j++){
        vec.push_back(help::read_id(temp2[i][j]));
      }
    }
    stage_temp.set_dependencies(vec);
    App.add_stage(stage_temp);
  }

  //task
  Job::time_instant diff;
  unsigned long int launch, finish;
  Job::id_type id_stage;
  read_type temp3;
  std::vector<std::vector<Job::time_instant>> tasks(App.get_num_stages());
  help::create_vector(file_names[3], temp3);
  for (unsigned i = 1; i < temp3.size(); i++) {
    launch = std::stoul(temp3[i][4]);
    finish = std::stoul(temp3[i][5]);
    id_stage = std::atoi(temp3[i][13].c_str());
    diff =  finish - launch;
    tasks[id_stage].push_back(diff);
  }

  for (auto i = App.modify_stages().begin(); i != App.modify_stages().end(); i++) {
    unsigned n = i->get_ID();
    i->set_max(tasks[n]);
    i->set_min(tasks[n]);
    i->set_avg(tasks[n]);
  }

  //Job::time_instant ex = App.execution_time_avg();
  //std::cout << "ex " << ex << '\n';
  return App;
}
