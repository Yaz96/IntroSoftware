#pragma once
#include<iostream> 
#include <string> 
#include "General.h"
#include <sys/types.h>

#if defined(_WIN32)
#include "dirent.h"
#include <direct.h>
#define cwd _getcwd
#define cd _chdir
#elif defined(_WIN64)
#include "dirent.h"
#elif defined(__linux__)
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#include <dirent.h>
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#include <dirent.h>
#endif
#include <vector>
#include <ctime>
typedef std::vector<std::string> stringvec;
using namespace std;


time_t now = time(0);

tm *ltm = localtime(&now);
void limpiarTerminal();
bool validacionFecha(string fileHandler) { // Valida que las fechas del archivo que se paso sea despues de la fecha actual

	

	/*cout << "Year" << 1900 + ltm->tm_year << endl;
	cout << "Month: " << 1 + ltm->tm_mon << endl;
	cout << "Day: " << ltm->tm_mday << endl;
	cout << "Time: " << 1 + ltm->tm_hour << ":";
	cout << 1 + ltm->tm_min << ":";
	cout << 1 + ltm->tm_sec << endl;
	*/

	///////////////////////// Validacion de la fecha
	string cadena;

	ifstream fe(fileHandler);

		getline(fe, cadena);
	
	int day=stoi(cadena.substr(1, 2)),month= stoi(cadena.substr(4, 5)),year= stoi("20"+cadena.substr(7, 8)),timeH= stoi(cadena.substr(10, 11)),timem= stoi(cadena.substr(13, 14));

	fe.close();
	int yearAx = 1900 + ltm->tm_year;
	
	if (year >= (yearAx)) {
		if (month >= (1 + ltm->tm_mon)) {
			if (day >= ltm->tm_mday) {
			
				if ((timeH*60+ timem) >= ((1 + ltm->tm_hour)*60+(1 + ltm->tm_min)) ) {
					return true;
				
				}
			}
		}
	}
	return false;
	
}

User iniSesion(string usuario, string pwd) {

	User u;
	bool loggeado = u.login(usuario, pwd);

	if (loggeado) {
		cout << "Bienvenido " << usuario << endl;
		int priv = u.getPriv(usuario);

		if (priv) {
			cout << "Usted tiene privilegios de Administrador" << endl;
		}
		else {
			cout << "Usted inicio sesion como Alumno" << endl;
		}
	}
	else {
		cout << "Error en usuario/contraseña" << endl;
	}



	return u;


}

void tareasProfesor(string materia) {
	int iAccion;
	string sNombre, sDescripcion, aux;
	ifstream iEntrada;

	cout << "1.Ver tareas" << endl;
	cout << "2. Crear tarea" << endl;
	cin >> iAccion;

	if (iAccion == 1) {
		const std::string& name = "./Tareas/" + materia;
		stringvec v;
		DIR* dirp = opendir(name.c_str());
		struct dirent * dp;
		string aux;
		while ((dp = readdir(dirp)) != NULL) {
			aux = dp->d_name;
			if (aux != "." && aux != "..")
				v.push_back(dp->d_name);
		}
		closedir(dirp);

		for (int i = 0; i < v.size(); i++) {
			cout << to_string(i) + ".-" << v[i] << endl;
		}

	}
	else {
		ofstream ofSalida;
		cout << "Ingresa el nombre de la tarea" << endl;
		cin >> sNombre;
		sNombre = "Tareas/" + materia +"/"+ sNombre + ".txt";
		ofSalida.open(sNombre);

		cout << "Ingresa la fecha limite con el formato D##M##A##H##m## " << endl;
		cin >> aux;
		cout << "Ingresa la descripcion" << endl;
		cin.ignore();
		getline(cin, sDescripcion);
		
		ofSalida << aux +"\n"+ sDescripcion;
		ofSalida .close();
	}
}

