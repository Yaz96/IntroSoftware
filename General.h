#pragma once
#include<iostream> 
#include <string> 
#include <fstream>
#include "FunGen.h"


using namespace std;
void tareasAlumno(string materia, string loggedActual);
void tareasProfesor(string materia);
void quizzesAlumno(string materia, string loggedActual);
void quizzesProfesor(string materia);
void forosAlumno(string materia, string loggedActual);
void forosProfesor(string materia);
void AvisosProfe(string materia);
bool file_exist(char *filename);

class User {
private:
	string users[100] = { "Clemente", "Joaquin", "Adrian" };
	int UserIndex;
	int cantUsuarios = 3;
	string passwd[100] = { "1234","2345","3456" };
	int priv[100] = { 0,1,0 }; // 0 significa alumno y 1 profesor
	bool u = false, p = false;
	string Materias[10];


public:
	bool logged = false;
	string loggedActual = "ninguno";
	int i;

	int Imprimir(char Imprime, int numMateria=0) {
		int i;
		string cadena;

		
		switch (Imprime)
		{
		case 'M':
			for (i = 0; i < 10; i++) {
				if (Materias[i] == "none") {
					return i;
				}
				cout << to_string(i) + ".- " << Materias[i] << endl;
			}
			

			break;
		case 'I':
			if (numMateria!=-1) {
				cout << "Avisos!" << endl;
				string materia = "avisos/" + Materias[numMateria] + ".txt";
				char* mataux = &materia[0];
				if (file_exist(mataux))
				{
					ifstream fe(materia);

					while (!fe.eof()) {
						getline(fe, cadena);
						cout << cadena << endl;
					}
				}
				else {
					cout << "\nNo hay avisos disponibles para desplegar\n" << endl;
				}

				cout << "\n0.- Tareas\n" << "1.- Quizzes\n" << "2.- Foros de Discusion" <<  endl;
				if (priv[this->UserIndex] == 1) {
					cout << "3.- Avisos" << endl;
				}
				cout << "r.- Regresar\n" << endl;
			}
			break;
	
		}




	}

	void MenuMaterias(int menu, int materia) {
		if (menu != -1) {
			switch (menu) {
			case 0:
				if (!priv[this->UserIndex]) { //si es alumno lo mandara a una funcion especial para el alumno en las tareas
					tareasAlumno(Materias[materia], this->loggedActual);

				}
				else {
					tareasProfesor(Materias[materia]); // si es profesor lo mandara a una funcion especial para el profesor para las tareas
				}
				break;
			case 1:
				if (!priv[this->UserIndex]) {

					quizzesAlumno(Materias[materia], this->loggedActual);

				}
				else {
					quizzesProfesor(Materias[materia]);
				}

				break;
			case 2:
				if (!priv[this->UserIndex]) {

					forosAlumno(Materias[materia], this->loggedActual);

				}
				else {
					forosProfesor(Materias[materia]);
				}
				break;
			case 3:

				if (priv[this->UserIndex]) {

					AvisosProfe(Materias[materia]);
				}


				break;

			}
		}

	}


	bool login(string usr, string psw) {
		for (i = 0; i < cantUsuarios; i++) {
			if (usr == users[i]) {
				u = true;
				UserIndex = i;
				break;
			}
		}

		if (psw == passwd[i]) {
			p = true;
		}

		if (u && p) {
			logged = true;
			loggedActual = usr;
			//Carga de materias
			string cadena;

			ifstream fe("Materias.txt");
			getline(fe, cadena);;
			while (cadena != usr) {
				getline(fe, cadena);;
		}
			
			for(int i = 0; i<10;i++){
				getline(fe, cadena);
				Materias[i] = cadena;
			}
			fe.close();

		}

		return logged;
	}

	bool getPriv(string usr) {
		for (i = 0; i < cantUsuarios; i++) {
			if (usr == users[i])
				break;
		}

		if (priv[i] == 1)
			return true;

		return false;
	}
};

