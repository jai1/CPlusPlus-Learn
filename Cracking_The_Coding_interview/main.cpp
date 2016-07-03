#include <iostream>
#include <BST.h>
#include <binaryTrees.h>
#include <heap.h>
#include <algorithms.h>
#include <LinkedList.h>
#include <Stacks.h>
#include <string>
#include <cctype>
using namespace std;
void checkBalancedParanthesis();
void infixToPostfixExp();

/* Types of Memory:-
     a. Heap:- Used to store dynamic memory
     b. Stack
     c. Static/Global
     d. Code/Text - Machine instructions.

     Size of all segments except Heap is decided at compile time
     Heap grows during runtime.
 */
void runDS()
{
    BST::learn();
    BT::learn();
    heapUsinArrays::learn();
    LinkedList::learn();
    Stacks::learn();
}

void InfixToPostfix();

void runAlgos()
{
    mergeSort::learn();
    checkBalancedParanthesis();
    InfixToPostfix();
    closest2DPoints::learn();
    QuickSort::learn();
}

void checkBalancedParanthesis()
{
    char data[]={"(9+4)-[{0+ [1 * 1]/2} * 100]"};
    char *exp=data;
    //cout<<"\nPlease Enter Some Expression ";
    //cin.getline(exp,256);
    Stacks st;
    while(*exp!='\0')
    {
        if(*exp=='(' || *exp=='[' || *exp =='{')
            st.push(*exp);
        else if(  (*exp==')' && st.peek()!='(')
                ||(*exp==']' && st.peek()!='[')
                ||(*exp=='}' && st.peek()!='{'))
                    {
                        cout<<"\nParenthesis don't match";
                        return;
                    }
        else if(*exp==')' || *exp==']' || *exp =='}')
            st.pop();
        exp++;
    }
    if(st.isEmpty())
        cout<<"\nOLA !!! All parenthesis  match";
    else
        cout<<"\nParenthesis don't match";
}

bool IsOperator(char);
int HasHigherPrecedence(char , char );
bool IsOperand(char );
// ((a + b) - c ) + (d * e) -> a b + c - d e * +
// Function to evaluate Postfix expression and return output
void InfixToPostfix()
{
   	string expression="(9+4)-[{0+ [1 * 1]/2} * 100]";
	//cout<<"Enter Infix Expression \n";
	//getline(cin,expression);

	// Declaring a Stack from Standard template library in C++.
	Stacks S;
	string postfix = ""; // Initialize postfix as empty string.
	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		if(expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(IsOperator(expression[i]))
		{
			while(!S.isEmpty() && S.peek() != '(' && HasHigherPrecedence(S.peek(),expression[i]))
			{
				postfix+= S.peek();
				S.pop();
			}
			S.push(expression[i]);
		}
		// Else if character is an operand
		else if(IsOperand(expression[i]))
		{
			postfix +=expression[i];
		}

		else if (expression[i] == '(')
		{
			S.push(expression[i]);
		}

		else if(expression[i] == ')')
		{
			while(!S.isEmpty() && S.peek() !=  '(') {
				postfix += S.peek();
				S.pop();
			}
			S.pop();
		}
	}

	while(!S.isEmpty()) {
		postfix += S.peek();
		S.pop();
	}

	cout<<"\n Output is: "<< postfix;;
}

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C)
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
		return true;

	return false;
}

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
	if(op == '$') return true;
	return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	case '$':
		weight = 3;
	}
	return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative.
	// return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ?  true: false;
}

int main()
{
    cout << "Hello world!" << endl;
    runDS();
    runAlgos();
    return 0;
}

