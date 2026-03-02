#include <iostream>
#include <memory>
using namespace std;

class Abstrata {
    protected:
        Abstrata() {}
};

class Concreta : public Abstrata {
    public:
        string dado1 = "batata";
        string dado2 = "alface";
};

void typeRacist(const Abstrata &theType) {
    cout << "Aceitou" << '\n';
}

int main() {

    unique_ptr<Abstrata> x = make_unique<Concreta>();

    typeRacist(*x);

    return 0;
}
