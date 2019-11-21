#include<iostream> 
#include <string> 
#include <stdlib.h>
#include "FunGen.h"
using namespace std;

// User iniSesion( string usuario, string psw);
User actual;
char globMenu;
int main()
{



	string usuario;
	string pwd;

	while (actual.logged == false) {
		limpiarTerminal();
		cout << "Bienvenido a BlackBoard\n¿Cual es su usuario?" << endl;
		cin >> usuario;
		cout << "Contraseña: ";
		cin >> pwd;

		actual = iniSesion(usuario, pwd);
	}

	//cout << actual.loggedActual << endl;

	string menu, materia;
	int index;
	do {
		do {
			limpiarTerminal();
			cout << "Materias:\n" << endl;

			index = actual.Imprimir('M'); // Imprime las materias

			cin >> materia;

			limpiarTerminal();
			actual.Imprimir('I', stoi(materia)); // Imprime las opciones de contenido de una materia
		//

			cin >> menu;
			menu = (menu == "r") ? "-1" : menu;
			limpiarTerminal();
		} while (menu == "-1");

		actual.MenuMaterias(stoi(menu), stoi(materia));
	} while (true);

	/*switch (globMenu) :
	{
		case
	
	}*/

	return 0;
}