#include <iostream>
using namespace std;

class Car {
    /*private constructors and a factory as a friend is my
    way of saying: "DON'T INSTANTIATE THIS CLASS DIRECTLY"*/
    friend class VehicleFactory;
    string brand;
    string model;
    int price;
    Car() {}
    Car(string nbrand, string nmodel, int nprice) {
        brand = nbrand;
        model = nmodel;
        price = nprice;
    }
    public:
        string toString() {
            return "brand: " + brand + "\nmodel: " + model + "\nprice: " + to_string(price) + '\n';
        }
};

class VehicleFactory {
    public:
        Car buildRaceCar() {
            Car car("Chevrolet", "Camaro", 1000000);
            return car;
        }
        Car buildTaxiCar() {
            Car car("Peugeot", "207", 10000);
            return car;
        }
        Car buildBestCar() {
            Car car("Chevrolet", "Chevette", 100000);
            return car;
        }
};

int main() {

    VehicleFactory vehicle_factory;

    Car mine = vehicle_factory.buildBestCar();

    cout << mine.toString();

    return 0;
}
