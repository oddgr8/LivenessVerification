//
// Created by onkar on 17/5/19.
//
#include "Automata.h"
#include "SymAutomata.cpp"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

int main(){

    SymAutomata a(4, FormulaTree("(x1&x2|x3)|-x4"), FormulaTree("x4"));
    a.addReadTransition('a', FormulaTree("x1_1&x1_2"));
    a.addWriteTransition('a', FormulaTree("x1_1&x2_2"));
    bdd_printall();
    bdd_printtable(a.reachableStates());
    cout << (a.isLive() ? "Yes" : "No") << endl;

//    bdd_init(100,100);
//    bdd_setvarnum(5);
//    bdd x = bdd_nithvar(0);
//    bdd y = bdd_ithvar(1);
//    bdd z = bdd_ithvar(2);
//    bdd f = x & y;
//    bdd_printall();
//    bdd_printtable(f);
//    bddPair *p = bdd_newpair();
//    bdd_setpair(p, 0, 2);
//    bdd_setpair(p, 1, 0);
//    bdd g = bdd_veccompose(f, p);
//    bdd_printall();
//    bdd_printtable(g);



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
////    A.print();
////    cout<<"Reachable States are :";
////    for ( auto & State : A.getReachableStates()){
////        cout<<State<<" ";
////    }
////    cout<<endl;
//    A.printSize();
//
//    time_t time1,time2;
//    time(&time1);
//    cout<<"Is A Live?";
//    if(A.isLive()){
//        cout<<"Yes"<<endl;
//    }
//    else{
//        cout<<"No"<<endl;
//    }
//    time(&time2);
//    cout<<"Time required to verify Liveness: "<<difftime(time2, time1)<<" seconds"<<endl<<endl;




    return 0;
}
