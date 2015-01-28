#pragma once
#include "Nodo.h"
#include <vector>
#include <math.h>

template <class t_dato>
class ArbolB
{

private:
	nodo_t <t_dato>* raiz_;
public:
	ArbolB();
	~ArbolB();
	nodo_t<t_dato>* & get_raiz(void);
	void podar(nodo_t<t_dato>* &);
	bool empty(nodo_t<t_dato>*);
	bool isLeaf(nodo_t<t_dato>*);
	int Tam();
	int TamRama(nodo_t<t_dato>*);
	int Alt();
	int AltRama(nodo_t<t_dato>*);
	void Preorden(nodo_t<t_dato>*, vector<t_dato>&);
	void Inorden(nodo_t<t_dato>*, vector<t_dato>&);
	void Postorden(nodo_t<t_dato>*, vector<t_dato>&);
	void Procesa(t_dato&);
	void Procesa(t_dato&, vector<t_dato>&);
	void imprimir();
	void expansion(nodo_t<t_dato>*, vector<t_dato>&, vector<int>&, int, int);
};

template <class t_dato>
ArbolB<t_dato>::ArbolB(void) :raiz_(NULL){}

template <class t_dato>
ArbolB<t_dato>::~ArbolB(void){
	podar(raiz_);
}

template <class t_dato>
nodo_t<t_dato>* & ArbolB<t_dato>::get_raiz(void) { return raiz_; }

template <class t_dato>
void ArbolB<t_dato>::podar(nodo_t<t_dato>* &nodo) {
	if (nodo == NULL)
		return;
	podar(nodo->izq_);
	podar(nodo->der_);
	delete nodo;
	nodo = NULL;
}
template <class t_dato>
bool ArbolB<t_dato>::empty(nodo_t<t_dato>* nodo) { return nodo == NULL; }

template <class t_dato>
bool ArbolB<t_dato>::isLeaf(nodo_t<t_dato>* nodo) { return ((nodo->der_ == NULL) && (nodo->izq_ == NULL)); }

template <class t_dato>
int ArbolB<t_dato>::Tam(){
	return TamRama(raiz_);
}
template <class t_dato>
int ArbolB<t_dato>::TamRama(nodo_t<t_dato>* nodo){
	if (nodo == NULL)
		return 0;
	return 1 + TamRama(nodo->izq_) + TamRama(nodo->der_);
}
template <class t_dato>
int ArbolB<t_dato>::Alt(){
	return AltRama(raiz_);
}
template <class t_dato>
int ArbolB<t_dato>::AltRama(nodo_t<t_dato>* nodo){

	if (nodo == NULL)
		return 0;
	int alt_i = AltRama(nodo->izq_);
	int alt_d = AltRama(nodo->der_);

	if (alt_d > alt_i)
		return ++alt_d;
	else
		return ++alt_i;
}

template <class t_dato>
void ArbolB<t_dato>::Preorden(nodo_t<t_dato>* nodo, vector<t_dato>& v){
	if (nodo == NULL)
		return;
	Procesa(nodo->dato_, v);
	Preorden(nodo->izq_, v);
	Preorden(nodo->der_, v);
}
template <class t_dato>
void ArbolB<t_dato>::Inorden(nodo_t<t_dato>* nodo, vector<t_dato>& v){
	if (nodo == NULL)
		return;
	Inorden(nodo->izq_, v);
	Procesa(nodo->dato_, v);
	Inorden(nodo->der_, v);
}
template <class t_dato>
void ArbolB<t_dato>::Postorden(nodo_t<t_dato>* nodo, vector<t_dato>& v){
	if (nodo == NULL)
		return;
	Postorden(nodo->izq_, v);
	Postorden(nodo->der_, v);
	Procesa(nodo->dato_, v);
}
template <class t_dato>
void ArbolB<t_dato>::Procesa(t_dato& dato) {
	cout << dato << " ";
}
template <class t_dato>
void ArbolB<t_dato>::Procesa(t_dato& dato, vector<t_dato>& v) { v.push_back(dato); }

template <class t_dato>
void ArbolB<t_dato>::imprimir() {
	vector<t_dato> v;
	vector<int> nnodos;
	int k = 0;
	int cap = Alt();
	t_dato e(EMPTY);
	//**************************
	nnodos.resize(cap, 0);

	for (int i = 0; i < cap; i++)
		expansion(raiz_, v, nnodos, 0, i);

	for (int i = 0; i < cap; i++){
		cout << "Nivel " << i << ": ";
		for (int j = 0; j < nnodos[i]; j++){
			if (v[k] != e){
				cout << "[" << v[k] << "] ";
				k++;
			}
			else{
				cout << "[.] ";
				k++;
			}
		}
		cout << endl;
	}
}
template <class t_dato>
void ArbolB<t_dato>::expansion(nodo_t<t_dato>* nodo, vector<t_dato>& v, vector<int>& nnodos, int inx, int cap){

	if (inx == cap){
		if (nodo == NULL)
			v.push_back(EMPTY);
		else
			Procesa(nodo->dato_, v);
		nnodos[cap]++;
	}
	else if (nodo != NULL){
		inx++;
		expansion(nodo->izq_, v, nnodos, inx, cap);
		expansion(nodo->der_, v, nnodos, inx, cap);
	}
}