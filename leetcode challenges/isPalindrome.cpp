class Solution {
public:
    bool isPalindrome(int x) {
        const int oldX = x;
        long int reverse = 0;
        while(x > 0) {
            reverse += x % 10;
            reverse *= 10;
            x /= 10;
        }
        reverse /= 10;
        return (oldX == reverse);
    }
};
