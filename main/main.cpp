#include "iri.cpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <funciones.h>

using namespace std;

int main(int argc, char** argv)
{
    int tamP = 0;
    int tamcon = 0;
    int tamult = 0;
    string nombrearchivados;
    Paciente* pacientes = new Paciente[tamP];
    Contacto* contactos = new Contacto[tamcon];
    UltimaConsulta* consultas = new UltimaConsulta[tamult];
    leerPaciente(pacientes, tamP);
    leercontacto(contactos, tamcon);
    leerConsultas(consultas, tamult);
    unicoPaciente(pacientes, tamP, consultas, tamult, contactos, tamcon);
    int tamv = 0;
    int tama = 0;
    Paciente* vigentes = new Paciente[tamv];
    Paciente* archivados = new Paciente[tama];
    cout << "Ingrese nombre del archivo archivados con su extension :" << endl;
    cin >> nombrearchivados;
    vigentyarch(pacientes, tamP, archivados, vigentes, tama, tamv);
    secretaria(vigentes, tamv, archivados, tama);
    archivoarchi(archivados, tama, nombrearchivados);
    delete[]pacientes;
    delete[]vigentes;
    delete[]archivados;

    return EXIT_SUCCESS;
}

