#include <utility>

#include <utility>

#include <utility>

//
// Created by onkar on 7/6/19.
//

#include "FormulaTree.h"

VariableNode::VariableNode(string name) : FormulaTreeNode() {
    variableName = std::move(name);
    type = VAR;
}

string VariableNode::getName() {
    return variableName;
}

NotNode::NotNode(FormulaTreeNode *c) : FormulaTreeNode() {
    child = c;
    type = NOT;
}

NotNode::~NotNode() {
    delete child;
}

FormulaTreeNode *NotNode::getChild() {
    return child;
}

AndNode::AndNode(FormulaTreeNode *l, FormulaTreeNode *r) : FormulaTreeNode() {
    leftChild = l;
    rightChild = r;
    type = AND;
}

AndNode::~AndNode() {
    delete leftChild;
    delete rightChild;
}

FormulaTreeNode *AndNode::getLeftChild() {
    return leftChild;
}

FormulaTreeNode *AndNode::getRightChild() {
    return rightChild;
}

OrNode::OrNode(FormulaTreeNode *l, FormulaTreeNode *r) : FormulaTreeNode() {
    leftChild = l;
    rightChild = r;
    type = OR;
}

OrNode::~OrNode() {
    delete leftChild;
    delete rightChild;
}

FormulaTreeNode *OrNode::getLeftChild() {
    return leftChild;
}

FormulaTreeNode *OrNode::getRightChild() {
    return rightChild;
}

ExistsNode::ExistsNode(string v, FormulaTreeNode *c) : FormulaTreeNode() {
    variableName = std::move(v);
    child = c;
    type = EXISTS;
}

ExistsNode::~ExistsNode() {
     delete child;
}

string ExistsNode::getName() {
    return variableName;
}

FormulaTreeNode *ExistsNode::getChild() {
    return child;
}

ForAllNode::ForAllNode(string v, FormulaTreeNode *c) : FormulaTreeNode() {
    variableName = std::move(v);
    child = c;
    type = FORALL;
}

ForAllNode::~ForAllNode() {
    delete child;
}

string ForAllNode::getName() {
    return variableName;
}

FormulaTreeNode *ForAllNode::getChild() {
    return child;
}

FormulaTree::FormulaTree(string formula) {
    root = stringToTree(std::move(formula));
}

FormulaTree::~FormulaTree() {
    if(!root){
        delete root;
    }
}

char FormulaTreeNode::getType() {
    return type;
}

TrueNode::TrueNode() : FormulaTreeNode() {
    type = TRUE;
}

FalseNode::FalseNode() : FormulaTreeNode() {
    type = FALSE;
}

FormulaTreeNode* stringToTree(string expression) {
    if (expression.front() == '(' and  expression.back() == ')') {
        return stringToTree(expression.substr(1,expression.size() - 2));
    }
    return nullptr;
}
