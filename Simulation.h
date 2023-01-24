#ifndef AIRHOCKEY_SIMULATION_H
#define AIRHOCKEY_SIMULATION_H
#include "Table.h"

class Simulation {
public:
    Table* table;
    Simulation();
    void getInputs();
    void simulate(double T, double dT);
    void print(double t);
    double dT;
};


#endif //AIRHOCKEY_SIMULATION_H
