#include <iostream>
#include "arithmeticExpression.h"

using namespace std;

int main(){
    // Test expression 1
    string expr1 = "a+b*c";
    arithmeticExpression ex1(expr1);    // Create tree object
    ex1.buildTree();                    // Build the expression tree
    cout<<"expression 1: "<<expr1<<endl;
    cout<<"infix: "; ex1.infix(); cout<<endl;     // Print in infix form
    cout<<"prefix: "; ex1.prefix(); cout<<endl;   // Print in prefix form
    cout<<"postfix: "; ex1.postfix(); cout<<endl; // Print in postfix form
    //ex1.visualizeTree("expr1.dot");   // Optional: generate dot file
    cout<<endl;

    // Test expression 2
    string expr2 = "(a+b)*(c-d)";
    arithmeticExpression ex2(expr2);
    ex2.buildTree();
    cout<<"expression 2: "<<expr2<<endl;
    cout<<"infix: "; ex2.infix(); cout<<endl;
    cout<<"prefix: "; ex2.prefix(); cout<<endl;
    cout<<"postfix: "; ex2.postfix(); cout<<endl;
    //ex2.visualizeTree("expr2.dot");
    cout<<endl;

    // Test expression 3
    string expr3 = "a + b * c - ( d * e + f ) * g";
    arithmeticExpression ex3(expr3);
    ex3.buildTree();
    cout<<"expression 3: "<<expr3<<endl;
    cout<<"infix: "; ex3.infix(); cout<<endl;
    cout<<"prefix: "; ex3.prefix(); cout<<endl;
    cout<<"postfix: "; ex3.postfix(); cout<<endl;
    //ex3.visualizeTree("expr3.dot");
    cout<<endl;

    return 0;
}
