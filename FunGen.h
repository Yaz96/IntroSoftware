#pragma once
#include<iostream> 
#include <string> 
#include "General.h"
#include <windows.h>
#include <vector>
typedef std::vector<std::string> stringvec;
using namespace std;


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
	const std::string& name = "./Tareas/"+materia;
	stringvec v;
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		FindNextFile(hFind, &data);
		FindNextFile(hFind, &data);
		do {
			if (data.cFileName != ".") {
				v.push_back(data.cFileName);
			}
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	



}

void quizzesAlumno() {

}
void quizzesProfesor() {

}
void forosAlumno() {

}
void forosProfesor() {

}