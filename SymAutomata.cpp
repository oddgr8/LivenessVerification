//
// Created by onkar on 6/6/19.
//

#include "SymAutomata.h"

int SymAutomata::totalVariables = 0;

SymAutomata::SymAutomata(int vn, const FormulaTree& I, const FormulaTree& F): varNum(vn), startIndex(totalVariables) {
    if(!bdd_isrunning()){
        bdd_init(defaultNodeNum,defaultCacheSize);
    }
    bdd_autoreorder(reorderMethod);
    bdd_extvarnum(2*varNum);
    totalVariables += 2* varNum;
    currIndex = startIndex;
    initialStates = FTNtoBDD(I.root);
    finalStates = FTNtoBDD(F.root);
}

void SymAutomata::addReadTransition(char letter, const FormulaTree& formula) {
    readTransitions[letter] = FTNtoTBDD(formula.root);
    return;
}

void SymAutomata::addWriteTransition(char letter, const FormulaTree& formula) {
    readTransitions[letter] = FTNtoTBDD(formula.root);
    return;
}

bdd SymAutomata::reachableStates() {
    return bdd();
}

bool SymAutomata::isLive() {
    return false;
}

bdd SymAutomata::FTNtoBDD(FormulaTreeNode *root) {
    if (root->getType() == TRUE) {
        return bdd_true();
    }
    if (root->getType() == FALSE) {
        return bdd_false();
    }
    if (root->getType() == VAR) {
        string name = dynamic_cast<VariableNode*>(root)->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_ithvar(index[name]);
    }
    if (root->getType() == AND) {
        auto* r = dynamic_cast<AndNode*>(root);
        return bdd_and(FTNtoBDD(r->getLeftChild()),FTNtoBDD(r->getRightChild()));
    }
    if (root->getType() == OR) {
        auto* r = dynamic_cast<OrNode*>(root);
        return bdd_or(FTNtoBDD(r->getLeftChild()),FTNtoBDD(r->getRightChild()));
    }
    if (root->getType() == NOT) {
        auto* r = dynamic_cast<NotNode*>(root);
        return bdd_not(FTNtoBDD(r->getChild()));
    }
    if (root->getType() == EXISTS) {//// TODO: Is this really needed for states and transitions?
        auto* r = dynamic_cast<ExistsNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_exist(FTNtoBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    if (root->getType() == FORALL) {
        auto* r = dynamic_cast<ForAllNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_forall(FTNtoBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    throw std::runtime_error("Invalid Node Type");
}

bdd SymAutomata::FTNtoTBDD(FormulaTreeNode *root) {
    if (root->getType() == TRUE) {
        return bdd_true();
    }
    if (root->getType() == FALSE) {
        return bdd_false();
    }
    if (root->getType() == VAR) {
        string name = dynamic_cast<VariableNode*>(root)->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_ithvar(index[name]);
    }
    if (root->getType() == AND) {
        auto* r = dynamic_cast<AndNode*>(root);
        return bdd_and(FTNtoBDD(r->getLeftChild()),FTNtoBDD(r->getRightChild()));
    }
    if (root->getType() == OR) {
        auto* r = dynamic_cast<OrNode*>(root);
        return bdd_or(FTNtoBDD(r->getLeftChild()),FTNtoBDD(r->getRightChild()));
    }
    if (root->getType() == NOT) {
        auto* r = dynamic_cast<NotNode*>(root);
        return bdd_not(FTNtoBDD(r->getChild()));
    }
    if (root->getType() == EXISTS) {
        auto* r = dynamic_cast<ExistsNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_exist(FTNtoBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    if (root->getType() == FORALL) {
        auto* r = dynamic_cast<ForAllNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_forall(FTNtoBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    throw std::runtime_error("Invalid Node Type");
}
