#pragma once
#include "Analisis.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

template <class t_dato>
class Estadistico :
	public Analisis<t_dato>
{
private:
	int P;
	int N;
	int minb;
	int maxb;
	int mini;
	int maxi;
	int mediab;
	int mediai;
public:
	Estadistico();
	~Estadistico();
	void run();
	void imprimir();
};

template <class t_dato>
Estadistico<t_dato>::Estadistico()
{
	minb = 9999999;
	maxb = -1;
	mini = 9999999;
	maxi = -1;
}

template <class t_dato>
Estadistico<t_dato>::~Estadistico()
{
}

template <class t_dato>
void Estadistico<t_dato>::run(){
	t_dato dummy;
	vector <t_dato> banco;
	vector <t_dato> bancoi;
	arbol_ = new ArbolAVL<t_dato>;
	int aux = 0;
	

	cout << "Introduzca el numero de nodos que desea que tenga el arbol: " << endl;
	cin >> N;
	cout << "Introduzca el numero de pruebas a realizar: " << endl;
	cin >> P;

	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		dummy.valor() = ((double)rand() / (double)RAND_MAX)*1000.0;
		banco.push_back(dummy);
		arbol_->Insertar(banco[i]);
		if (!arbol_->Balanceado()){
			cout << "OJITOOOOO" << endl;//****************
			for (int j = 0; j <= i; j++)
				cout << banco[j] << " ";
			cout << endl;
			arbol_->imprimir();

		}
	}

	t_dato::contador() = 0;

	for (int i = 0; i < P; i++){
		arbol_->Buscar(banco[i % N]);								//Por si hay mas pruebas q elementos
		if (t_dato::contador() - aux < minb)
			minb = t_dato::contador() - aux;
		if (t_dato::contador() - aux > maxb)
			maxb = t_dato::contador() - aux;
		aux = t_dato::contador();
	}

	for (int i = 0; i < P; i++) {
		dummy.valor() = ((double)rand() / (double)RAND_MAX)*1000.0;
		bancoi.push_back(dummy);
	}

	mediab = t_dato::contador() / P;

	t_dato::contador() = 0;
	aux = 0;
	for (int i = 0; i < P; i++){
		arbol_->Buscar(bancoi[i]);
		if (t_dato::contador() - aux < mini)
			mini = t_dato::contador() - aux;
		if (t_dato::contador() - aux > maxi)
			maxi = t_dato::contador() - aux;
		aux = t_dato::contador();
	}

	mediai = t_dato::contador() / P;

	imprimir();

}

template <class t_dato>
void Estadistico<t_dato>::imprimir() {

	cout << "\t\tN\tP\tMinimo\tMedio\tMaximo" << endl;
	cout << "Busqueda\t" << N << "\t" << P << "\t" << minb << "\t" << mediab << "\t" << maxb << endl;
	cout << "Insercion\t" << N << "\t" << P << "\t" << mini << "\t" << mediai << "\t" << maxi << endl;




}