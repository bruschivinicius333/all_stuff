class Solution {
public:
    int romanToInt(string s) {
    for(auto &each : s) {
        each = toupper(each);
    }
    //char afterLastEach = 0;
    char lastEach = 0;
    int acum = 0;
    enum RomanNumerals {
        I = 1,
        V = 5,
        X = 10,
        L = 50,
        C = 100,
        D = 500,
        M = 1000
    };
    for(auto each : s) {
        switch (each) {
            case 'I': {
                acum += I;
                break;
            }
            case 'V': {
                if(lastEach == 'I') {
                    acum += V - 2 * I;
                } else {
                    acum += V;
                }
                break;
            }
            case 'X': {
                if(lastEach == 'I') {
                    acum += X - 2 * I;
                } else {
                    acum += X;
                }
                break;
            }
            case 'L': {
                if(lastEach == 'X') {
                    acum += L - 2 * X;
                } else {
                    acum += L;
                }
                break;
            }
            case 'C': {
                if(lastEach == 'X') {
                    acum += C - 2 * X;
                } else {
                    acum += C;
                }
                break;
            }
            case 'D': {
                if(lastEach == 'C') {
                    acum += D - 2 * C;
                } else {
                    acum += D;
                }
                break;
            }
            case 'M': {
                if(lastEach == 'C') {
                    acum += M - 2 * C;
                } else {
                    acum += M;
                }
                break;
            }
        };
        lastEach = each;
    }
    return acum;
}
};
