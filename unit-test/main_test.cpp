#include "gmock/gmock.h"
#include "funciones.h"

namespace foobar::tests {
	TEST(ExampleTests, Example) {
        ASSERT_THAT(1, 1);
	}
}
namespace CasosBase {
	TEST(CasosBase, AgregarPaciente)
	{
		int N = 2;
		Paciente* ejemplo = new Paciente[N];

		ejemplo[0].dni = 45238330;
		ejemplo[0].nombre = "Juan";
		ejemplo[0].apellido = "Guaglianone";
		ejemplo[0].obra_social = "osde";
		ejemplo[0].genero = 'm';
		ejemplo[0].con.dni = 45238330;
		ejemplo[0].con.mail = "juanpiguaglianone@gmail.com";
		ejemplo[0].con.celular = " + 54(147)34982983";
		ejemplo[0].con.telefono = "+ 54(974)82014567";
		ejemplo[0].con.direccion = "Bouchard";
		ejemplo[0].consulta.dni = 45238330;
		ejemplo[0].consulta.fecha_solicitado = "5/12/2022";
		ejemplo[0].consulta.fechaturno = 1245365257;
		ejemplo[0].consulta.presencialidad = 0;
		ejemplo[0].consulta.matricula_med = "11-089-2367";
		ejemplo[0].nac = "12/2/1970";
		ejemplo[0].estado = "internado";

		ejemplo[1].dni = 43892783;
		ejemplo[1].nombre = "Maria";
		ejemplo[1].apellido = "Namir";
		ejemplo[1].obra_social = "swiss medical";
		ejemplo[1].genero = 'f';
		ejemplo[1].con.dni = 43892783;
		ejemplo[1].con.mail = "Mnamir@gmail.com";
		ejemplo[1].con.celular = "+ 54(176)68420326";
		ejemplo[1].con.telefono = "+ 54(801)04193744";
		ejemplo[1].con.direccion = "Rosales";
		ejemplo[1].consulta.dni = 43892783;
		ejemplo[1].consulta.fecha_solicitado = "5/12/2022";
		ejemplo[1].consulta.fechaturno = 1565365817;
		ejemplo[1].consulta.presencialidad = 1;
		ejemplo[1].consulta.matricula_med = "87-079-3429";
		ejemplo[1].nac = "7/2/2000";
		ejemplo[1].estado = "fallecido";





		Paciente aux;

		aux.dni = 34982378;
		aux.nombre = "Jesus";
		aux.apellido = "Messi";
		aux.obra_social = "pasteur";
		aux.genero = 'm';
		aux.con.dni = 34982378;
		aux.con.mail = "MessiJ@gmail.com";
		aux.con.celular = " + 54(345)56489374)";
		aux.con.telefono = " + 54(262)26039091";
		aux.con.direccion = "Mitre";
		aux.consulta.dni = 34982378;
		aux.consulta.fecha_solicitado = "05/12/2022";
		aux.consulta.fechaturno = 1490365817;
		aux.consulta.presencialidad = 1;
		aux.consulta.matricula_med = "90-092-5729";
		aux.nac = "25/10/2003";
		aux.estado = "n/c";


		agregarPaciente(ejemplo, aux, &N);

		EXPECT_EQ(N, 3);
		EXPECT_EQ(ejemplo[2].dni, aux.dni);
		EXPECT_EQ(ejemplo[2].nombre, aux.nombre);
		EXPECT_EQ(ejemplo[2].apellido, aux.apellido);
		EXPECT_EQ(ejemplo[2].obra_social, aux.obra_social);
		EXPECT_EQ(ejemplo[2].genero, aux.genero);
		EXPECT_EQ(ejemplo[2].con.dni, aux.con.dni);
		EXPECT_EQ(ejemplo[2].con.mail, aux.con.mail);
		EXPECT_EQ(ejemplo[2].con.celular, aux.con.celular);
		EXPECT_EQ(ejemplo[2].con.telefono, aux.con.telefono);
		EXPECT_EQ(ejemplo[2].con.direccion, aux.con.direccion);
		EXPECT_EQ(ejemplo[2].consulta.dni, aux.consulta.dni);
		EXPECT_EQ(ejemplo[2].consulta.fecha_solicitado, aux.consulta.fecha_solicitado);
		EXPECT_EQ(ejemplo[2].consulta.fechaturno, aux.consulta.fechaturno);
		EXPECT_EQ(ejemplo[2].consulta.presencialidad, aux.consulta.presencialidad);
		EXPECT_EQ(ejemplo[2].consulta.matricula_med, aux.consulta.matricula_med);
		EXPECT_EQ(ejemplo[2].nac, aux.nac);
		EXPECT_EQ(ejemplo[2].estado, aux.estado);

		delete[] ejemplo;
	}