void tareasAlumno(string materia,string loggedActual) {
	const std::string& name = "./Tareas/" + materia;
	stringvec v;
	

	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	string aux;
	while ((dp = readdir(dirp)) != NULL) {
		aux = dp->d_name;
		if (aux != "." && aux != ".." && aux.substr(0,3) != "Res")
			v.push_back(dp->d_name);
	}
	closedir(dirp);

	
	limpiarTerminal();
	for (int i = 0; i < v.size(); i++) {
		cout << to_string(i) + ".-" << v[i] << endl;
	}

	string tarea1;
	cout << "r para gregresar" << endl;

	cin >> tarea1;
///////////////////////////////////
	if (tarea1 != "r") {
		int tarea = stoi(tarea1);
		string cadena;
		if (validacionFecha("./Tareas/" + materia + "/" + v[tarea])) {
			ifstream fe("./Tareas/" + materia + "/" + v[tarea]);

			getline(fe, cadena);
			//cout << "\n" + cadena + "\n" << endl;
			cout << "\nDescripcion:\n" << "Fecha de entrega:" + cadena.substr(1, 2) + "/" + cadena.substr(4, 2) + "  " + cadena.substr(10, 2) + ":" + cadena.substr(13, 2) << endl;
			while (!fe.eof()) {
				getline(fe, cadena);
				cout << cadena << endl;
			}

			cout << "\n0.- Subir Tarea\n1.-Regresar" << endl;
			fe.close();
			int menu;
			cin >> menu;
			if (menu == 0) { // Subir tarea
				ofstream myfile;
				myfile.open("./Tareas/" + materia + "/" + "Resp" + v[tarea]);
				string aux = (loggedActual + to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + " " + to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + "\n");
				myfile << aux;
				myfile.close();

			}
		}
		else {
			cout << "La tarea ya excedio su tiempo para subirla" << endl;
			cout << "\n0.-Regresar" << endl;
			cin >> tarea;
			///////////////////////regresar
		}


	}
	else {
		limpiarTerminal();
		
	}



}

