class Solution {
public:
    string longestCommonPrefix(const vector<string>& strs) {

    // empty or one-element vector
    if(strs.begin() == strs.end()) {
        return "";
    }
    if(strs.begin() == --(strs.end())) {
        return strs[0];
    }

    string prefixRemains = strs[0];

    for_each(++(strs.begin()), strs.end(), [&](const string &each) {
        
        // limit for prefix
        if(each[0] != prefixRemains[0]) {
            prefixRemains = "";
            return;
        }

        // prefixRemains must be <= than the shortest element ALWAYS
        if(each.length() < prefixRemains.length()) {
            prefixRemains.resize(each.length());
        }
        
        // trim at the first different element
        int cont = 0;
        while(each[cont] && prefixRemains[cont]) {
            if(each[cont] != prefixRemains[cont]) {
                prefixRemains[cont] = '\0';
            }
            ++cont; 
        }

        // if EVERYTHING's different
        if(prefixRemains[0] == '\0') {
            return;
        }

    });

    // resize for new null-terminated length
    prefixRemains = string(prefixRemains.c_str());
    return prefixRemains;
}
};
