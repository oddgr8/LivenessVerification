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
    bdd_extvarnum(varRatio*varNum);
    totalVariables += varRatio*varNum;
    currIndex = startIndex;
    initialStates = FTNtoBDD(I.root);
    finalStates = FTNtoBDD(F.root);
    definedToTransition = bdd_newpair();
    transitionToDefined = bdd_newpair();
    for (int i = 0; i < varNum; ++i) {
        bdd_setpair(definedToTransition,i,i+varNum);
        bdd_setpair(definedToTransition,i+2*varNum,i+3*varNum);
        bdd_setpair(transitionToDefined,i+varNum,i);
        bdd_setpair(transitionToDefined,i+3*varNum,i+2*varNum);
    }
}

void SymAutomata::addReadTransition(char letter, const FormulaTree& formula) {
    readTransitions[letter] = FTNtoTBDD(formula.root);
}

void SymAutomata::addWriteTransition(char letter, const FormulaTree& formula) {
    writeTransitions[letter] = FTNtoTBDD(formula.root);
}

bdd SymAutomata::reachableStates() {
    bdd r = initialStates;

    while (true) {
        bdd r_2 = bdd_veccompose(r, definedToTransition);
        set<char> lettersSeen;
        for (auto& transition : writeTransitions){
            bdd formula = r & r_2 & transition.second;
            if (formula != bddfalse) {
                lettersSeen.insert(transition.first);
            }
        }

        bdd formula = bdd_false();
        for (auto& transition : writeTransitions){
            formula = formula | transition.second;
        }
        for (auto letter : lettersSeen){
            formula = formula | readTransitions[letter];
        }
        int v[varNum];
        for (int i = 0; i < varNum; ++i) {
            v[i] = startIndex+i;
        }
        bdd rnew = bdd_veccompose(bdd_appex(r, formula, bddop_and, bdd_makeset(v, varNum)), transitionToDefined);
        rnew = r | rnew;
        if ((rnew & bdd_not(r)) == bddfalse) {
            break;
        }
        r = rnew;
    }
    return r;
}

