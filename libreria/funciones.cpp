#include "funciones.h"

//leemos paciente y los pasamos a una array dinamico
void leerPaciente(fstream& fpPacientes, Paciente*& array, int n)
{
	//abrimos los archivos.
	if (!(fpPacientes.is_open())) //comprobamos que abrieron.
		return;

	string dummys;
	char coma;
	//sacamos el header de paciente.
	fpPacientes >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;

	Paciente aux;//guarda la informacion provisionalmente

	while (fpPacientes)
	{
		//extraemos la informacion del paciente.
		fpPacientes >> aux.dni >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.genero >> coma >> aux.nac >> coma >> aux.estado >> coma >> aux.obra_social;
		agregarPaciente(array, aux, &n);
	}

	fpPacientes.close();

	return;
}
//leemos consultas y las guardamos en un array dinamico
void leerConsultas(UltimaConsulta*& array, int n)
{
	fstream fpConsultas;

	fpConsultas.open("Consultas.csv", ios::in);

	if (!(fpConsultas.is_open()))
		return;

	char coma;
	string dummys;
	UltimaConsulta aux;
	string fechAux;
	stringstream str;
	string fecha;
	int anio, dia, mes;
	time_t fechaC;
	tm* consulta = new tm;

	fpConsultas >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;

	while (fpConsultas)
	{
		fpConsultas >> aux.dni >> coma >> aux.fecha_solicitado >> coma >> fecha >> coma >> aux.presencialidad >> coma >> aux.matricula_med;

		str << fecha;
		getline(str, fechAux, '/');
		dia = stoi(fechAux);//convierte un string en int.
		getline(str, fechAux, '/');
		mes = stoi(fechAux);
		getline(str, fechAux, '/');
		anio = stoi(fechAux);
		time(&fechaC);
		localtime_s(consulta, &fechaC);
		consulta->tm_sec = 0;
		consulta->tm_year = anio - 1900;
		consulta->tm_mon = mes - 1;
		consulta->tm_hour = 0;
		consulta->tm_min = 0;
		consulta->tm_mday = dia;
		aux.fechaturno = mktime(consulta);

		AgregarConsulta(array, aux, &n);
		
	}
	delete consulta;
	fpConsultas.close();
} //
//leemos contacto y los guardamos en un array dinamico
void leercontacto(Contacto*& con, int n) {
	fstream fpContactos;
	Contacto aux;

	fpContactos.open("Contactos.csv", ios::in);

	if (!(fpContactos.is_open()))
		return;

	string dummys;
	char coma;

	fpContactos >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;

	while (fpContactos) 
	{
		fpContactos >> aux.dni >> coma >> aux.telefono >> coma >> aux.celular >> coma;
		getline(fpContactos, aux.direccion, ',');
		fpContactos >> aux.mail;
		agregarContacto(con, aux, &n);
	}

	fpContactos.close();
}
//leemos medicos y los guardamos en un array dinamico
void leerMedicos(Medico*& array, int n)
{
	fstream fpmedicos;

	fpmedicos.open("Medicos.csv", ios::in);

	if (!(fpmedicos.is_open()))
		return;

	string dummys;
	char coma;
	Medico aux;

	fpmedicos >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;

	while (fpmedicos)
	{
		fpmedicos >> aux.matricula >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.telefono >> coma >> aux.especialidad >> coma >> aux.activo;
		agregarMedicos(array, aux, &n);
	}

	fpmedicos.close();
	return;
}
//agregamos el auxiliar de medico a el array dinamico
void agregarMedicos(Medico*& medicos, Medico aux, int* tam)
{
	*tam = *tam + 1;
	int i = 0;
	Medico* aux1 = new Medico[*tam];

	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = medicos[i];
		i++;
	}
	aux1[i] = aux;

	delete[]medicos;
	medicos = aux1;
	return;
}
//agregamos el auxiliar de contacto a el array dinamico
void agregarContacto(Contacto*& con, Contacto aux, int* tam) {
	*tam = *tam + 1;
	int i = 0;
	Contacto* aux1 = new Contacto[*tam];

	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = con[i];
		i++;
	}
	aux1[i] = aux;

	delete[]con;
	con = aux1;
	return;
}
//agregamos el auxiliar de paciente a el array dinamico
void agregarPaciente(Paciente*& array, Paciente aux, int* tam) {
	*tam = *tam + 1;
	int i = 0;
	Paciente* aux1 = new Paciente[*tam];

	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = array[i];
		i++;
	}
	aux1[i] = aux;

	delete[]array;
	array = aux1;
	return;
}
//agregamos el auxiliar de consulta a el array dinamico
void AgregarConsulta(UltimaConsulta*& consultas, UltimaConsulta aux, int* tam)
{
	*tam = *tam + 1;
	int i = 0;
	UltimaConsulta* aux1 = new UltimaConsulta[*tam];

	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = consultas[i];
		i++;
	}
	aux1[i] = aux;

	delete[]consultas;
	consultas = aux1;
	return;
}
//unificamos el array dinamico de pacientes con la ultima consulta del mismo y su contacto
void unicoPaciente(Paciente*& array, int tamp, UltimaConsulta*& ult, int tamult, Contacto*& con, int tamcon) {
	int i,k,j;
	time_t max;

	for (i = 0; i < tamp; i++) {
		for (k = 0; k < tamcon; k++) {
			if (array[i].dni == con[k].dni) {
				array[i].con.celular = con[k].celular;
				array[i].con.direccion = con[k].direccion;
				array[i].con.mail = con[k].mail;
				array[i].con.telefono = con[k].telefono;
				break;
			}
		}
		max = 0;
		for (j = 0; j < tamult; j++) 
		{
			if (array[i].dni == ult[j].dni && max < ult[j].fechaturno && ult[i].presencialidad == 1) {
				max = ult[j].fechaturno;
				array[i].consulta.fechaturno = ult[j].fechaturno;
				array[i].consulta.fecha_solicitado = ult[j].fecha_solicitado;
				array[i].consulta.matricula_med = ult[j].matricula_med;
				array[i].consulta.presencialidad = ult[j].presencialidad;
			}
		}
	}
	return;
}
//separamos los pacientes entre vigentes y archivados
void vigentesyArchivados(Paciente*& array, int n, Paciente*& archivados, Paciente*& vigentes, int tama, int tamv)//vigentes y archivados
{
	int i;
	time_t now = time(NULL);

	for (i = 0; i < n; i++) {

		if (difftime(now, array[i].consulta.fechaturno) < 315532800 && (array[i].estado != "fallecido" || array[i].estado != "internado"))
			// solo pusimos la cantidad de segundos de 8 años de 365 dias y 2 bisiestos porque sabemos que hay seguro dos años bisiestos en 10 años
			//y consideramos que 1 dia es despreciable respecto a la cantidad que se quiere calcular
			agregarPaciente(vigentes, array[i], &tamv);

		else
			agregarPaciente(archivados, array[i], &tama);
	}
	return;
}
//sacamos la informacion del ultimo medico que atendio al respectivo paciente y creamos un archivo con eso
void medicos(UltimoMedico *&ultimos, Paciente*& array, Medico*& med, int tamP, int tamM, int tamUltimos)
{
	int i, j;
	UltimoMedico aux;

	for (i = 0; i < tamP; i++)
	{
		for (j = 0; j < tamM; j++)
		{
			if (array[i].consulta.matricula_med == med[j].matricula)
			{
				aux.activo = med[j].activo;
				aux.apellidoM = med[j].apellido;
				aux.apellidoP = array[i].apellido;
				aux.dni = array[i].dni;
				aux.especialidad = med[j].especialidad;
				aux.matricula = med[j].matricula;
				aux.nombreM = med[j].nombre;
				aux.nombreP = array[i].nombre;
				aux.obra_social = array[i].obra_social;
				aux.telefonoM = med[j].telefono;
				ultimosMedicos(ultimos, aux, &tamUltimos);
			}
		}
	}
	archivoMedicos(ultimos, tamUltimos);
}
//agregamos el auxiliar de ultimomedico a el array dinamico
void ultimosMedicos(UltimoMedico*& array, UltimoMedico aux, int* tam)
{
	*tam = *tam + 1;
	int i = 0;
	UltimoMedico* aux1 = new UltimoMedico[*tam];

	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = array[i];
		i++;
	}
	aux1[i] = aux;

	delete[]array;
	array = aux1;
	return;
}
//creamos el archivo que contiene a los ultimos medicos que atendieron a los pacientes
void archivoMedicos(UltimoMedico*& array, int tam)
{
	fstream fpUltimos;
	int i;

	fpUltimos.open("UltimosMedico.csv", ios::out);

	if (!(fpUltimos.is_open()))
		return;

	fpUltimos << "DNI del paciente, Nombre del paciente, Apellido del paciente, Obra social, Nombre del medico, Apellido del medico, Matricula, Especialidad, Telefono del medico, Activo" << endl;

	for (i = 0; i < tam; i++)
	{
		fpUltimos << array[i].dni << ',' << array[i].nombreP << ',' << array[i].apellidoP << ',' << array[i].obra_social << ',' << array[i].nombreM << ',' << array[i].apellidoM << ',' 
			<< array[i].matricula<< ',' << array[i].especialidad << ',' << array[i].telefonoM << ',' << array[i].activo << endl;
	}

	fpUltimos.close();
	return;
}
//funcion que usa la secretaria para determinae si vuelven o no los pacientes
void secretaria(Paciente*& vigentes, int tamv, Paciente*& archivados, int tama) {
	int dni = 0;
	int condicion = 0;//la condicion para salir del for
	int cont2 = 0;
	int tamp = 0, tamC = 0;
	int i;
	tm* auxi = new tm;
	Paciente* pendientes = new Paciente[tamp];
	Paciente aux2;
	UltimaConsulta* consultas = new UltimaConsulta[tamC];
	UltimaConsulta aux;
	int pos;
	string respuesta;
	char fechaS[36];
	char fechaT[36];

	do {
		cout << "Ingrese el dni del paciente a buscar: ";
		cin >> dni;
		for (i = 0; i < tamv; i++)
		{
			if (dni == vigentes[i].dni) {
				condicion = 1;
				pos = i;
				break;
			}
		}
	} while (condicion < 1);

	int opcion;
	bool repetir = true;

	do {
		system("cls"); //se borra lo de la pantalla

		// Texto del menú que se verá cada vez
		cout << "******** MENU DE OPCIONES ********" << endl;
		cout << "Paciente " << vigentes[pos].nombre << " " << vigentes[pos].apellido << " ,con DNI : " << vigentes[pos].dni << endl;
		cout << "1. Si el paciente retorna" << endl;
		cout << "2. Si el paciente no retorna" << endl;
		cout << "3. Si el paciente no atendio" << endl;
		cout << "4. SALIR" << endl;

		cout << "Ingrese una opcion: " << endl;
		cin >> opcion;

		switch (opcion) {
		case 1:
			time_t now;
			int month, year, day, hora, minutos;
			cout << "Ingresar los datos de la proxima consulta" << endl;
			cout << "Ingresar hora de la consulta: " << endl;
			cin >> hora;
			cout << "Ingrese el minuto de la consulta: " << endl;
			cin >> minutos;
			cout << "Ingrese el dia: " << endl;
			cin >> day;
			cout << "Ingrese el mes: ";
			cin >> month;
			cout << "Ingrese el anio: " << endl;
			cin >> year;
			time(&now);
			localtime_s(auxi, &now);
			asctime_s(fechaS, 36, auxi);
			aux.fecha_solicitado = fechaS;
			auxi->tm_sec = 0;
			auxi->tm_year = year - 1900;
			auxi->tm_mon = month - 1;
			auxi->tm_hour = hora;
			auxi->tm_min = minutos;
			auxi->tm_mday = day;
			aux.fechaturno = mktime(auxi);

			cout << "¿El Paciente cambio la obra social?(responder con si o no) " << endl;
			cin >> respuesta;
			if (respuesta == "si" || respuesta == "Si" || respuesta == "SI") {
				cout << "Ingrese la obra social nueva:" << endl;
				cin >> vigentes[pos].obra_social;

			}
			aux.matricula_med = vigentes[pos].consulta.matricula_med;
			aux.dni = vigentes[pos].dni;

			AgregarConsulta(consultas, aux, &tamC);//guardamos consultas para ingresarlas al archivo luego

			system("pause>nul"); // Pausa
			break;

		case 2:
			// Lista de instrucciones de la opción 2                
			for (i = 0; i < tamv; i++)
			{
				if (dni == vigentes[i].dni) {
					aux2 = vigentes[i];
					agregarPaciente(archivados, aux2, &tama);//pasamos el paciente que no vuelve a archivados.
					for (int y = i; y < tamv - 1; y++)
					{
						vigentes[y] = vigentes[y + 1];
						cont2++;
					}
				}
			}
			system("pause>nul"); // Pausa
			break;

		case 3:

			for (i = 0; i < tamv; i++)
			{
				if (dni == vigentes[i].dni) {
					aux2 = vigentes[i];
					agregarPaciente(pendientes, aux2, &tamp);
					for (int y = i; y < tamv - 1; y++)
					{
						vigentes[y] = vigentes[y + 1];
						cont2++;
					}
				}
			}
			system("pause>nul");
			break;

		case 4:
			repetir = false;
			break;
		}
	} while (repetir);

	if (tamp != 0) // si hay pendientes creamos el archivo, sino no
		pendiente(pendientes, tamp);
	delete[]pendientes;

	Consultas(consultas, tamC);
	delete[]consultas;

	eliminarVigente(vigentes, &tamv, cont2);
	archivoVigentes(vigentes, tamv);

}
//crea el archivo pendientes que se utiliza para guardar a aquellos que no contestan el celular(caso 3 del menu)
void pendiente(Paciente*& pendientes, int tamp) {
	char c = ',';
	fstream fp;
	fp.open("Pendientes.csv", ios::out);
	if (!(fp.is_open()))
		return;

	fp << "DNI , Nombre , Apellido , Sexo , Natalicio , Estado , Obra_Social " << endl; // le escribo el header

	for (int i = 0; i < tamp; i++) {
		fp << pendientes[i].dni << c << pendientes[i].nombre << c << pendientes[i].apellido << c << pendientes[i].genero << c << pendientes[i].nac
			<< c << pendientes[i].estado << c << pendientes[i].obra_social << endl;
	}
	fp.close();
}
//se agregan las nuevas consultas al archivo original(caso 1 del menu)
void Consultas(UltimaConsulta*& consulta, int tamC)
{
	fstream fp;
	tm* aux = new tm;
	char fecha[36];

	fp.open("Consultas.csv", ios::app);
	if (!(fp.is_open()))
		return;
	for (int i = 0; i < tamC; i++)
	{
		localtime_s(aux, &consulta[i].fechaturno);
		asctime_s(fecha, 36, aux);
		fp << consulta[i].dni << ',' << consulta[i].fecha_solicitado << ',' << fecha << ',' << consulta[i].presencialidad << ',' << consulta[i].matricula_med << endl;
	}

	fp.close();
	return;
}
//elimina los vigentes que no retornaran o no contestan(caso 2 del menu)
void eliminarVigente(Paciente*& array, int* tam, int cont)
{
	*tam = *tam - cont;
	int i = 0;
	paciente* aux1 = new paciente[*tam];

	while (i < *tam) {
		aux1[i] = array[i];
		i++;
	}
	delete[] array;
	array = aux1;

}
//guardamos a todos los pacientes que no retornaran por diferentes circunstancias
void archivoarchi(Paciente*& archivados, UltimaConsulta*& consultas, int tama, int tamC) {
	fstream fparchivados;
	char c = ',';

	fparchivados.open("archivado.csv", ios::app);

	if (!(fparchivados.is_open())) //comprobamos que abrieron.
		return;

	fparchivados << "DNI, Nombre, Apellido, Genero, Nacimiento, Estado, Obra social, Fecha de solicitud de turno, Fecha del turno, Presencialidad, Matricula del medico" << endl;

	for (int i = 0; i < tama; i++) {//copiamos en el archivo , los archivados.
		for (int j = 0; i < tamC; i++)
		{
			if (archivados[i].dni == consultas[i].dni)
				fparchivados << archivados[i].dni << c << archivados[i].nombre << c << archivados[i].apellido << c << archivados[i].genero << c << archivados[i].nac << c << archivados[i].estado
				<< c << archivados[i].obra_social << c << consultas[i].fecha_solicitado << c << consultas[i].fechaturno << c << consultas[i].presencialidad << c << consultas[i].matricula_med << endl;
		}
	}

	fparchivados.close();
	return;
}
//guardamos los vigentes en su respectivo archivo
void archivoVigentes(paciente*& vigentes, int tamv) {
	fstream fpv;
	int i;
	char c = ',';

	fpv.open("vigentes.csv", ios::out);

	if (!(fpv.is_open()))
		return;

	fpv << "DNI , Nombre , Apellido , Sexo , Natalicio , Estado , Obra_social"<<endl;

	for (i = 0; i < tamv; i++) {
		fpv << vigentes[i].dni << c << vigentes[i].nombre << c << vigentes[i].apellido << c << vigentes[i].genero << c << vigentes[i].nac << c 
			<< vigentes[i].estado << c << vigentes[i].obra_social << endl;
	}
	fpv.close();
	return;
}