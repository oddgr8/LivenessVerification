//
// Created by onkar on 17/5/19.
//
#include <map>
#include <set>
#include "State.cpp"
using namespace std;

#ifndef LIVENESSVERIFICATION_AUTOMATA_H
#define LIVENESSVERIFICATION_AUTOMATA_H


class Automata {
    map<int, State> States;//int is the id itself
    set<int> initialStates, finalStates;
public:
    void addInitialState(int id);//Add empty state if already does not exist
    void addFinalState(int id);//Add empty set if already does not exist
    void addWriteTransition(int src, int dst, char letter);
    void addReadTransition(int src, int dst, char letter);
    bool deleteState(int id);//Remove State and all its transitions
    bool deleteReadTransition(int src, int dst, char letter);
    bool deleteWriteTransition(int src, int dst, char letter);
    set<int> getInitialStates();
    set<int> getFinalStates();
    State getState(int id);
//TODO    set State> getReachableStates();
    void print();
};


#endif //LIVENESSVERIFICATION_AUTOMATA_H
