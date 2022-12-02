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

//dni_pac , fecha_solicitado , fecha_turno , presento , matricula_med

struct ultimaConsulta
{
    unsigned int dni{};
    string fecha_solicitado;
    string fechaturno;
    unsigned int presencialidad{};
    string matricula_med;

}; typedef struct ultimaConsulta UltimaConsulta;

//dni_paciente , telefono , celular , direccion , mail
struct contacto
{
    unsigned int dni{};
    string mail;
    string celular;
    string telefono;
    string direccion;

}; typedef struct contacto Contacto;
//dni , nombre , apellido , sexo , natalicio , estado , obra_social
struct paciente
{
    int dni{};
    string nombre;
    string apellido;
    string tipoDeDoc;
    string obra_social;
    char genero{};
    Contacto con;
    UltimaConsulta consulta;
    string nac;
    string estado;

}; typedef struct paciente Paciente;
//matricula , nombre , apellido , telefono , especialidad , activo
struct medico
{
    string matricula;
    string nombre;
    string apellido;
    string telefono;
    string especialidad;
    int activo;
}; typedef struct medico Medico;


void secretaria(Paciente*& vigentes, int tamv, Paciente*& archivados, int tama);
void leer(Paciente*& array, int n);
void agregarPaciente(Paciente*& array, Paciente aux, int* n);
void vigentyarch(Paciente*& array, int n, Paciente*& archivados, Paciente*& vigentes, int tama, int tamv);
void archivoarchi(Paciente*& archivados, int tama, string nombrearchivados);
void pendiente(Paciente*& pendientes, int tamp);
void AgregarConsulta(UltimaConsulta*& consultas, UltimaConsulta aux, int* tam);
void Consultas(UltimaConsulta*& consulta, int tamC);
void eliminarVigente(Paciente*& array, int* tam, int cont);