#include <iostream>
using namespace std;

// As C++ doesn't have static classes *in the same way as Java*,
// one has to create a namespace in order to have a structure that
// works like a class, but with only a single and static instance
namespace Person {
    string name;
    uint age;
    bool sex;
    void setName(string _name) {
        name = _name;
    }
    void setAge(uint _age) {
        age = _age;
    }
    void setSex(char _sex) {
        _sex = toupper(_sex);
        sex = (_sex == 'F') ? 1 : 0;
    }
    string getName() {
        return name;
    }
    uint getAge() {
        return age;
    }
    char getSex() {
        char output = (sex == 1) ? 'F' : 'M';
        return output;
    }
    string toString() {
        return getName() + ' ' + to_string(getAge()) + ' ' + getSex() + '\0';
    }
};

int main() {

    // Person a; // This doesn't works, as it's uninstantiable;
    // Thus "only one class can be instantiated" (VIRTUALLY, obviously),
    // making it a singleton.
    // But all of this right there works, like as if it was instantiated
    // since its own declaration -- just like Java's static classes
    Person::setAge(17);
    Person::setSex('F');
    Person::setName("Camila");
    cout << Person::toString() << '\n';


    return 0;
}
