#include <iostream>
using namespace std;

class CharacterEnvironment {
protected:
    CharacterEnvironment() {}
public:
    virtual ~CharacterEnvironment() {};
    virtual string attack() = 0;
    virtual string run() = 0;
    virtual string whereAmI() = 0;
};

class CharacterEnvironmentSoil : public CharacterEnvironment {
public:
    string attack() override {
        return "Doing a hard earthy punch";
    }
    string run() override {
        return "Running with my nike shoes and my own legs";
    }
    string whereAmI() override {
        return "Soil";
    }
};

class CharacterEnvironmentWater : public CharacterEnvironment {
public:
    string attack() override {
        return "Doing water kicks and wet punches";
    }
    string run() override {
        return "You mean: *swimming*";
    }
    string whereAmI() override {
        return "Water";
    }
};

class Character {
    CharacterEnvironment *characterEnvironment;
public:
    void setEnvironment(CharacterEnvironment &_characterEnvironment) {
        characterEnvironment = &_characterEnvironment;
    }
    Character(CharacterEnvironment &_characterEnvironment) {
        setEnvironment(_characterEnvironment);
    }
    string attack() {
        return characterEnvironment->attack();
    }
    string run() {
        return characterEnvironment->run();
    }
    string whereAmI() {
        return characterEnvironment->whereAmI();
    }
};

int main() {

    CharacterEnvironmentSoil a;
    Character john(a);
    cout << john.attack() << '\n';

    CharacterEnvironmentWater b;
    john.setEnvironment(b);
    cout << john.run() << '\n';


    return 0;
}
