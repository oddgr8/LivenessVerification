//
// Created by onkar on 7/6/19.
//

#ifndef LIVENESSVERIFICATION_FORMULATREE_H
#define LIVENESSVERIFICATION_FORMULATREE_H
#include <string>
#include <iostream>
using namespace std;

const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';
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
    virtual string print() = 0;
    virtual ~FormulaTreeNode() = 0;
};
class TrueNode : public FormulaTreeNode{
public:
    TrueNode();
    string print() override;
};
class FalseNode : public FormulaTreeNode{
public:
    FalseNode();
    string print() override;
};

class VariableNode : public FormulaTreeNode{
    const string variableName;
public:
    explicit VariableNode(string name);
    string getName();
    string print() override;
};

class NotNode : public FormulaTreeNode{
    FormulaTreeNode* child;
public:
    explicit NotNode(FormulaTreeNode* c);
    ~NotNode() override;
    FormulaTreeNode* getChild();
    string print() override;
};

class AndNode : public FormulaTreeNode{
    FormulaTreeNode* leftChild, *rightChild;
public:
    AndNode(FormulaTreeNode* l, FormulaTreeNode* r);
    ~AndNode() override;
    FormulaTreeNode* getLeftChild();
    FormulaTreeNode* getRightChild();
    string print() override;
};

class OrNode : public FormulaTreeNode{
    FormulaTreeNode* leftChild, *rightChild;
public:
    OrNode(FormulaTreeNode* l, FormulaTreeNode* r);
    ~OrNode() override;
    FormulaTreeNode* getLeftChild();
    FormulaTreeNode* getRightChild();
    string print() override;
};

class ExistsNode : public FormulaTreeNode{
    const string variableName;
    FormulaTreeNode* child;
public:
    ExistsNode(string v, FormulaTreeNode* c);
    ~ExistsNode() override;
    string getName();
    FormulaTreeNode* getChild();
    string print() override;
};

class ForAllNode : public FormulaTreeNode{
    const string variableName;
    FormulaTreeNode* child;
public:
    ForAllNode(string v, FormulaTreeNode* child);
    ~ForAllNode() override;
    string getName();
    FormulaTreeNode* getChild();
    string print() override;
};

FormulaTreeNode* stringToTree(string expression);

class FormulaTree {
public:
    FormulaTreeNode* root;
    FormulaTree(string formula);
    ~FormulaTree();
    void print();
};




#endif //LIVENESSVERIFICATION_FORMULATREE_H
