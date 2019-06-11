#include <utility>

#include <utility>

#include <utility>

#include <utility>

//
// Created by onkar on 7/6/19.
//

#include "FormulaTree.h"

VariableNode::VariableNode(string name) : FormulaTreeNode(), variableName(std::move(name)) {
    type = VAR;
}

string VariableNode::getName() {
    return variableName;
}

string VariableNode::print() {
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

string NotNode::print() {
    return string(1, NOT) + string(1, OPEN_BRACKET) + child->print() + string(1, CLOSE_BRACKET);
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

string AndNode::print() {
    return string(1, OPEN_BRACKET) + leftChild->print() + string(1, CLOSE_BRACKET) + string(1, AND) + string(1, OPEN_BRACKET) + rightChild->print() + string(1, CLOSE_BRACKET);
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

string OrNode::print() {
    return string(1, OPEN_BRACKET) + leftChild->print() + string(1, CLOSE_BRACKET) + string(1, OR) + string(1, OPEN_BRACKET) + rightChild->print() + string(1, CLOSE_BRACKET);
}

ExistsNode::ExistsNode(string v, FormulaTreeNode *c) : FormulaTreeNode(), variableName(std::move(v)) {
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

string ExistsNode::print() {
    return string(1, EXISTS) + variableName + string(1, OPEN_BRACKET) + child->print() + string(1, CLOSE_BRACKET);
}

ForAllNode::ForAllNode(string v, FormulaTreeNode *c) : FormulaTreeNode(), variableName(std::move(v)) {
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

string ForAllNode::print() {
    return string(1, FORALL) + variableName + string(1, OPEN_BRACKET) + child->print() + string(1, CLOSE_BRACKET);
}

FormulaTree::FormulaTree(string formula) {
    root = stringToTree(std::move(formula));
}

FormulaTree::~FormulaTree() {
    if(!root){
        delete root;
    }
}

void FormulaTree::print() {
    cout<<root->print()<<endl;
}

char FormulaTreeNode::getType() {
    return type;
}

FormulaTreeNode::~FormulaTreeNode() = default;

TrueNode::TrueNode() : FormulaTreeNode() {
    type = TRUE;
}

string TrueNode::print() {
    return string(1, TRUE);
}

FalseNode::FalseNode() : FormulaTreeNode() {
    type = FALSE;
}

string FalseNode::print() {
    return string(1, FALSE);
}

FormulaTreeNode* stringToTree(string expression) {
    if (expression.front() == OPEN_BRACKET and  expression.back() == CLOSE_BRACKET) {
        bool flag = false;
        int count = 1;
        for (auto i : expression.substr(1)){
            if (count == 0) {
                flag = true;
                break;
            }
            if (i == '(') {count++;}
            else if(i == ')') {count--;}
        }
        if (!flag) {
            return stringToTree(expression.substr(1,expression.size() - 2));
        }
    }
    FormulaTreeNode* answer;
    if (expression.front() == EXISTS) {
        auto i = expression.find(OPEN_BRACKET);
        if (i == string::npos) {
            throw std::runtime_error("Empty formula given to EXISTS");
        }
        answer = new ExistsNode(expression.substr(1,i-1),stringToTree(expression.substr(i)));
        return answer;
    }
    if (expression.front() == FORALL) {
        auto i = expression.find(OPEN_BRACKET);
        if (i == string::npos) {
            throw std::runtime_error("Empty formula given to FORALL");
        }
        answer = new ForAllNode(expression.substr(1,i-1),stringToTree(expression.substr(i)));
        return answer;
    }
    if (expression.front() == OPEN_BRACKET) {
        auto i = expression.find(CLOSE_BRACKET);
        if (i == string::npos) {
            throw std::runtime_error("Invalid Brackets");
        }
        if (expression[i+1] == AND) {
            answer = new AndNode(stringToTree(expression.substr(0,i+1)), stringToTree(expression.substr(i+2)));
            return answer;
        }
        if (expression[i+1] == OR) {
            answer = new OrNode(stringToTree(expression.substr(0,i+1)), stringToTree(expression.substr(i+2)));
            return answer;
        }
        throw std::runtime_error("Invalid formula");
    }
    auto i = expression.find(OR);
    if (i != string::npos) {
        answer = new OrNode(stringToTree(expression.substr(0, i)), stringToTree(expression.substr(i+1)));
        return answer;
    }
    i = expression.find(AND);
    if (i != string::npos) {
        answer = new AndNode(stringToTree(expression.substr(0, i)), stringToTree(expression.substr(i+1)));
        return answer;
    }
    if (expression.front() == NOT) {
        answer = new NotNode(stringToTree(expression.substr(1)));
        return answer;
    }
    answer = new VariableNode(expression);
    return answer;
}
