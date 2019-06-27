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


    int varNum;
    cin>>varNum;
    string i,f;
    cin>>i;
    cin>>f;
    SymAutomata test(varNum, FormulaTree(i), FormulaTree(f));

    int rt,wt;
    cin>>rt>>wt;
    char c;
    string t;
    for (int j = 0; j < rt; ++j) {
        cin>>c;
        cin>>t;
        test.addReadTransition(c, FormulaTree(t));
    }
    for (int j = 0; j < wt; ++j) {
        cin>>c;
        cin>>t;
        test.addWriteTransition(c, FormulaTree(t));
    }
    cout<<"No of variabes is "<<varNum<<endl;
    cout<<"No of read transitions is "<<rt<<endl;
    cout<<"No of write transitions is "<<wt<<endl;
    
    time_t time1,time2;
    time(&time1);
    cout<< (test.isLive() ? "Yes" : "No") <<endl;
    time(&time2);
    cout<<"Time required to verify Symbolic Liveness: "<<difftime(time2, time1)<<" seconds"<<endl<<endl;



//    SymAutomata b(2, FormulaTree("x1&x2"), FormulaTree("x1&-x2"));
//    b.addReadTransition('a', FormulaTree("x1_1&x2_1&-x1_2&-x2_2"));
//    b.addWriteTransition('a', FormulaTree("x1_1&x2_1&x1_2&-x2_2"));
////    bdd_printall();
//    cout << (b.isLive() ? "Yes" : "No") << endl;
//
//    SymAutomata a(7, FormulaTree("((x1&x2&x3)|-x4)"), FormulaTree("x5&x6"));
//    a.addReadTransition('a', FormulaTree("x5_1&x6_2"));
//    a.addWriteTransition('a', FormulaTree("x1_1&x2_2"));
//    a.addReadTransition('b',FormulaTree("T"));
//    //bdd_printall();
//    //bdd_printtable(a.reachableStates());
//    cout << (a.isLive() ? "Yes" : "No") << endl;

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
//    A.print();
//    cout<<"Reachable States are :";
//    for ( auto & State : A.getReachableStates()){
//        cout<<State<<" ";
//    }
//    cout<<endl;
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
