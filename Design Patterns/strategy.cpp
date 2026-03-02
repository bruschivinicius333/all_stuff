#include <iostream>
using namespace std;

namespace AlgorithmsToChoose {
    double summation(double num1, double num2) {
        return (num1 + num2);
    }
    double subtraction(double num1, double num2) {
        return (num1 - num2);
    }
    double multiplication(double num1, double num2) {
        return (num1 * num2);
    }
    double division(double num1, double num2) {
        return (num1 / num2);
    }
}

class AlgorithmApplierOnTwoNumbers {
    double num1, num2, (*algorithm)(double, double);
    public:
        void setNums(double _num1, double _num2) {
            num1 = _num1;
            num2 = _num2;
        }
        void setAlgorithm(double (*_algorithm)(double, double)) {
            algorithm = _algorithm;
        }
        double calculate() {
            return algorithm(num1, num2);
        }
};

int main() {

    AlgorithmApplierOnTwoNumbers aatn1;
    aatn1.setNums(5, 7);
    aatn1.setAlgorithm(AlgorithmsToChoose::summation);
    cout << aatn1.calculate() << '\n';
    aatn1.setAlgorithm([](double n1, double n2) -> double {
        return (n1 - n2);
    });
    cout << aatn1.calculate() << '\n';
    aatn1.setNums(3, 4);
    aatn1.setAlgorithm(AlgorithmsToChoose::multiplication);
    cout << aatn1.calculate() << '\n';
    aatn1.setAlgorithm(AlgorithmsToChoose::division);
    cout << aatn1.calculate() << '\n';

    return 0;
}
