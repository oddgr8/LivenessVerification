//
// Created by onkar on 6/6/19.
//

#ifndef LIVENESSVERIFICATION_SYMAUTOMATA_H
#define LIVENESSVERIFICATION_SYMAUTOMATA_H
#include <bdd.h>
#include "FormulaTree.cpp"
#include <map>
using namespace std;

const auto reorderMethod = BDD_REORDER_WIN2ITE;
const int defaultNodeNum = 1000;
const int defaultCacheSize = 1000;

class SymAutomata {
    static int totalVariables;
    const int startIndex, varNum;
    int currIndex;
    map<string, int> index;
    bdd initialStates, finalStates;
    map<char,bdd> readTransitions, writeTransitions;
    bdd FTNtoBDD(FormulaTreeNode* root);
    bdd FTNtoTBDD(FormulaTreeNode* root);//separates var_1 and var_2
public:
    SymAutomata(int varNum, const FormulaTree& I, const FormulaTree& F);
    void addReadTransition(char letter, const FormulaTree& formula);
    void addWriteTransition(char letter, const FormulaTree& formula);
    bdd reachableStates();
    bool isLive();
};


#endif //LIVENESSVERIFICATION_SYMAUTOMATA_H
