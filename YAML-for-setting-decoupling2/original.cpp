#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
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
        for (auto item: this->lista){
          if(item.nro_destino == primer_nro_destino){
            cantidad_de_paquetes_enviados++;
            acummulated_bytes += item.bytes;
          }
        }

        cout << "la cantidad de paquetes es: " << cantidad_de_paquetes_enviados << " son = " << acummulated_bytes / 1000 << " kilobytes " << endl;

    };

    //Consigna 5
    void calcularKBpsPromedio(){

        std::map<int,int> timestamp_to_bytes_sent;
        for (auto item: this->lista){
          int timestamp = item.hora * 36000 + item.min * 60 + item.seg;
          timestamp_to_bytes_sent[timestamp] = item.bytes;
        }

        std::list<int> timestamps_grouped_by_range;
        int range_in_seconds = 60 * 5;
        int acummulated_seconds = 0;
        int acummulated_bytes = 0;
        for (auto item: timestamp_to_bytes_sent){
          acummulated_seconds += item.first;
          acummulated_bytes += item.second;
          if (acummulated_seconds >= range_in_seconds){
            acummulated_seconds = 0;
            timestamps_grouped_by_range.push_back(acummulated_bytes);
            acummulated_bytes = 0;
          }
        }

        for (auto item: timestamps_grouped_by_range){
          cout << "Average Kb sent every 5 minutes: " << item / 1000<< " Kbps" <<endl;
        }

    };
}myLinkedTimestamps;











int main() {
    linkedTimestamp * aux = NULL;

    int begginingTimestamp = getMilliCount();

    myLinkedTimestamps.cargarArchivo();
    myLinkedTimestamps.toString();
    myLinkedTimestamps.contarCantidadDePaquetesEnviados();
    myLinkedTimestamps.calcularKBpsPromedio();

    /*if (cargarArchivo() == 1) {
        cerr << "hubo algun problema interno." << endl;
    }*/

    cout << "Took " + to_string(getMilliSpan(begginingTimestamp)) +  " milliseconds";

    return 0;
}
