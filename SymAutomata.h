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
const int defaultNodeNum = 2000;
const int defaultCacheSize = 2000;
const int varRatio = 4;

//Variable profile:
//  0 - vn : defined variables
//  vn - 2vn : transition variable
//  2vn - 3vn : defined variable component
//  3vn - 4vn : transition variable component

class SymAutomata {
    static int totalVariables;
    const int startIndex, varNum;
    int currIndex;
    map<string, int> index;
    bdd initialStates, finalStates;
    bddPair *definedToTransition, *transitionToDefined;
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

//// FIXME: Optimisations
////    Remove Varnum from arguments and dynamically update it
////    lettersSeen computation can be optimised by having the index based
////    for loop outside the range based for loop

#endif //LIVENESSVERIFICATION_SYMAUTOMATA_H
