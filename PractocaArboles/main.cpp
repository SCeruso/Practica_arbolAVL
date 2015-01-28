#include <iostream>
#include "ArbolBB.h"
#include"Tdato.h"
#include "Demostracion.h"
#include "Estadistico.h"
#include "ArbolAVL.h"

int tester::cont_ = 0;
double tester::p_ = 0.001;

int main(void) {
	Analisis<tester>* analisis;
	int op = -1;

	cout << "Elija un modo de ejecución: " << endl;
	cout << "[0] Demostracion" << endl;
	cout << "[1] Estadistico" << endl;

	cin >> op;
	if (op == 0) {
		analisis = new Demostracion<tester>;
		analisis->run();
	}
	if (op == 1){
		analisis = new Estadistico<tester>;
		analisis->run();
	}
	system("pause");
}