void quizzesAlumno(string materia, string loggedActual) {
	const std::string& name = "./Quizzes/" + materia;
	stringvec v;
	string respuestas,aux1,aux2;
	int cont,contglobal;


	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	string aux;
	while ((dp = readdir(dirp)) != NULL) {
		aux = dp->d_name;
		if (aux != "." && aux != ".." && aux.substr(0, 3) != "Res"&& aux !="Provicional.txt" && aux != "Calificaciones.txt")
			v.push_back(dp->d_name);
	}
	closedir(dirp);


	limpiarTerminal();
	for (int i = 0; i < v.size(); i++) {
		cout << to_string(i) + ".-" << v[i] << endl;
	}

	int quizz;
	string quizzx;
	cout << "\nr.-Regresar" << endl;
	cin >> quizzx;

	
	if (quizzx != "r") {
		quizz = stoi(quizzx);
		string cadena;
		if (validacionFecha("./Quizzes/" + materia + "/" + v[quizz])) {
			ifstream fe("./Quizzes/" + materia + "/" + v[quizz]);

			getline(fe, cadena);
			//cout << "\n" + cadena + "\n" << endl;
			cout << "Fecha de entrega:" + cadena.substr(1, 2) + "/" + cadena.substr(4, 2) + "  " + cadena.substr(10, 2) + ":" + cadena.substr(13, 2) << "\nPreguntas: \n" << endl;
			while (!fe.eof()) {
				getline(fe, cadena);
				cout << cadena << endl;
			}
			fe.close();
			int menu;
		
				cout << "\n0.- Responder Quizz\n1.-Regresar\n" << endl;
				cin >> menu;
			
			if (menu == 0) { // responderquizz tarea
				cout << "\nComienza a responder las preguntas presionando enter para cada pregunta, si terminas envia z\n" << endl;
				ofstream myfile;
				myfile.open("./Quizzes/" + materia + "/" + "Provicional.txt");
				cin.ignore();
				getline(cin, respuestas);
				while (respuestas != "z") {
					myfile << respuestas + "\n";
					getline(cin, respuestas);
				}
				myfile.close();

				/// revisar el quizz

				ifstream alumno("./Quizzes/" + materia + "/" + "Provicional.txt");
				string auxc = "./Quizzes/" + materia + "/" + "Resp" + v[quizz];
				ifstream Respuestas(auxc);
				cont = 0;
				contglobal = 0;
				while (!Respuestas.eof()) {
					getline(Respuestas, aux1);
					getline(alumno, aux2);
					if (aux1 == aux2)
						cont++;
					contglobal++;
				}
				cont--;
				contglobal--;
				cont = cont * 100 / contglobal;

				limpiarTerminal();
				cout << "Tu calificacion es:  " + to_string(cont) + "/100\nPresiona enter para volver\n" << endl;

				myfile.open("./Quizzes/" + materia + "/" + "Calificaciones.txt");
				myfile << loggedActual + "grade = " + to_string(cont);
				myfile.close();
				cin >> aux1;
			}
			else {
				limpiarTerminal();
			}

		}
		else {
			cout << "La tarea ya excedio su tiempo para subirla" << endl;
			cout << "\n0.-Regresar" << endl;
			cin >> quizz;

		}
	}
	else {
		limpiarTerminal();
	}
	///////// regresar




}
void quizzesProfesor(string materia) {
	int iAccion;
	string sNombre, sDescripcion,aux;

	cout << "1.Ver quizzes" << endl;
	cout << "2.Crear quizz" << endl;
	cin >> iAccion;

	if (iAccion == 1) {
		limpiarTerminal();

		const std::string& name = "./Quizzes/" + materia;
		stringvec v;
		DIR* dirp = opendir(name.c_str());
		struct dirent * dp;
		string aux;
		while ((dp = readdir(dirp)) != NULL) {
			aux = dp->d_name;
			if (aux != "." && aux != ".." && aux !="Provicional.txt")
				v.push_back(dp->d_name);
		}
		closedir(dirp);

		for (int i = 0; i < v.size(); i++) {
			cout << to_string(i) + ".-" << v[i] << endl;
		}

		int quizz;
		string quizzx;
		cout << "\nr.-Regresar" << endl;
		cin >> quizzx;

		if (quizzx != "r") {
			quizz = stoi(quizzx);
			string cadena;
			
				ifstream fe("./Quizzes/" + materia + "/" + v[quizz]);

				getline(fe, cadena);
				//cout << "\n" + cadena + "\n" << endl;
				//cout << "Fecha de entrega:" + cadena.substr(1, 2) + "/" + cadena.substr(4, 2) + "  " + cadena.substr(10, 2) + ":" + cadena.substr(13, 2) << "\nPreguntas: \n" << endl;
				while (!fe.eof()) {
					getline(fe, cadena);
					cout << cadena << endl;
				}
				fe.close();
				int menu;
				string men;
				cout << "\nr.-Regresar\n" << endl;
				cin >> men;
				
			}


	}
	else if (iAccion==2) {
		ofstream ofSalida;
		cout << "Ingresa el nombre del quizz." << endl;
		cin >> sNombre;
		ofSalida.open("Quizzes/" + materia + "/" + sNombre + ".txt");
		cout << "Ingresa la fecha limite con el formato D##M##A##H##m## " << endl;
		cin >> aux;
		ofSalida << aux + "\n";
		cin.ignore();
		cout << "Ingresa las preguntas con sus posibles respuestas. (Sal del modo de escritura escribiendo z)" << endl;
		getline(cin, sDescripcion);
		while (sDescripcion != "z") {
			ofSalida << sDescripcion+"\n";
			//cin.ignore();
			getline(cin, sDescripcion);
			}
	
		ofSalida.close();
		ofSalida.open("Quizzes/" + materia + "/" + "Resp" + sNombre + ".txt");
		cout << "Ingresa las respuestas del quizz. (Sal del modo de escritura escribiendo z)" << endl;
		getline(cin, sDescripcion);
		while (sDescripcion != "z") {
			ofSalida << sDescripcion + "\n";
			getline(cin, sDescripcion);
		}
		ofSalida.close();

	}

}
void forosAlumno(string materia, string loggedActual) {

	ifstream ifEntrada;
	ofstream ofSalida;
	string sMensaje, sMensaje2;
	int iForo;

	const std::string& name = "./Foros/" + materia;
	stringvec v;
	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	string aux;
	while ((dp = readdir(dirp)) != NULL) {
		aux = dp->d_name;
		if (aux != "." && aux != "..")
			v.push_back(dp->d_name);
	}
	closedir(dirp);

	limpiarTerminal();
	for (int i = 0; i < v.size(); i++) {
		cout << to_string(i) + ".-" << v[i] << endl;
	}
	if (v.size() != 0) {
		cout << "Cual desas abrir?" << endl;

	

	cin >> iForo;
	ifEntrada.open("Foros/" + materia + "/" + v[iForo]);
	cin.ignore();
	while (!ifEntrada.eof()) {

		getline(ifEntrada, sMensaje);
		cout << sMensaje << endl;
	}
	ofSalida.open("Foros/" + materia + "/" + v[iForo], ofstream::app);
	cout << "Escribe tu mensaje" << endl;
	getline(cin, sMensaje2);

	ofSalida << endl << loggedActual+": "+sMensaje2;
	}


}
void forosProfesor(string materia) {
	ifstream ifEntrada;                           ////////
	ofstream ofSalida;
	string sMensaje, sMensaje2, sNombre, sDescripcion;
	int iForo, iAccion;

	const std::string& name = "./Foros/" + materia;  
	stringvec v;
	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	string aux;
	while ((dp = readdir(dirp)) != NULL) {
		aux = dp->d_name;
		if (aux != "." && aux != "..")
			v.push_back(dp->d_name);
	}
	closedir(dirp);									////// esta parte lee y despliega los archivos en una carpeta



	cout << "1. Ver foros" << endl;
	cout << "2. Crear nuevo foro" << endl;
	cin >> iAccion;

	if (iAccion == 1) {
		limpiarTerminal();
		for (int i = 0; i < v.size(); i++) {
			cout << to_string(i) + ".-" << v[i] << endl;
		}
		cout << "Cual desas abrir?" << endl;
		cin >> iForo;
		ifEntrada.open("Foros/"+materia+"/"+v[iForo]);
		cin.ignore();
		while (!ifEntrada.eof()) {

			getline(ifEntrada, sMensaje);
			cout << sMensaje << endl;
		}
		ofSalida.open("Foros/" + materia + "/" + v[iForo], ofstream::app); // este codigo modifica y agrega texto a un doc
		cout << "Escribe tu mensaje" << endl;
		getline(cin, sMensaje2);

		ofSalida << "Profesor: " << endl << sMensaje2;
		ifEntrada.close();
		ofSalida.close();
	}
	else {
		cout << "Ingresa el nombre del foro" << endl;
		cin >> sNombre;
		sNombre = "Foros/"+materia+"/"+sNombre + ".txt";
		ofSalida.open(sNombre);
		cout << "Ingresa la descripcion" << endl;
		cin.ignore();
		getline(cin, sDescripcion);
		ofSalida << sDescripcion;
	}

}


void AvisosProfe(string materia) {
	ofstream ofSalida;
	string sMensaje2;
	cout << "0.-modificar los avisos\nr.- regresar" << endl;
	string menu;
	int menui;
		cin >> menu;
	if (menu != "r") {
		menui = stoi(menu);


		//////////aqui debes de tomar el archivo de avisos de esta materia 
		ofSalida.open("avisos/" +materia+ ".txt");
		cout << "Escribe tu Aviso\n" << endl;
		cin.ignore();
		getline(cin, sMensaje2);

		ofSalida <<  sMensaje2;


	}
	else {
		limpiarTerminal();
	}


}


void limpiarTerminal() {
#if defined(_WIN32)
	system("cls");
#elif defined(_WIN64)
	system("cls");
#elif defined(__linux__)
	system("clear");
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
	system("clear");
#endif


}

bool file_exist(char *filename)
{
	struct stat   buffer;
	return (stat(filename, &buffer) == 0);
}