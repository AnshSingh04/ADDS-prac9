#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;

string convertInfix(string prefix) {
    stack<string> infix;
    int len = prefix.size();
    for (int i =len-1; i >= 0; i--) {
        if ((prefix[i] == '+') || (prefix[i] == '-') || (prefix[i] == '*') || (prefix[i] == '/')) {
            string operand1 = infix.top();
            infix.pop();
            string operand2 = infix.top();
            infix.pop();
            if(i == 0) {
                string temp = operand1+prefix[i]+operand2;
                infix.push(temp);
            }   
            else {
                string temp = "("+operand1+prefix[i]+operand2+")";
                infix.push(temp);
            }
        } 
        else
            infix.push(string(1,prefix[i]));
            
   }
   return infix.top();
}

int evaluatePrefix(string prefix) {
    stack<int> infixSum;
    int len = prefix.size();

    for (int i=len-1; i >= 0; i--) {
        if (isdigit(prefix[i]))
            infixSum.push(prefix[i] - '0');
        else {
            int o1 = infixSum.top();
            infixSum.pop();
            int o2 = infixSum.top();
            infixSum.pop();
            if( prefix[i] == '+')
                infixSum.push(o1 + o2);
            else if( prefix[i] == '-')
                infixSum.push(o1 - o2);
            else if( prefix[i] == '*')
                infixSum.push(o1 * o2);
            else if( prefix[i] == '/')
                infixSum.push(o1 / o2);
        }
    }
    return infixSum.top();
}

int main(void) {
    stringstream ss;
    string str;
    getline(cin, str);
    replace(str.begin(), str.end(), ',', ' ');
    ss << str;
    string in;
    int num_count = 0;
    int operator_count = 0;
    string prefix;
    while (ss >> in) {   
        if(in <= "9" && in >= "0")
            num_count++;
        else if((in == "+") || (in == "-") || (in == "*") || (in == "/"))
            operator_count++;
        prefix.append(in);
    }
    if(operator_count == num_count-1) {
        string result = convertInfix(prefix);
        int res = evaluatePrefix(prefix);
        cout<<result<<"="<<res;
    }
    else
        cout<<"Error"<<endl;
}