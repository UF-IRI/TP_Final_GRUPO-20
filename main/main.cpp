#include "iri.cpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <funciones.h>

using namespace std;

int main()
{
    int tamP = 0;
    int tamcon = 0;
    int tamult = 0;
    int tamM = 0;
    int tamUltimos = 0;
    Paciente* pacientes = new Paciente[tamP];
    Contacto* contactos = new Contacto[tamcon];
    UltimaConsulta* consultas = new UltimaConsulta[tamult];
    Medico* Medicos = new Medico[tamM];
    UltimoMedico* ultimos = new UltimoMedico[tamUltimos];
    fstream fpPacientes;
    string routePac = (BASE_PATH + "../data_files/input/Pacientes.csv");
    
    fpPacientes.open(routePac, ios::in);
    leerPaciente(fpPacientes,pacientes, tamP);
    leercontacto(contactos, tamcon);
    leerConsultas(consultas, tamult);
    leerMedicos(Medicos, tamM);
    unicoPaciente(pacientes, tamP, consultas, tamult, contactos, tamcon);
    delete[]contactos;
    int tamv = 0;
    int tama = 0;
    Paciente* vigentes = new Paciente[tamv];
    Paciente* archivados = new Paciente[tama];
    vigentesyArchivados(pacientes, tamP, archivados, vigentes, tama, tamv);
    medicos(ultimos, pacientes, Medicos, tamP, tamM, tamUltimos);
    delete[]Medicos;
    delete[]ultimos;
    secretaria(vigentes, tamv, archivados, tama);
    archivoarchi(archivados, consultas, tama, tamult);
    delete[]consultas;
    delete[]pacientes;
    delete[]vigentes;
    delete[]archivados;

    return EXIT_SUCCESS;
}