bool SymAutomata::isLive() {
    bdd r = reachableStates();
    if(bdd_and(r, finalStates) == bdd_false()){
        return false;
    }
    for (int i = 0; i < varNum; ++i) {
        r = r & bdd_not(bdd_xor(bdd_ithvar(i + startIndex), bdd_ithvar(i + startIndex + 2*varNum)));
    }

    bdd C = bdd_true();
    while(true){
        bdd C_2 = bdd_veccompose(C, definedToTransition);
        bdd X = r;
        bdd XX_2 = bdd_veccompose(X, definedToTransition);
        set<char> lettersSeen;
        for (auto& transition : writeTransitions){
            bdd formula = X & XX_2 & transition.second;
            for (int i = 0; i < varNum; ++i) {
                formula = formula & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
            }
            if (formula != bddfalse) {
                lettersSeen.insert(transition.first);
            }
        }
        bdd formulaa = bdd_false();
        for (auto& transition : writeTransitions){
            formulaa = formulaa | transition.second;
        }
        for (auto letter : lettersSeen){
            formulaa = formulaa | readTransitions[letter];
        }
        int vv[2*varNum];
        for (int i = 0; i < varNum; ++i) {
            vv[i] = startIndex+i;
            vv[i+varNum] = startIndex + i + 2*varNum;
            formulaa = formulaa & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
        }
        X = bdd_veccompose(bdd_appex(X & C, formulaa, bddop_and, bdd_makeset(vv, 2*varNum)),transitionToDefined);
        while(true){//Find Spost*(Spost(R))
            bdd X_2 = bdd_veccompose(X, definedToTransition);
            for (auto& transition : writeTransitions){
                bdd formula = X & X_2 & transition.second;
                for (int i = 0; i < varNum; ++i) {
                    formula = formula & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
                }
                if (formula != bddfalse) {
                    lettersSeen.insert(transition.first);
                }
            }
            bdd formula = bdd_false();
            for (auto& transition : writeTransitions){
                formula = formula | transition.second;
            }
            for (auto letter : lettersSeen){
                formula = formula | readTransitions[letter];
            }
            int v[2*varNum];
            for (int i = 0; i < varNum; ++i) {
                v[i] = startIndex+i;
                v[i+varNum] = startIndex + i + 2*varNum;
                formula = formula & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
            }
            bdd Xnew = X | bdd_veccompose(bdd_appex(X & C, formula, bddop_and, bdd_makeset(v, 2*varNum)),transitionToDefined);
            if ((Xnew & bdd_not(X)) == bddfalse){
                break;
            }
            X = Xnew;
        }
        bdd S = r;
        while(true){//Find pre*(R)
            bdd S_2 = bdd_veccompose(S, definedToTransition);
            for (auto& transition : writeTransitions){
                bdd formula = S & S_2 & transition.second;
                for (int i = 0; i < varNum; ++i) {
                    formula = formula & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
                }
                if (formula != bddfalse) {
                    lettersSeen.insert(transition.first);
                }
            }
            bdd formula = bdd_false();
            for (auto& transition : writeTransitions){
                formula = formula | transition.second;
            }
            for (auto letter : lettersSeen){
                formula = formula | readTransitions[letter];
            }
            int v[2*varNum];
            for (int i = 0; i < varNum; ++i) {
                v[i] = startIndex+i + varNum;
                v[i+varNum] = startIndex + i + 3*varNum;
                formula = formula & bdd_not(bdd_xor(bdd_ithvar(i + startIndex + 2*varNum), bdd_ithvar(i + startIndex + 3*varNum)));
            }
            bdd Snew = S | bdd_appex(S & C_2, formula, bddop_and, bdd_makeset(v, 2*varNum));
            if ((Snew & bdd_not(S)) == bddfalse){
                break;
            }
            S = Snew;
        }
        bdd Cnew = S & X;
        if ((Cnew & bdd_not(C)) == bddfalse) {
            break;
        }
        C = Cnew;
    }
    return C == bddfalse == 0;//return true if C != bddfalse
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
        return FTNtoBDD(r->getLeftChild()) & FTNtoBDD(r->getRightChild());
    }
    if (root->getType() == OR) {
        auto* r = dynamic_cast<OrNode*>(root);
        return FTNtoBDD(r->getLeftChild()) | FTNtoBDD(r->getRightChild());
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
        string fullName = dynamic_cast<VariableNode*>(root)->getName();
        if (fullName[fullName.size() - 2] != '_') {
            throw std::runtime_error("Invalid Variable in Transition");
        }
        string name = fullName.substr(0, fullName.size() - 2);
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        if (fullName.back() == '1') {
            return bdd_ithvar(index[name]);
        } else {
            return bdd_ithvar(index[name]+varNum);
        }
    }
    if (root->getType() == AND) {
        auto* r = dynamic_cast<AndNode*>(root);
        return FTNtoTBDD(r->getLeftChild()) & FTNtoTBDD(r->getRightChild());
    }
    if (root->getType() == OR) {
        auto* r = dynamic_cast<OrNode*>(root);
        return FTNtoTBDD(r->getLeftChild()) | FTNtoTBDD(r->getRightChild());
    }
    if (root->getType() == NOT) {
        auto* r = dynamic_cast<NotNode*>(root);
        return bdd_not(FTNtoTBDD(r->getChild()));
    }
    if (root->getType() == EXISTS) {
        auto* r = dynamic_cast<ExistsNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_exist(FTNtoTBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    if (root->getType() == FORALL) {
        auto* r = dynamic_cast<ForAllNode*>(root);
        string name = r->getName();
        if (index.find(name) == index.end()) {
            index[name] = currIndex++;
        }
        return bdd_forall(FTNtoTBDD(r->getChild()), bdd_ithvar(index[name]));
    }
    throw std::runtime_error("Invalid Node Type");
}
