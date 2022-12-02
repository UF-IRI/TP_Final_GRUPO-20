#include <cstdlib>
#include <iostream>
#include <string>
#include <funciones.h>

using namespace std;

int main(int argc, char** argv)
{
    int tamP = 0;
    string nombrep, nombreco, nombrecons, nombrearchivados;
    Paciente* pacientes = new Paciente[tamP];
    cout << "Ingrese nombre del archivo paciente con su extension: " << endl;
    cin >> nombrep;
    cout << "Ingrese nombre del archivo contacto con su extension: " << endl;
    cin >> nombreco;
    cout << "Ingrese nombre del archivo consulta con su extension: " << endl;
    cin >> nombrecons;
    leer(pacientes, tamP, nombrep, nombreco, nombrecons);
    int tamv = 0;
    int tama = 0;
    Paciente* vigentes = new Paciente[tamv];
    Paciente* archivados = new Paciente[tama];
    cout << "Ingrese nombre del archivo archivados con su extension :" << endl;
    cin >> nombrearchivados;
    vigentyarch(pacientes, tamP, archivados, vigentes, tama, tamv);
    secretaria(vigentes, tamv, archivados, tama, nombrecons);
    archivoarchi(archivados, tama, nombrearchivados);
    delete[]pacientes;
    delete[]vigentes;
    delete[]archivados;

    return EXIT_SUCCESS;
}
