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
    int tamp = 0;
    int tamC = 0;
    Paciente* pacientes = new Paciente[tamP];
    Contacto* contactos = new Contacto[tamcon];
    UltimaConsulta* consultas = new UltimaConsulta[tamult];
    Medico* Medicos = new Medico[tamM];
    UltimoMedico* ultimos = new UltimoMedico[tamUltimos];
    Paciente* pendientes = new Paciente[tamp];
    UltimaConsulta* con = new UltimaConsulta[tamC];

    fstream fpPacientes,fpContactos,fpConsultas,fpMedicos, fpvigentes, fparchivados, fppendientes, fpultimo;
    string paciente = (BASE_PATH + "../data_files/input/Pacientes.csv");
    string contacto = (BASE_PATH + "../data_files/input/Contactos.csv");
    string consulta = (BASE_PATH + "../data_files/input/Consultas.csv");
    string medico = (BASE_PATH + "../data_files/input/Medicos.csv");
    fpPacientes.open(paciente, ios::in);
    leerPaciente(fpPacientes,pacientes, &tamP);
    fpContactos.open(contacto, ios::in);
    leercontacto(fpContactos,contactos, &tamcon);
    fpConsultas.open(consulta, ios::in);
    leerConsultas(fpConsultas,consultas, &tamult);
    fpMedicos.open(medico, ios::in);
    leerMedicos(fpMedicos, Medicos, &tamM);
    unicoPaciente(pacientes, tamP, consultas, &tamult, contactos, &tamcon);
    delete[]contactos;
    int tamv = 0;
    int tama = 0;
    Paciente* vigentes = new Paciente[tamv];
    Paciente* archivados = new Paciente[tama];
    vigentesyArchivados(pacientes, tamP, archivados, vigentes, &tama, &tamv);
    medicos(ultimos, pacientes, Medicos, tamP, tamM, &tamUltimos);
    string ultimomedico = (BASE_PATH + "../data_files/output/UltimoMedico.csv");
    fpultimo.open(ultimomedico, ios::out);
    archivoMedicos(ultimos, tamUltimos, fpultimo);
    delete[]Medicos;
    delete[]ultimos;
    string pendient = (BASE_PATH + "../data_files/output/pendientes.csv");
    fppendientes.open(pendient, ios::out);
    secretaria(vigentes, &tamv, archivados, &tama, pendientes, &tamp, con, &tamC);
    if (tamp != 0) // si hay pendientes creamos el archivo, sino no
        pendiente(pendientes, tamp, fppendientes);
    string archi = (BASE_PATH + "../data_files/output/archivado.csv");
    fparchivados.open(archi, ios::out);
    archivoarchi(archivados, consultas, tama, tamult, fparchivados);
    if (tamC != 0)
        Consultas(con, tamC, fpConsultas);
    delete[]con;
    string vigente = (BASE_PATH + "../data_files/output/vigentes.csv");
    fpvigentes.open(vigente, ios::out);
    archivoVigentes(vigentes, tamv, fpvigentes);
    delete[]consultas;
    delete[]pacientes;
    delete[]vigentes;
    delete[]archivados;

    return EXIT_SUCCESS;
}

