#pragma once
#include "Analisis.h"
#include <iostream>

using namespace std;

template <class t_dato>
class Demostracion :
	public Analisis<t_dato>
{
public:
	Demostracion();
	~Demostracion();
	void run();
};

template <class t_dato>
Demostracion<t_dato>::Demostracion()
{
}

template <class t_dato>
Demostracion<t_dato>::~Demostracion()
{
}

template <class t_dato>
void Demostracion<t_dato>::run() {
	int op = -1;
	double clave;
	arbol_ = new ArbolAVL<t_dato>;

	while (op != 0) {
		switch (op) {
		case 1: cout << "Introduzca la clave a insertar" << endl;
			cin >> clave;
			arbol_->Insertar(clave);
			break;
		case 2:	cout << "Introduzca la clave a eliminar" << endl;
			cin >> clave;
			arbol_->Eliminar(clave);
			break;
		default: break;
		}

		arbol_->imprimir();

		cout << "[0] Salir" << endl;
		cout << "[1] Insertar clave" << endl;
		cout << "[2] Eliminar clave" << endl;
		cin >> op;
	}
}