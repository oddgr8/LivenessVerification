//
// Created by onkar on 17/5/19.
//
#include "Automata.cpp"
#include <iostream>
using namespace std;

int main(){
    Automata A;
    int I,F;
    cin>>I>>F;//Initial and Final States
    for (int count = 0; count < I; ++count) {
        int id;
        cin>>id;
        A.addInitialState(id);
    }
    for (int count = 0; count < F; ++count) {
        int id;
        cin>>id;
        A.addFinalState(id);
    }
    int rt,wt;//Read and write transitions
    cin>>rt>>wt;
    for (int count = 0; count < rt; ++count) {
        int src, dst;
        cin>>src>>dst;
        char letter;
        cin>>letter;
        A.addReadTransition(src, dst, letter);
    }
    for (int count = 0; count < wt; ++count) {
        int src, dst;
        cin>>src>>dst;
        char letter;
        cin>>letter;
        A.addWriteTransition(src, dst, letter);
    }
    A.print();

    int ds;//Delete States
    cin>>ds;
    for (int i = 0; i < ds; ++i) {
        int s;
        cin>>s;
        A.deleteState(s);
    }
    A.print();

    int drt,dwt;//Delete Transitions
    cin>>drt>>dwt;
    for (int j = 0; j < drt; ++j) {
        int src, dst;
        cin>>src>>dst;
        char letter;
        cin>>letter;
        A.deleteReadTransition(src, dst, letter);
    }
    for (int j = 0; j < dwt; ++j) {
        int src, dst;
        cin>>src>>dst;
        char letter;
        cin>>letter;
        A.deleteWriteTransition(src, dst, letter);
    }
    A.print();
}
