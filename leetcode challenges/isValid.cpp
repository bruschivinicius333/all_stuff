class Solution {
public:
    bool isValid(const string &s) {
    auto isBracketsEquivalent = [](char open, char close) -> bool { // do NOT exchange places
        if(open == '(' && close == ')') return true;
        if(open == '[' && close == ']') return true;
        if(open == '{' && close == '}') return true;
        return false;
    };
    if(s.length() <= 1) {
        return false;
    }
    stack<char> scoper;
    scoper.emplace(s[0]);
    for(ulong i = 1; i < s.length(); ++i) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
            scoper.emplace(s[i]);
        } else { // s[i] == ')' || s[i] == ']' || s[i] == '}'
            if(scoper.empty()) {
                return false;
            }
            if(!isBracketsEquivalent(scoper.top(), s[i])) {
                return false;
            }
            scoper.pop();
        } 
    }
    if(!scoper.empty()) {
        return false;
    }
    return true;
}
};
