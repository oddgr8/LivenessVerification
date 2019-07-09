//
// Created by onkar on 17/5/19.
//
#include <map>
#include <set>
#include <string>
#include "State.h"
using namespace std;

#ifndef LIVENESSVERIFICATION_AUTOMATA_H
#define LIVENESSVERIFICATION_AUTOMATA_H


class Automata {
    map<string, State> States;//int is the id itself
    set<string> initialStates, finalStates;
public:
    void addInitialState(const string& id);
    void addFinalState(const string& id);
    void addWriteTransition(const string& src, const string& dst, char letter);
    void addReadTransition(const string& src, const string& dst, char letter);
    bool isLive();


    set<string> getReachableStates();
    void makeAllStatesFinal();
    bool deleteState(const string& id);//Remove State and all its transitions
    bool deleteReadTransition(const string& src, const string& dst, char letter);
    bool deleteWriteTransition(const string& src, const string& dst, char letter);
    set<string> getInitialStates();
    set<string> getFinalStates();
    State getState(const string& id);
    void print();//Prints all states and transitions
    void printSize();//Prints number of total, initial and final states and read and write transitions
};


Automata readFromStream(istream &stream);//reads in BA Format


//// FIXME: Optimisations
////    use initialization lists instead of assignments

#endif //LIVENESSVERIFICATION_AUTOMATA_H
