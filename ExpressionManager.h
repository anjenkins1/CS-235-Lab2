#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "ExpressionManagerInterface.h"

using namespace std;


class ExpressionManager: public ExpressionManagerInterface
{
public:
	ExpressionManager() {}
	virtual ~ExpressionManager() {}

	/*
	* Checks whether an expression has balanced parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* return true if expression is balanced
	* return false otherwise
	*/
	bool isBalanced(string expression);

	/*
	* Converts a postfix expression into an infix expression
	* and returns the infix expression.
	*
	* - The given postfix expression will have a space between every number or operator.
	* - The returned infix expression must have a space between every number or operator.
	* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix expression.
	* otherwise, return the correct infix expression as a string.
	*/
	string postfixToInfix(string postfixExpression);

	/*
	* Evaluates a postfix expression returns the result as a string
	*
	* - The given postfix expression will have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix Expression
	* otherwise, return the correct evaluation as a string
	*/
	string postfixEvaluate(string postfixExpression);

	/*
	* Converts an infix expression into a postfix expression
	* and returns the postfix expression
	*
	* - The given infix expression will have a space between every number or operator.
	* - The returned postfix expression must have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if infixExpression is not a valid infix expression.
	* otherwise, return the correct postfix expression as a string.
	*/
	string infixToPostfix(string infixExpression);

private:
	/*
	* Checks a given character if it is the left side of a parenthesis, bracket, or brace
	* 
	* returns true if t is one of the following - "(" "{" "["
	*/
	bool isLeftParen(char c);
	bool isLeftParen(string c);

	/*
	* Checks a given character if it is the right side of a parenthesis, bracket, or brace
	*
	* returns true if t is one of the following - ")" "}" "]"
	*/
	bool isRightParen(char c);
	bool isRightParen(string c);
	/*
	* Checks two strings if they are a pair of parenthesis, brackets, or braces
	*
	* 
	*/
	bool isPair(char left, char right);

	bool isPair(string left, string right);

	bool isOperator(string check);

	bool isNumber(const string& test);

	bool isValidChar(string check);

	bool processOperator(stack<string>& opStack, string& postfix, string& op);

	int precedence(string check);

	vector<string> parseTokens(string expression);

	int solveExpression(int left, int right, string op);

	void trim(string& s);
};
