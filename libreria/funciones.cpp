#include "funciones.h"

void leer(Paciente*& array, int n)
{
	fstream fpPacientes, fpContactos, fpConsultas;
	//abrimos los archivos.
	fpPacientes.open("Pacientes.csv", ios::in);
	fpContactos.open("Contactos.csv", ios::in);
	fpConsultas.open("Consultas.csv", ios::in);
	if (!(fpPacientes.is_open() && fpContactos.is_open() && fpConsultas.is_open())) //comprobamos que abrieron.
		return;
	string dummys;
	char coma;
	//sacamos los headers de paciente.
	fpPacientes >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;

	Paciente aux;//guarda la informacion provisionalmente
	int dni;
	while (fpPacientes)
	{
		//saco los headers cada vez que repito el ciclo de los otros dos archivos.
		fpContactos >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;
		fpConsultas >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;
		//extraemos la informacion del paciente.
		fpPacientes >> aux.dni >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.genero >> coma >> aux.nac >> coma >> aux.estado >> coma >> aux.obra_social;

		while (fpContactos) //recorremos el archivo hasta encontrar el contacto con el mismo codigo que el paciente.
		{
			fpContactos >> dni >> coma >> aux.con.telefono >> coma >> aux.con.celular >> coma >> aux.con.direccion >> coma >> aux.con.mail; //extraemos la informacion.
			if (aux.dni == dni) // en caso de que el codigo coincida, se termina el ciclo
			{
				aux.con.dni = dni;
				break;
			}
		}

		fpContactos.seekg(fpContactos.beg);

		double max = 0; // guarda la fecha maxima y la que se saca del archivo.
		time_t seconds;
		string fechaC;
		string fechaS;

		while (fpConsultas)
		{
			fpConsultas >> dni >> coma >> fechaS >> coma >> fechaC >> coma;


			if (aux.dni == dni && max < fechaC)
			{
				max = seconds; //guardo la fecha max.
				aux.consulta.fechaturno = seconds;
				aux.consulta.fecha_solicitado = fechaS;
				fpConsultas >> aux.consulta.presencialidad >> coma >> aux.consulta.matricula_med;
			}
			else
				fpConsultas >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys >> coma >> dummys;
		}

		fpConsultas.seekg(fpConsultas.beg);

		agregarPaciente(array, aux, &n);

	}

	fpPacientes.close();
	fpContactos.close();
	fpConsultas.close();

	return;
}

void agregarPaciente(Paciente*& array, Paciente aux, int* tam) {
	*tam = *tam + 1;
	int i = 0;
	Paciente* aux1 = new Paciente[*tam];
	int* aux2 = new int[*tam];
	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = array[i];
		i++;
	}
	aux1[i] = aux;

	delete[]array;
	array = aux1;
	return;
}

void vigentyarch(Paciente*& array, int n, Paciente*& archivados, Paciente*& vigentes, int tama, int tamv)//vigentes y archivados
{
	int i;
	time_t now = time(NULL);
	Paciente aux;
	time_t consulta;
	for (i = 0; i < n; i++) {

		if (difftime(now, consulta) < 315532800 && (array[i].estado != "fallecido" || array[i].estado != "internado"))
			// solo pusimos la cantidad de segundos de 8 años de 365 dias y 2 bisiestos porque sabemos que hay seguro dos años bisiestos en 10 años
			//y consideramos que 1 dia es despreciable respecto a la cantidad que se quiere calcular
			agregarPaciente(vigentes, array[i], &tamv);

		else
			agregarPaciente(archivados, array[i], &tama);
	}

}


void archivoarchi(Paciente*& archivados, int tama, string nombrearchivados) {
	fstream fparchivados;
	char c = ',';
	fparchivados.open(nombrearchivados, ios::app);
	if (!(fparchivados.is_open())) //comprobamos que abrieron.
		return;

	for (int i = 0; i < tama; i++) {//copiamos en el archivo , los archivados.
		fparchivados << archivados[i].dni << c << archivados[i].nombre << c << archivados[i].apellido << c << archivados[i].genero << c << archivados[i].nac
			<< c << archivados[i].estado << c << archivados[i].obra_social << endl;
	}
	fparchivados.close();
	return;
}//guarda en archivo los archivados hallados en vigentyarch.

void medico(Paciente*& array, int n)
{
	fstream fp, fp2;
	string dummy;
	Medico aux;
	char c;
	int i = 0;

	fp.open("UltimosMedicos.csv", ios::out);//no pedimos el nombre del archivo porque lo creamos nosotros
	fp2.open("Medicos.csv", ios::in);
	if (!(fp.is_open() && fp2.is_open()))
		return;

	fp << "Matricula, Nombre, Apellido, Telefono, Especialidad, Activo, Obra social" << endl;
	fp2 >> dummy >> c >> dummy >> c >> dummy >> c >> dummy >> c >> dummy >> c >> dummy >> c >> dummy;
	while(fp2)
	{
		fp2 << aux.matricula << c << aux.nombre << c << aux.apellido << c << aux.telefono << c << aux.especialidad << c << aux.activo;
		for (i = 0; i < n; i++)
		{
			if (array[i].consulta.matricula_med == aux.matricula)
			{
				fp << aux.matricula << ',' << aux.nombre << ',' << aux.apellido << ',' << aux.telefono << ','
					<< aux.especialidad << ',' << aux.activo << ',' << array[i].obra_social << endl;
			}
		}
	}
	
	fp.close();
	return;
}