	TEST(CasosBase, LeerConsultas)
	{
		int n = 1;
		UltimaConsulta* ejemplo = new UltimaConsulta[n];
		UltimaConsulta aux;

		aux.dni = 43963883;
		aux.fecha_solicitado = "14/05/1987";
		aux.fechaturno = 1470363817;
		aux.presencialidad = 0;
		aux.matricula_med = "11-089-2367";

		ejemplo[0] = aux;
		Consultas(ejemplo, n);

		EXPECT_EQ(ejemplo[0].dni, aux.dni);
		EXPECT_EQ(ejemplo[0].fecha_solicitado, aux.fecha_solicitado);
		EXPECT_EQ(ejemplo[0].fechaturno, aux.fechaturno);
		EXPECT_EQ(ejemplo[0].presencialidad, aux.presencialidad);
		EXPECT_EQ(ejemplo[0].matricula_med, aux.matricula_med);
		delete[] ejemplo;

	}


	TEST(CasosBase, EliminarVigente)
	{
		int N = 3;
		Paciente* array = new Paciente[N];

		array[0].dni = 45238330;
		array[0].nombre = "Juan";
		array[0].apellido = "Guaglianone";
		array[0].obra_social = "osde";
		array[0].genero = 'm';
		array[0].con.dni = 45238330;
		array[0].con.mail = "juanpiguaglianone@gmail.com";
		array[0].con.celular = "+ 54(147)34982983";
		array[0].con.telefono = "+ 54(974)82014567";
		array[0].con.direccion = "Bouchard";
		array[0].consulta.dni = 45238330;
		array[0].consulta.fecha_solicitado = "5/12/2022";
		array[0].consulta.fechaturno = 1356865257;
		array[0].consulta.presencialidad = 0;
		array[0].consulta.matricula_med = "11-089-2367";
		array[0].nac = "23/8/2014";
		array[0].estado = "internado";

		array[1].dni = 43892783;
		array[1].nombre = "Maria";
		array[1].apellido = "Namir";
		array[1].obra_social = "swiss medical";
		array[1].genero = 'f';
		array[1].con.dni = 43892783;
		array[1].con.mail = "Mnamir@gmail.com";
		array[1].con.celular = "+ 54(176)68420326";
		array[1].con.telefono = "+ 54(801)04193744";
		array[1].con.direccion = "Rosales";
		array[1].consulta.dni = 43892783;
		array[1].consulta.fecha_solicitado = "5/12/2022";
		array[1].consulta.fechaturno = 1457865137;
		array[1].consulta.presencialidad = 1;
		array[1].consulta.matricula_med = "87-079-3429";
		array[1].nac = "11/9/2001";
		array[1].estado = "fallecido";

		array[2].dni = 34982378;
		array[2].nombre = "Jesus";
		array[2].apellido = "Messi";
		array[2].obra_social = "pasteur";
		array[2].genero = 'm';
		array[2].con.dni = 34982378;
		array[2].con.mail = "MessiJ@gmail.com";
		array[2].con.celular = "+ 54(345)56489374)";
		array[2].con.telefono = "+ 54(262)26039091";
		array[2].con.direccion = "Mitre";
		array[2].consulta.dni = 34982378;
		array[2].consulta.fecha_solicitado = "05/12/2022";
		array[2].consulta.fechaturno = 1670364535;
		array[2].consulta.presencialidad = 1;
		array[2].consulta.matricula_med = "90-092-5729";
		array[2].nac = "19/5/2018";
		array[2].estado = "n/c";

		int cantEliminar = 2;

		eliminarVigente(array, &N, cantEliminar);



		EXPECT_EQ(N, 1);

		for (int i = 0; i < N; i++) {
			EXPECT_EQ(array[i].dni, array[0].dni);
			EXPECT_EQ(array[i].nombre, array[0].nombre);
			EXPECT_EQ(array[i].apellido, array[0].apellido);
			EXPECT_EQ(array[i].obra_social, array[0].obra_social);
			EXPECT_EQ(array[i].genero, array[0].genero);
			EXPECT_EQ(array[i].con.dni, array[0].con.dni);
			EXPECT_EQ(array[i].con.mail, array[0].con.mail);
			EXPECT_EQ(array[i].con.celular, array[0].con.celular);
			EXPECT_EQ(array[i].con.telefono, array[0].con.telefono);
			EXPECT_EQ(array[i].con.direccion, array[0].con.direccion);
			EXPECT_EQ(array[i].consulta.dni, array[0].consulta.dni);
			EXPECT_EQ(array[i].consulta.fecha_solicitado, array[0].consulta.fecha_solicitado);
			EXPECT_EQ(array[i].consulta.fechaturno, array[0].consulta.fechaturno);
			EXPECT_EQ(array[i].consulta.presencialidad, array[0].consulta.presencialidad);
			EXPECT_EQ(array[i].consulta.matricula_med, array[0].consulta.matricula_med);
			EXPECT_EQ(array[i].nac, array[0].nac);
			EXPECT_EQ(array[i].estado, array[0].estado);
		}
	}
}