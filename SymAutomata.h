//
// Created by onkar on 6/6/19.
//

#ifndef LIVENESSVERIFICATION_SYMAUTOMATA_H
#define LIVENESSVERIFICATION_SYMAUTOMATA_H
#include <bdd.h>
#include "FormulaTree.cpp"
#include <map>
using namespace std;

const int reorderMethod = BDD_REORDER_WIN2ITE;

class SymAutomata {
    static int totalVariables;
    bdd initialStates, finalStates;
    map<char,bdd> readTransitions, writeTransitions;
    ////TODO Static map between variables and integers
public:
    SymAutomata(int varNum, FormulaTree I, FormulaTree F);
    void addReadTransition(char letter, bdd formula);
    void addWriteTransition(char letter, bdd formula);
    bdd reachableStates();
    bool isLive();
};


#endif //LIVENESSVERIFICATION_SYMAUTOMATA_H
