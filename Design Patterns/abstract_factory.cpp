#include <iostream>
#include <math.h>
using namespace std;

class Car { // interface
    virtual string whichFuel() = 0;
    virtual void drive(int howLong) = 0;
    virtual void fill(int howMuch) = 0;
    virtual void write() = 0;
};

class Fusca : public Car {
    public:
        string whichFuel() {
            return "gasoline";
        }
        void drive(int howLong) {
            cout << "Driving for " << howLong << " kilometers" << '\n';
        }
        void fill(int howMuch) {
            cout << "Putting " << howMuch << " liters of " << whichFuel() << '\n';
        }
        void write() { // covering edge cases
            cout << "Fuscas don't write" << '\n';
        }
};

class Chevette : public Car {
    public:
        string whichFuel() {
            return "alcohol";
        }
        void drive(int howLong) {
            srand(time(0));
            cout << "Oops, it's all jammed out! -- now for " << howLong * (rand() % 10)+5 << " minutes" << '\n';
        }
        void fill(int howMuch) {
            srand(time(0));
            if(rand() % 2) {
                cout << "Putting " << whichFuel() << " in the engine" << '\n';
            } else {
            }
            cout << "The gas tank has a new hole. The fix will cost " << trunc(sqrt(howMuch)*10) << " bucks" << '\n';
        }
        void write() {
            cout << "Surprisingly, Chevettes still can't write" << '\n';
        }
};

int main() {

    Fusca f;
    f.drive(7);
    f.fill(9);
    f.write();

    cout << '\n';

    Chevette c;
    c.drive(10);
    c.fill(13);
    c.write();

    return 0;
}