//
// Created by onkar on 17/5/19.
//
#include "Automata.h"
#include "SymAutomata.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

int main(){

////GNU G++ Comilation command is:
//// g++ testMain.cpp Automata.cpp SymAutomata.cpp FormulaTree.cpp State.cpp


//////////////////////
//// The following code reads from stdin in BA format and generates Automata A
//////////////////////
//
//    Automata A;
//    char input[100];
//    bool atInitial = true,firstInput =true, foundFinalState = false;
//    while(cin.getline(input,100)){
//        string s(input);
//        if(s=="input_over"){
//            break;
//        }
//        if(s.find(',')==string::npos){
//            if(atInitial){
//                A.addInitialState(s);
//            }
//            else{
//                A.addFinalState(s);
//                foundFinalState = true;
//            }
//        }
//        else{
//            atInitial = false;
//            int c = s.find(','), t = s.find("->");
//            string src = s.substr(c+1,t-c-1);
//            string dst = s.substr(t+2);
//            if(s[0]=='!'){
//                A.addWriteTransition(src, dst, s[1]);
//            }
//            else if(s[0]=='?'){
//                A.addReadTransition(src, dst, s[1]);
//            }
//            if(firstInput){
//                A.addInitialState(src);
//            }
//        }
//        firstInput = false;
//    }
//    if(!foundFinalState){
//        A.makeAllStatesFinal();
//    }
//
//////////////////////
//// Code finished
//////////////////////



//////////////////////
////The following code reads from stdin in the given format and generates Symbolic Automata A
//// Format is
//// <no of variables as int>
//// <formula for initial states as string>
//// <formula for final states as string>
//// <no of read transitions as int>
//// <no of write transitions as int>
//// For each read transition:
////    <label of transition as char>
////    <formula for transitions as string>
//// For each write transition:
////    <label of transition as char>
////    <formula for transitions as string>
//////////////////////
//
//    int varNum;
//    cin>>varNum;
//    string i,f;
//    cin>>i;
//    cin>>f;
//    SymAutomata A(varNum, FormulaTree(i), FormulaTree(f));
//
//    int rt,wt;
//    cin>>rt>>wt;
//    char c;
//    string t;
//    for (int j = 0; j < rt; ++j) {
//        cin>>c;
//        cin>>t;
//        A.addReadTransition(c, FormulaTree(t));
//    }
//    for (int j = 0; j < wt; ++j) {
//        cin>>c;
//        cin>>t;
//        A.addWriteTransition(c, FormulaTree(t));
//    }
//
//////////////////////
//// Code finished
//////////////////////

    return 0;
}
