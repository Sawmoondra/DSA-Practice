#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValid(string s) {
    stack<char> st;

    for (char c : s) {
        // If opening bracket push to stack
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }
        // If closing bracket check top of stack
        else {
            // If stack is empty nothing to match
            if (st.empty()) return false;

            char top = st.top();
            st.pop();

            if (c == ')' && top != '(') return false;
            if (c == ']' && top != '[') return false;
            if (c == '}' && top != '{') return false;
        }
    }

    // Stack must be empty at end
    return st.empty();
}

int main() {
    cout << isValid("()")     << "\n";  // 1 = true
    cout << isValid("()[]{}")  << "\n";  // 1 = true
    cout << isValid("(]")     << "\n";  // 0 = false
    cout << isValid("([)]")   << "\n";  // 0 = false
    cout << isValid("{[]}")   << "\n";  // 1 = true

    return 0;
}