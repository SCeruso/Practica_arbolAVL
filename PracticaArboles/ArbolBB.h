#pragma once
#include "ArbolB.h"

template <class t_dato>
class ArbolBB :
	public ArbolB <t_dato>
{
private:
	void CrearBalanceado(vector<t_dato>&, int, int);
	nodo_t<t_dato>* BuscarRama(nodo_t<t_dato>*, t_dato);
	void InsertarRama(nodo_t<t_dato>* &, t_dato);
	void EliminarRama(nodo_t<t_dato>* &, t_dato);
public:
	ArbolBB();
	ArbolBB(ArbolBB<t_dato>&);
	~ArbolBB();
	nodo_t<t_dato>* Buscar(t_dato);
	virtual void Insertar(t_dato);
	virtual void Eliminar(t_dato);
	bool Balanceado();
	bool BalanceRama(nodo_t<t_dato>*);
};

template <class t_dato>
ArbolBB<t_dato>::ArbolBB() : ArbolB<t_dato>() {}

template <class t_dato>
ArbolBB<t_dato>::ArbolBB(ArbolBB<t_dato>& arbol){

	vector <t_dato> v;

	arbol.Inorden(arbol.get_raiz(), v);

	CrearBalanceado(v, 0, v.size() - 1);
}
template <class t_dato>
void ArbolBB<t_dato>::CrearBalanceado(vector<t_dato>& v, int iz, int der){

	int mid = (der + 1 - iz) / 2 + iz;

	Insertar(v[mid]);
	if (iz != der) {
		if (mid > iz)
			CrearBalanceado(v, iz, mid - 1);
		if (mid < der)
			CrearBalanceado(v, mid + 1, der);
	}
}
template <class t_dato>
ArbolBB<t_dato>::~ArbolBB() {}

template <class t_dato>
nodo_t<t_dato>* ArbolBB<t_dato>::Buscar(t_dato dato) {
	return BuscarRama(get_raiz(), dato);
}

template <class t_dato>
nodo_t<t_dato>* ArbolBB<t_dato>::BuscarRama(nodo_t<t_dato>* nodo, t_dato dato){
	if (nodo == NULL)
		return NULL;
	if (nodo->dato_ == dato)
		return nodo;
	if (nodo->dato_ > dato)
		return BuscarRama(nodo->izq_, dato);
	else
		return BuscarRama(nodo->der_, dato);
}

template <class t_dato>
void ArbolBB<t_dato>::Insertar(t_dato dato){
	if (Buscar(dato) == NULL)							//Para evitar que se inserten valores repetidos
		InsertarRama(get_raiz(), dato);
}

template <class t_dato>
void ArbolBB<t_dato>::InsertarRama(nodo_t<t_dato>* &nodo, t_dato dato){
	if (nodo == NULL)
		nodo = new nodo_t<t_dato>(dato);
	else {
		if (nodo->dato_ > dato)
			return InsertarRama(nodo->izq_, dato);
		else
			return InsertarRama(nodo->der_, dato);
	}
}

template <class t_dato>
void ArbolBB<t_dato>::Eliminar(t_dato dato){
	if (Buscar(dato) == NULL){
		cerr << "El dato no está en el árbol" << endl;
		return;
	}
	EliminarRama(get_raiz(), dato);
}

template <class t_dato>
void ArbolBB<t_dato>::EliminarRama(nodo_t<t_dato>* &nodo, t_dato dato){

	if (nodo == NULL)
		return;
	if (nodo->dato_ > dato)
		EliminarRama(nodo->izq_, dato);
	else if (nodo->dato_ < dato)
		EliminarRama(nodo->der_, dato);
	else {
		nodo_t<t_dato>* eliminado = nodo;
		if (nodo->der_ == NULL) {
			nodo = nodo->izq_;
			delete eliminado;
		}
		else if (nodo->izq_ == NULL) {
			nodo = nodo->der_;
			delete eliminado;
		}
		else{
			nodo_t<t_dato>* aux = nodo->izq_;
			while (aux->der_ != NULL)
				aux = aux->der_;
			eliminado->dato_ = aux->dato_;
			EliminarRama(nodo->izq_, aux->dato_);
		}
	}
}

template <class t_dato>
bool  ArbolBB<t_dato>::Balanceado(){
	return BalanceRama(get_raiz());
}

template <class t_dato>
bool  ArbolBB<t_dato>::BalanceRama(nodo_t<t_dato>* nodo){

	if (nodo == NULL)
		return true;
	int balance = AltRama(nodo->izq_) - AltRama(nodo->der_);
	switch (balance) {
	case -1:
	case 0:
	case 1:
		return BalanceRama(nodo->izq_) && BalanceRama(nodo->der_);
	default: return false;
	}
}