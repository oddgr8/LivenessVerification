//
// Created by onkar on 7/6/19.
//

#ifndef LIVENESSVERIFICATION_FORMULATREE_H
#define LIVENESSVERIFICATION_FORMULATREE_H
#include <string>
using namespace std;

const char TRUE = 'T';
const char FALSE = 'F';
const char AND = '&';
const char OR = '|';
const char NOT = '-';
const char EXISTS = '/';
const char FORALL = '?';
const char VAR = 'x';

class FormulaTreeNode{
protected:
    char type;
public:
    char getType();
};
class TrueNode : public FormulaTreeNode{
public:
    TrueNode();
};
class FalseNode : public FormulaTreeNode{
public:
    FalseNode();
};

class VariableNode : public FormulaTreeNode{
    string variableName;
public:
    explicit VariableNode(string name);
    string getName();
};

class NotNode : public FormulaTreeNode{
    FormulaTreeNode* child;
public:
    explicit NotNode(FormulaTreeNode* c);
    ~NotNode();
    FormulaTreeNode* getChild();
};

class AndNode : public FormulaTreeNode{
    FormulaTreeNode* leftChild, *rightChild;
public:
    AndNode(FormulaTreeNode* l, FormulaTreeNode* r);
    ~AndNode();
    FormulaTreeNode* getLeftChild();
    FormulaTreeNode* getRightChild();
};

class OrNode : public FormulaTreeNode{
    FormulaTreeNode* leftChild, *rightChild;
public:
    OrNode(FormulaTreeNode* l, FormulaTreeNode* r);
    ~OrNode();
    FormulaTreeNode* getLeftChild();
    FormulaTreeNode* getRightChild();
};

class ExistsNode : public FormulaTreeNode{
    string variableName;
    FormulaTreeNode* child;
public:
    ExistsNode(string v, FormulaTreeNode* c);
    ~ExistsNode();
    string getName();
    FormulaTreeNode* getChild();
};

class ForAllNode : public FormulaTreeNode{
    string variableName;
    FormulaTreeNode* child;
public:
    ForAllNode(string v, FormulaTreeNode* child);
    ~ForAllNode();
    string getName();
    FormulaTreeNode* getChild();
};

FormulaTreeNode* stringToTree(string expression);

class FormulaTree {
    FormulaTreeNode* root;
public:
    FormulaTree(string formula);
    ~FormulaTree();
    ////TODO empty constructor that take
};




#endif //LIVENESSVERIFICATION_FORMULATREE_H
