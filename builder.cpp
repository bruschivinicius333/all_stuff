#include <iostream>
using namespace std;

class Bicicleta {
    friend class BicicletaBuilder;
    string quadro, aros, rodas, guidom;     
    Bicicleta(string _quadro, string _aros, string _rodas, string _guidom) {
        quadro = _quadro;
        aros = _aros;
        rodas = _rodas;
        guidom = _guidom;
    }
    public:
        string getQuadro() const {
            return quadro;
        }
        string getAros() const {
            return aros;
        }
        string getRodas() const {
            return rodas;
        }
        string getGuidom() const {
            return guidom;
        }
};

class BicicletaBuilder {
    string quadro, aros, rodas, guidom;     
    public:
        void setQuadro(string _quadro) {
            quadro = _quadro;
        }
        void setAros(string _aros) {
            aros = _aros;
        }        
        void setRodas(string _rodas) {
            rodas = _rodas;
        }
        void setGuidom(string _guidom) {
            guidom = _guidom;
        }
        string getQuadro() const {
            return quadro;
        }
        string getAros() const {
            return aros;
        }
        string getRodas() const {
            return rodas;
        }
        string getGuidom() const {
            return guidom;
        }
        Bicicleta build() {
            Bicicleta bicicleta(quadro, aros, rodas, guidom);
            return bicicleta;
        }
};

int main() {
    BicicletaBuilder bicicleta_builder;
    bicicleta_builder.setQuadro("Shimano");
    bicicleta_builder.setAros("Magnésio");
    bicicleta_builder.setRodas("Alumínio");
    bicicleta_builder.setGuidom("Curvado XXL");

    Bicicleta mine = bicicleta_builder.build();

    cout << mine.getQuadro() << ',' << mine.getAros() << ',' << mine.getRodas() << ',' << mine.getGuidom() << '\n';

    return 0;
}