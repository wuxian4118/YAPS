//
// flow_generator.h
// support arbitrary flow generation models.
//
// 6/15/2015 Akshay Narayan
//

#ifndef CORESIM_FLOW_GENERATOR_H
#define CORESIM_FLOW_GENERATOR_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <set>
#include <math.h>
#include <assert.h>

#include "params.h"

class EmpiricalRandomVariable;
class Event;
class Flow;
class Topology;

extern DCExpParams params;
extern void add_to_event_queue(Event *);

//extern double start_time;
//extern double get_current_time();

// subclass FlowGenerator to implement your favorite flow generation scheme


class FlowGenerator {
public:
    uint32_t num_flows;
    Topology *topo;
    std::string filename;

    FlowGenerator(uint32_t num_flows, Topology *topo, std::string filename);
    virtual ~FlowGenerator() = 0;
    virtual void write_flows_to_file(std::deque<Flow*> flows, std::string file);
    virtual void make_flows();
};

class PoissonFlowGenerator : public FlowGenerator {
public:
    PoissonFlowGenerator(uint32_t num_flows, Topology *topo, std::string filename);
    virtual void make_flows();
};

class FlowBytesGenerator : public FlowGenerator {
public:
    FlowBytesGenerator(uint32_t num_flows, Topology *topo, std::string filename);
    virtual void make_flows();
};

class FlowReader : public FlowGenerator {
public:
    std::set<std::pair<uint32_t, uint32_t>> *src_dst_set;
    FlowReader(uint32_t num_flows, Topology *topo, std::string filename);
    virtual void make_flows();
};

class CustomCDFFlowGenerator : public FlowGenerator {
public:
    CustomCDFFlowGenerator(uint32_t num_flows, Topology *topo, std::string filename, std::string interarrivals_cdf_filename);
    virtual void make_flows();

    std::string interarrivals_cdf_filename;
private:
    std::vector<EmpiricalRandomVariable*>* makeCDFArray(std::string fn_template, std::string filename);
};

class PermutationTM : public FlowGenerator {
public:
    PermutationTM(uint32_t num_flows, Topology *topo, std::string filename);
    virtual void make_flows();

};

#endif  // CORESIM_FLOW_GENERATOR_H
