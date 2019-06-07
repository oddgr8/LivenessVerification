//
// Created by onkar on 6/6/19.
//

#include "SymAutomata.h"

int SymAutomata::totalVariables = 0;

SymAutomata::SymAutomata(int varNum, FormulaTree I, FormulaTree F) {

}

void SymAutomata::addReadTransition(char letter, bdd formula) {
    return;
}

void SymAutomata::addWriteTransition(char letter, bdd formula) {
    return;
}

bdd SymAutomata::reachableStates() {
    return bdd();
}

bool SymAutomata::isLive() {
    return false;
}
