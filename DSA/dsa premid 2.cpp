#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

class itemtype {
public:
    string key;
    itemtype() {}
    itemtype(string k) {
        key = k;
    }

    bool operator==(const itemtype& other) const {
        return key == other.key;
    }

    friend ostream& operator<<(ostream& os, const itemtype& item) {
        os << item.key;
        return os;
    }
};

const int max_item = 100;

class Stack {
private:
    itemtype info[max_item];
    int top;
public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == max_item - 1;
    }

    void push(itemtype item) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
        }
        else {
            top++;
            info[top] = item;
        }
    }

    void pop() {
        if (isEmpty()) {
            throw out_of_range("Stack Underflow!");
        }
        else {
            top--;
        }
    }

    itemtype peek() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return info[top];
    }

    bool hasElements() { return !isEmpty(); }
};



int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Infix to Postfix
string infixToPostfix(string infix) {
    Stack st;
    string result = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            st.push(itemtype(string(1, c)));
        }
        else if (c == ')') {
            bool foundOpening = false;
            while (st.hasElements()) {
                if (st.peek().key == "(") {
                    st.pop();
                    foundOpening = true;
                    break;
                }
                result += st.peek().key;
                st.pop();
            }
            if (!foundOpening) {
                throw invalid_argument("Error: Unbalanced parentheses (extra ')')");
            }
        }
        else if (isOperator(c)) {
            while (st.hasElements() && precedence(st.peek().key[0]) >= precedence(c)) {
                if (c == '^' && st.peek().key[0] == '^') break;
                result += st.peek().key;
                st.pop();
            }
            st.push(itemtype(string(1, c)));
        }
        else {
            throw invalid_argument(string("Error: Invalid character '") + c + "'");
        }
    }


    while (st.hasElements()) {
        if (st.peek().key == "(") {
            throw invalid_argument("Error: Unbalanced parentheses (extra '(')");
        }
        result += st.peek().key;
        st.pop();
    }

    return result;
}

//infix to prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}


int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    cin >> infix;

    try {
        string postfix = infixToPostfix(infix);
        string prefix = infixToPrefix(infix);

        cout << "Postfix: " << postfix << endl;
        cout << "Prefix: " << prefix << endl;
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}