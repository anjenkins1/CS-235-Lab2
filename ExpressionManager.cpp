#include "ExpressionManager.h"

const string OPEN = "([{";
const string CLOSE = ")]}";
const string OPERATOR = "+-*/%";
const string VALID_CHAR = "([{)]}+-*/%";

bool ExpressionManager::isBalanced(string expression) {
	cout << "isBalanced: " << expression << endl;

	stack<char> stack;	//Stack of characters
	bool balanced = true;	//Assume expression is balanced

	for (string::const_iterator itr = expression.begin();
		balanced && (itr != expression.end()); 
		++itr) {
		char next = *itr;
		if (isLeftParen(next)) {
			stack.push(next);
		} 
		else if (isRightParen(next)) {
			if (stack.empty()) {
				balanced = false;
			}
			else {
				char top = stack.top();
				stack.pop();
				balanced = isPair(top, next);
			}
		}
	}
	return balanced && stack.empty();
}

string ExpressionManager::postfixToInfix(string postfixExpression) {
	cout << "postfixToInfix: " << postfixExpression << endl;

	vector<string> input = parseTokens(postfixExpression); //string stream for string to int conversion
	stack<string> s; //stack of ints for token storage
	
	for (int i = 0; i < input.size(); i++) {
		string current = input.at(i);

		if (isNumber(current)) {
			s.push(current);
		}
		else {
			if (s.size() < 2) {
				return "invalid";
			}
			else {
				string top1 = s.top();
				s.pop();
				string top2 = s.top();
				s.pop();
				s.push("( " + top2 + " " + current + " " + top1 + " )");
			}
		}
	}
	if (s.size() == 1) {
		return s.top();
	}
	else {
		return "invalid";
	}
	
}

string ExpressionManager::postfixEvaluate(string postfixExpression) {
	cout << "postfixEvaluate: " << postfixExpression << endl;

	stack<int> s; //operand stack
	vector<string> input = parseTokens(postfixExpression); //vector of input expression

	for (int i = 0; i < input.size(); i++) {
	
		string next = input[i];
		if (isNumber(next)) {
			int num = stoi(next);
			s.push(num);
		}
		else {
			if (s.size() < 2) {
				return "invalid";
			}
			else {
				int top1 = s.top();
				s.pop();
				int top2 = s.top();
				s.pop();

				if (next == "/" && top1 == 0) {
					return "invalid";
				}

				s.push(solveExpression(top2, top1, next));
			}
		}
	}
	return to_string(s.top());
}

string ExpressionManager::infixToPostfix(string infixExpression) {
	cout << "infixToPostfix: " << infixExpression << endl;

	string postfix = ""; //initialize postfix to empty string
	stack<string> s; //operator stack
	vector<string> input = parseTokens(infixExpression); //vector of input expression
	
	if (input.size() == 1) { return "invalid"; }

	for (int i = 0; i < input.size(); i++) {
		string next = input.at(i);
		if (isNumber(next)) {
			postfix.append(next + " ");
		}
		else if (isValidChar(next)) {
			if (isOperator(next) && isOperator(input.at(i-1))) {
				return "invalid";
			}
			else if (!processOperator(s, postfix, next)) {
				return "invalid";
			}
			
		}
		else {
			return "invalid";
		}
	}

	//Add the remaining operators to the end of the postfix phrase
	while (!s.empty()) {
		if (!isOperator(s.top())) {
			return "invalid";
		}
		postfix.append(s.top() + " ");
		s.pop();
	}

	trim(postfix);
	return postfix;
}


//Helper function definitions (private)

bool ExpressionManager::isLeftParen(char c) {
	return OPEN.find(c) != string::npos;
}

bool ExpressionManager::isLeftParen(string c) {
	return OPEN.find(c) != string::npos;
}

bool ExpressionManager::isRightParen(char c) {
	return CLOSE.find(c) != string::npos;
}

bool ExpressionManager::isRightParen(string c) {
	return CLOSE.find(c) != string::npos;
}

bool ExpressionManager::isPair(char left, char right) {
	
	return OPEN.find(left) == CLOSE.find(right);
}

bool ExpressionManager::isPair(string left, string right) {

	return OPEN.find(left) == CLOSE.find(right);
}

bool ExpressionManager::isOperator(string check) {
	return OPERATOR.find(check) != string::npos;
}

bool ExpressionManager::isValidChar(string check) {
	return VALID_CHAR.find(check) != string::npos;
}

bool ExpressionManager::isNumber(const string& test) {

	string::const_iterator itr = test.begin();
	while (itr != test.end() && isdigit(*itr)) ++itr;
	return !test.empty() && itr == test.end();
}

bool ExpressionManager::processOperator(stack<string> &opStack, string &postfix, string &op) {
	if (opStack.empty() || isLeftParen(opStack.top()) || isLeftParen(op)) {
		opStack.push(op);
		return true;
	}
	else if (isRightParen(op)) {
		while (!isLeftParen(opStack.top())) {
			postfix.append(opStack.top() + " ");
			opStack.pop();
			if (opStack.empty()) {
				return false;
			}
		}
		if (!isPair(opStack.top(), op)) {
			return "invalid";
		}
		opStack.pop();
		return true;
	}
	else {
		while (!opStack.empty() && (precedence(op) <= precedence(opStack.top()))) {
			postfix.append(opStack.top() + " ");
			opStack.pop();
		}
		opStack.push(op);
		return true;
	}
}

int ExpressionManager::precedence(string check) {
	if (isRightParen(check)) {
		return 3;
	}
	if (check == "*" || check == "/" || check == "%") {
		return 2;
	}
	else if (check == "+" || check == "-") {
		return 1;
	}
	else {
		return 0;
	}
}

vector<string> ExpressionManager::parseTokens(string expression)
{
	stringstream ss(expression);
	string token;
	vector<string> tokens;
	while (getline(ss, token, ' '))
	{
		tokens.push_back(token);
	}
	return tokens;
}

int ExpressionManager::solveExpression(int left, int right, string op) {
	if (op == "+") {
		return left + right;
	}
	else if (op == "-") {
		return left - right;
	}
	else if (op == "*") {
		return left * right;
	}
	else if (op == "/") {
		return left / right;
	}
	else if (op == "%") {
		return left % right;
	}
	return 0;
}

void ExpressionManager::trim(string& s) {
	int p = s.find_last_not_of(" \t");
	if (string::npos != p) {
		s.erase(p + 1);
	}
}