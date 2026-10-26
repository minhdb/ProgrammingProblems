/**
 * EPI Chapter 09 Stacks and Queues
 *
 * A string is said to be an arithmetical expression in Reverse Polish Notation
 * (RPN) if:
 *
 * (1.) It is a single digit or a sequence of digits, prefixed with an option -
 * e.g., "6", "123", "-42"
 * (2.) It is a form "A, B, o" where A and B are RPN expressions and o is one
 * of +, -, x, /
 *
 * For example, the followign strings satisfy these rules: "1729",
 * "3,4,+,2,x,1,+",
 * "1,1,+,-2,x",
 * "-641,6,/,28,/"
 *
 * An RPN expression can be evaluated uniquely to an integer, which is
 * determined recursively. The base case corresponds to rule (1.), which is an
 * integer expressed in base-10 positional system. Rule (2.) corresponds to the
 * recursive case, and the RPNs are evaluated in the natural way, e.g., if A
 * evaluates to 2 and B evaluates to 3, then "A,B,x" evaluates to 6.
 *
 * Write a program that takes an arithmetical expression in RPN and returns the
 * expression evaluates to.
 *
 * Hint: Process subexpressions, keeping values in a stack. How should
 * operators be handled?
 */

#include <string>
#include <stack>
#include <sstream>
#include <cassert>
#include <cstdio>

using std::stack;
using std::string;
using std::istringstream;

/**
 * Create a stack of ints. Assume the input is valid.
 *
 * For each string, delimitted by a comma, in the expression
 * 1. If it's a number, push it onto the stack.
 * 2. if it's either +, -, x, /, pop 2 elements from the stack
 * and evaluate the expression according to the operator. Push back
 * the result onto the stack.
 *
 * Time complexity: O(n) from the length of the expression.
 * Space complexity: O(m) where m is the number of operators.
 */
int Eval(const string& rpn_expression)
{
    stack<int> s;

    istringstream in(rpn_expression);
    string token;

    while(std::getline(in, token, ',')) {
        if (token[0] == '+') {
            int second_op = s.top();
            s.pop();
            int first_op = s.top();
            s.pop();
            s.emplace(first_op + second_op);
        } else if (token.size() == 1 && token[0] == '-') {
            int second_op = s.top();
            s.pop();
            int first_op = s.top();
            s.pop();
            s.emplace(first_op - second_op);
        } else if (token[0] == '*') {
            int second_op = s.top();
            s.pop();
            int first_op = s.top();
            s.pop();
            s.emplace(first_op * second_op);
        } else if (token[0] == '/') {
            int second_op = s.top();
            s.pop();
            int first_op = s.top();
            s.pop();
            // printf("%d / %d = %d\n", first_op, second_op, first_op/second_op);
            s.emplace(first_op / second_op);
        } else {
            // printf("%d\n",std::stoi(token));
            s.emplace(std::stoi(token));
        }
    }
    return s.top();
}


 /*
  * (1.) It is a single digit or a sequence of digits, prefixed with an option -
  * e.g., "6", "123", "-42"
  * (2.) It is a form "A, B, o" where A and B are RPN expressions and o is one
  * of +, -, x, /
  *
  * For example, the followign strings satisfy these rules: "1729",
  * "3,4,+,2,x,1,+",
  * "1,1,+,-2,x",
  * "-641,6,/,28,/"
  */

int main()
{ 
    string tc1("6");
    assert(Eval(tc1) == 6);
    printf("Test case 1 passed.\n");

    string tc2("-42");
    assert(Eval(tc2) == -42);
    printf("Test case 2 passed.\n");

    string tc3("123");
    assert(Eval(tc3) == 123);
    printf("Test case 3 passed.\n");

    string tc4("1729");
    assert(Eval(tc4) == 1729);
    printf("Test case 4 passed.\n");

    string tc5("3,4,+,2,*,1,+");
    assert(Eval(tc5) == 15);
    printf("Test case 5 passed.\n");

    string tc6("1,1,+,-2,*");
    assert(Eval(tc6) == -4);
    printf("Test case 6 passed.\n");
    
    string tc7("-641,6,/,28,/");
    assert(Eval(tc7) == -3);
    printf("Test case 7 passed.\n");

    string tc8("-641,6,/,28,/,7,*,56,+");
    assert(Eval(tc8) == 35);
    printf("Test case 8 passed.\n");

    return 0;
}