void secretaria(Paciente*& vigentes, int tamv, Paciente*& archivados, int tama, string nombrecons) {
	int code = 0;
	int condicion = 0;//la condicion para salir del for
	int cont2 = 0;
	int tamp = 0, tamC = 0;
	int i;
	tm* auxi = new tm;
	int* codes = new int[tamC];
	Paciente* pendientes = new Paciente[tamp];
	Paciente aux2;
	UltimaConsulta* consultas = new UltimaConsulta[tamC];
	UltimaConsulta aux;
	do {
		cout << "Ingrese el codigo del paciente a buscar: ";
		cin >> code;
		for (i = 0; i < tamv; i++)
		{
			if (code == vigentes[i].codigo) {
				condicion = 1;

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
		cout << "Paciente " << vigentes[i].nombre << " " << vigentes[i].apellido << " ,con codigo : " << vigentes[i].codigo << endl;
		cout << "1. Si el paciente retorna" << endl;
		cout << "2. Si el paciente no retorna" << endl;
		cout << "3. Si el paciente no atendio" << endl;
		cout << "4. SALIR" << endl;

		cout << "Ingrese una opcion: " << endl;
		cin >> opcion;

		switch (opcion) {
		case 1:
			time_t now;
			int month, year, hour, minute, day;
			cout << "Ingresar los datos de la proxima consulta" << endl;
			cout << "Ingrese la hora: " << endl;
			cin >> hour;
			cout << "Ingrese los minuto: " << endl;
			cin >> minute;
			cout << "Ingrese el dia: " << endl;
			cin >> day;
			cout << "Ingrese el mes: ";
			cin >> month;
			cout << "Ingrese el anio: " << endl;
			cin >> year;
			time(&now);
			localtime_s(auxi, &now);
			auxi->tm_sec = 0;
			auxi->tm_year = year - 1900;
			auxi->tm_mon = month - 1;
			auxi->tm_hour = hour;
			auxi->tm_min = minute;
			auxi->tm_mday = day;
			aux.fechaC = mktime(auxi);
			cout << "Ingrese la obra social del paciente: " << endl;
			cin >> aux.obrasocial;
			cout << "Ingrese el nombre del medico: " << endl;
			cin >> aux.nombreMed;
			cout << "Ingrese el apellido del medico: " << endl;
			cin >> aux.apellidoMed;
			cout << "Ingrese el numero del medico: " << endl;
			cin >> aux.numMed;
			cout << "Ingrese el mail del medico: " << endl;
			cin >> aux.mailMed;

			AgregarConsulta(consultas, aux, &tamC, codes, code);//guardamos consultas para ingresarlas al archivo luego

			system("pause>nul"); // Pausa
			break;

		case 2:
			// Lista de instrucciones de la opción 2                
			for (i = 0; i < tamv; i++)
			{
				if (code == vigentes[i].codigo) {
					aux2 = vigentes[i];
					agregarPaciente(archivados, aux2, &tama);
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
				if (code == vigentes[i].codigo) {
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

	Consultas(consultas, tamC, nombrecons, codes);
	delete[]consultas;

	eliminarVigente(vigentes, &tamv, cont2);

}

void pendiente(Paciente*& pendientes, int tamp) {
	char c = ',';
	fstream fp;
	fp.open("Pendientes.csv", ios::out);
	if (!(fp.is_open()))
		return;

	fp << "Codigo, Nombre, Apellido, Telefono, Mail, Pais, Ciudad, Calle, Direccion, Piso , Departamento" << endl; // le escribo el header

	for (int i = 0; i < tamp; i++) {
		fp << pendientes[i].codigo << c << pendientes[i].nombre << c << pendientes[i].apellido << c << pendientes[i].con.telefono << c << pendientes[i].con.mail
			<< c << pendientes[i].con.pais << c << pendientes[i].con.ciudad << c << pendientes[i].con.calle << c << pendientes[i].con.numDireccion << c <<
			pendientes[i].con.piso << c << pendientes[i].con.depto << endl;
	}
	fp.close();
}

void AgregarConsulta(UltimaConsulta*& consultas, UltimaConsulta aux, int* tam, int*& codes, int code)
{
	*tam = *tam + 1;
	int i = 0;
	UltimaConsulta* aux1 = new UltimaConsulta[*tam];
	int* aux3 = new int[*tam];
	int* aux2 = new int[*tam];
	while (i < *tam - 1 && *tam - 1 != 0) {
		aux1[i] = consultas[i];
		aux3[i] = codes[i];
		i++;
	}
	aux1[i] = aux;
	aux3[i] = code;
	delete[]codes;
	delete[]consultas;
	consultas = aux1;
	codes = aux3;
	return;
}

void Consultas(UltimaConsulta*& consulta, int tamC, string nombre, int*& code)
{
	fstream fp;
	fp.open(nombre, ios::app);
	if (!(fp.is_open()))
		return;
	for (int i = 0; i < tamC; i++)
	{
		fp << code[i] << ',' << consulta[i].fechaC << ',' << consulta[i].motivo << ',' << consulta[i].obrasocial << ',' << consulta[i].nombreMed << ',' <<
			consulta[i].apellidoMed << ',' << consulta[i].numMed << ',' << consulta[i].mailMed << endl;
	}
	fp.close();
}

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