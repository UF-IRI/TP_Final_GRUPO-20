#include <fstream>
#include <ctime>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

struct fecha
{
    unsigned int dia{};
    unsigned int mes{};
    unsigned int anio{};
};


struct ultimaConsulta
{
    time_t fechaC{};
    string motivo;
    string obrasocial;
    string nombreMed;
    string apellidoMed;
    unsigned int numMed{};
    string mailMed;

}; typedef struct ultimaConsulta UltimaConsulta;


struct contacto
{
    unsigned int telefono{};
    string mail;
    string pais;
    string ciudad;
    string calle;
    unsigned int numDireccion{};
    int piso{};
    char depto{};

}; typedef struct contacto Contacto;

struct paciente
{
    unsigned int codigo{};
    string nombre;
    string apellido;
    string tipoDeDoc;
    unsigned int numDeDoc{};
    char genero{};
    Contacto con;
    UltimaConsulta consulta;
    fecha nac;
    string estado;

}; typedef struct paciente Paciente;



void secretaria(Paciente*& vigentes, int tamv, Paciente*& archivados, int tama, string nombrecons);
void leer(Paciente*& array, int n, string  nombrep, string nombreco, string nombrecons);
void agregarPaciente(Paciente*& array, Paciente aux, int* n);
void vigentyarch(Paciente*& array, int n, Paciente*& archivados, Paciente*& vigentes, int tama, int tamv);
void archivoarchi(Paciente*& archivados, int tama, string nombrearchivados);
void pendiente(Paciente*& pendientes, int tamp);
void AgregarConsulta(UltimaConsulta*& consultas, UltimaConsulta aux, int* tam, int*& codes, int code);
void Consultas(UltimaConsulta*& consulta, int tamC, string nombre, int*& code);
void eliminarVigente(Paciente*& array, int* tam, int cont);