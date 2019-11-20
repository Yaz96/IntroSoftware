#pragma once
#include<iostream> 
#include <string> 
#include "General.h"
#include <sys/types.h>

#if defined(_WIN32)
#include "dirent.h"
#elif defined(_WIN64)
#include "dirent.h"
#elif defined(__linux__)
#include <dirent.h>
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
#include <dirent.h>
#endif
#include <vector>
#include <ctime>
typedef std::vector<std::string> stringvec;
using namespace std;


time_t now = time(0);


void limpiarTerminal();
bool validacionFecha(string fileHandler) { // Valida que las fechas del archivo que se paso sea despues de la fecha actual

	tm *ltm = localtime(&now);

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
	
	if (year < (1900 + ltm->tm_year)) {
		if (month < (1 + ltm->tm_mon)) {
			if (day < ltm->tm_mday) {
			
				if ((timeH*60+ timem) < ((1 + ltm->tm_hour)*60+(1 + ltm->tm_min)) ) {
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

}

void tareasAlumno(string materia) {
	const std::string& name = "./Tareas/" + materia;
	stringvec v;
#if defined(_WIN32)|| defined(_WIN64)
	

	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	string aux;
	while ((dp = readdir(dirp)) != NULL) {
		aux = dp->d_name;
		if (aux != "." && aux != "..")
			v.push_back(dp->d_name);
	}
	closedir(dirp);
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
	string dir; 
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(name.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
}

	while ((dirp = readdir(dp)) != NULL) {
		v.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;



#endif
	
	limpiarTerminal();
	for (int i = 0; i < v.size(); i++) {
		cout << to_string(i) + ".-" << v[i] << endl;
	}

	int tarea;

	cin >> tarea;
///////////////////////////////////
	
	validacionFecha("./Tareas/" + materia+"/"+ v[tarea]);


		cout << "\n0.- subir tarea" << "\n1.- regresar" << endl;
}

void quizzesAlumno() {

}
void quizzesProfesor() {

}
void forosAlumno() {

}
void forosProfesor() {

}


void limpiarTerminal() {
#if defined(_WIN32)
	system("cls");
#elif defined(_WIN64)
	system("cls");
#elif defined(__linux__)
	system("clear");
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
	system("clear");
#endif


}

