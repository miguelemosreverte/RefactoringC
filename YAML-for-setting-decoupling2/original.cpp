#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include "timespan.h"
using namespace std;

struct linkedTimestamp {
    float hora, min, seg, bytes, nro_destino, num;
};

class MyLinkedTimestamp {
  public:


    list <linkedTimestamp> lista;





    void toString(){
      for( auto& item : this->lista){
        cout  << setw(7) << item.hora
              << setw(7) << item.min
              << setw(7) << item.seg
              << setw(7) << item.bytes
              << setw(7) << item.nro_destino
              << endl;
      }
    };


    void cargarArchivo(string nombre_de_archivo  = "../Archivos/red1.txt"){

        ifstream entrada;
        entrada.open(nombre_de_archivo);

        if (entrada.is_open()) {

            while (!entrada.eof()) {
                linkedTimestamp aux;// = new linkedTimestamp;//chequear si es null
                entrada >> aux.hora;
                entrada >> aux.min;
                entrada >> aux.seg;
                entrada >> aux.bytes;
                entrada >> aux.nro_destino;
                this->lista.push_back(aux);
            }

            entrada.close();
        }

        //this->toString();
    };




    //Consigna 4
    void contarCantidadDePaquetesEnviados(){
        int cantidad_de_paquetes_enviados = 0;
        float acummulated_bytes = 0.0;
        float primer_nro_destino = this->lista.front().nro_destino;
        cout << "Entrando en contarCantidadDePaquetesEnviados" << endl;

        /*while (this->lista != NULL) {
            if (this->lista->nro_destino == primer_nro_destino) {
                cantidad_de_paquetes_enviados++;
                acummulated_bytes += this->lista->bytes;

            }

            this->lista = this->lista->next;

        }

        cout << "la cantidad de paquetes es: " << cantidad_de_paquetes_enviados << " son = " << acummulated_bytes / 1000 << " kilobytes " << endl;
        */
    };

    //Consigna 5
    void calcularKBpsPromedio(){};
}myLinkedTimestamps;











int main() {
    linkedTimestamp * aux = NULL;

    int begginingTimestamp = getMilliCount();

    myLinkedTimestamps.cargarArchivo();
    myLinkedTimestamps.toString();
    myLinkedTimestamps.contarCantidadDePaquetesEnviados();

    /*if (cargarArchivo() == 1) {
        cerr << "hubo algun problema interno." << endl;
    }*/

    cout << "Took " + to_string(getMilliSpan(begginingTimestamp)) +  " milliseconds";

    return 0;
}
