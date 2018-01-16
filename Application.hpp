#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "Job.hh"
#include "Stage.hpp"
#include <vector>
#include <string>
#include <iostream>

class Application{
    std::string id_application;
    std::vector<Job> jobs;
    std::vector<Stage> stages;
    double weight;  // every application has a cost per core

    Job::time_instant submission_time;
    Job::time_instant deadline;
    Job::time_instant real_execution_time;
    Job::time_instant d_line; // time that the single application needs

    double alpha;
    double beta;
    unsigned int n_core_log;
    unsigned int n_core;
    unsigned int n1;  // number of cores when d becomes d+delta
    unsigned int n2;  // number of cores when d becomes d-delta

  public:
    Application() = default;

    std::vector<Stage>& modify_stages() {return stages;}
    const std::vector<Stage>& get_stages() const {return stages;}
    const std::vector<Job>& get_jobs() const {return jobs;}
    unsigned int get_n_core_log() const {return n_core_log;}
    unsigned int get_n_core() const {return n_core;}
    unsigned int get_n1() const {return n1;}
    unsigned int get_n2() const {return n2;}

    void add_job(Job);
    void add_stage(Stage);

    unsigned int get_num_stages() const {return stages.size();}
    Job::time_instant get_submission_time() const {return submission_time;}
    Job::time_instant get_deadline() const {return deadline;}
    std::string get_id_app()const {return id_application;}

    Job::time_instant execution_time_avg() const;
    Job::time_instant execution_time_avg(unsigned int) const;
    double get_alpha() const { return alpha;}
    double get_beta() const {return beta;}

    Job::time_instant get_real_execution_time() const {return real_execution_time;}
    Job::time_instant get_d_line() const {return d_line;}
    double get_weight() const {return weight;}

    void set_id(const std::string& );
    void set_n_core_log(const unsigned int c){ n_core_log = c;}
    void set_n_core(const unsigned int c){ n_core = c; }
    void set_n1(const Job::time_instant D);
    void set_n2(const Job::time_instant D);
    void set_submission_time(Job::time_instant sub) {submission_time = sub;}
    void set_deadline(Job::time_instant dead) {deadline = dead;}
    void set_real_execution_time(Job::time_instant ret) {real_execution_time = ret;}
    void set_alpha_beta(unsigned int, unsigned int);  // it gets n1 and n2 numbers of cores
    void set_d_line(Job::time_instant d){ d_line = d; };
    void set_weight(double w) { weight=w; }

    void controlRD();
    unsigned int max_tasks() const;

    void print() const;
    void print_job() const;
    void print_stage() const;
    void print_ret() const{ std::cout << "ret: "<< real_execution_time << '\n';}

    Application& operator=(const Application&);
};

#endif
