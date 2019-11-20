#include<iostream> 
#include <string> 
#include <stdlib.h>
#include "FunGen.h"
using namespace std;

// User iniSesion( string usuario, string psw);
User actual;

int main()
{
	


	string usuario;
	string pwd;

	while (actual.logged == false) {
		cout << "Bienvenido a BlackBoard\n¿Cual es su usuario?" << endl;
		cin >> usuario;
		cout << "Contraseña: ";
		cin >> pwd;

		actual = iniSesion(usuario, pwd);
	}

	//cout << actual.loggedActual << endl;

	string menu, materia;
	int index;
	cout << "Materias:\n" << endl;

	index = actual.Imprimir('M'); // Imprime las materias

	cin >> materia;
	limpiarTerminal();
	actual.Imprimir('I', stoi(materia));

	cin >> menu;

	limpiarTerminal();
	
	actual.MenuMaterias(stoi(menu),stoi(materia));




	return 0;
}