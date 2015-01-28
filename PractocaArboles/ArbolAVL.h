#pragma once
#include "ArbolBB.h"

template <class t_dato>
class ArbolAVL :
	public ArbolBB <t_dato>
{
private:
	void RotacionII(nodo_t<t_dato>* &);
	void RotacionID(nodo_t<t_dato>* &);
	void RotacionDI(nodo_t<t_dato>* &);
	void RotacionDD(nodo_t<t_dato>* &);

	void InsertarBal(nodo_t<t_dato>* &, nodo_t<t_dato>*, bool&);
	void InsertarReBalIzq(nodo_t<t_dato>* &, bool&);
	void InsertarReBalDer(nodo_t<t_dato>* &, bool&);

	void EliminarRama(nodo_t<t_dato>* &, t_dato, bool&);

	void Sustituye(nodo_t<t_dato>* &, nodo_t<t_dato>* &, bool&);

	void EliminarReBalIzq(nodo_t<t_dato>* &, bool&);
	void EliminarReBalDer(nodo_t<t_dato>* &, bool&);

public:
	ArbolAVL();
	~ArbolAVL();

	void Insertar(t_dato);
	void Eliminar(t_dato);
};

template <class t_dato>
ArbolAVL<t_dato>::ArbolAVL() : ArbolBB<t_dato>() {}

template <class t_dato>
ArbolAVL<t_dato>::~ArbolAVL() {}

template <class t_dato>
void ArbolAVL<t_dato>::RotacionII(nodo_t<t_dato>* &nodo) {

	nodo_t<t_dato>* nodo1 = nodo->izq_;
	nodo->izq_ = nodo1->der_;
	nodo1->der_ = nodo;

	if (nodo1->bal_ == 1){
		nodo->bal_ = 0;
		nodo1->bal_ = 0;
	}
	else {
		nodo->bal_ = 1;
		nodo1->bal_ = -1;
	}
	nodo = nodo1;
}

template <class t_dato>
void ArbolAVL<t_dato>::RotacionDD(nodo_t<t_dato>* &nodo) {

	nodo_t<t_dato>* nodo1 = nodo->der_;
	nodo->der_ = nodo1->izq_;
	nodo1->izq_ = nodo;

	if (nodo1->bal_ == -1){
		nodo->bal_ = 0;
		nodo1->bal_ = 0;
	}
	else {
		nodo->bal_ = -1;
		nodo1->bal_ = 1;
	}
	nodo = nodo1;
}

template <class t_dato>
void ArbolAVL<t_dato>::RotacionID(nodo_t<t_dato>* &nodo) {

	nodo_t<t_dato>* nodo1 = nodo->izq_;
	nodo_t<t_dato>* nodo2 = nodo1->der_;
	
	nodo->izq_ = nodo2->der_;
	nodo2->der_ = nodo;
	nodo1->der_ = nodo2->izq_;
	nodo2->izq_ = nodo1;

	if (nodo2->bal_ == -1) {
		nodo1->bal_ = 1;
		nodo->bal_ = 0;
	}
	else if (nodo2->bal_ == 1) {
		nodo1->bal_ = 0;
		nodo->bal_ = -1;
	}
	else {						//nodo2->bal_ == 0
		nodo1->bal_ = 0;
		nodo->bal_ = 0;
	}
	nodo2->bal_ = 0;
	nodo = nodo2;
}

template <class t_dato>
void ArbolAVL<t_dato>::RotacionDI(nodo_t<t_dato>* &nodo) {

	nodo_t<t_dato>* nodo1 = nodo->der_;
	nodo_t<t_dato>* nodo2 = nodo1->izq_;

	nodo->der_ = nodo2->izq_;
	nodo2->izq_ = nodo;
	nodo1->izq_ = nodo2->der_;
	nodo2->der_ = nodo1;

	if (nodo2->bal_ == -1) {
		nodo1->bal_ = 0;
		nodo->bal_ = 1;
	}
	else if (nodo2->bal_ == 1) {
		nodo1->bal_ = -1;
		nodo->bal_ = 0;
	}
	else {						//nodo2->bal_ == 0
		nodo1->bal_ = 0;
		nodo->bal_ = 0;
	}
	nodo2->bal_ = 0;
	nodo = nodo2;
}

template <class t_dato>
void ArbolAVL<t_dato>::Insertar(t_dato dato) {
	nodo_t<t_dato>* nuevo = new nodo_t<t_dato>(dato);
	bool crece = false;

	InsertarBal(ArbolB<t_dato>::get_raiz(),nuevo, crece);
}

template <class t_dato>
void ArbolAVL<t_dato>::InsertarBal(nodo_t<t_dato>* &nodo, nodo_t<t_dato>* nuevo, bool &crece){
	if (nodo == NULL) {
		nodo = nuevo;
		crece = true;
	}
	else if (nuevo->dato_ < nodo->dato_) {
		InsertarBal(nodo->izq_, nuevo, crece);
		if (crece)
			InsertarReBalIzq(nodo, crece);
	}
	else {
		InsertarBal(nodo->der_, nuevo, crece);
		if (crece)
			InsertarReBalDer(nodo, crece);
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::InsertarReBalIzq(nodo_t<t_dato>* &nodo, bool& crece) {

	switch (nodo->bal_){
	case -1: 
		nodo->bal_ = 0;
		crece = false;
		break;
	case 0:
		nodo->bal_ = 1;
		break;
	case 1:
		nodo_t<t_dato>* nodo1 = nodo->izq_;
		if (nodo1->bal_ == 1)
			RotacionII(nodo);
		else //if (nodo1->bal_ == -1)	//****
			RotacionID(nodo);
		crece = false;
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::InsertarReBalDer(nodo_t<t_dato>* &nodo, bool& crece) {

	switch (nodo->bal_){
	case 1:
		nodo->bal_ = 0;
		crece = false;
		break;
	case 0:
		nodo->bal_ = -1;
		break;
	case -1:
		nodo_t<t_dato>* nodo1 = nodo->der_;
		if (nodo1->bal_ == -1 )
			RotacionDD(nodo);
		else //if (nodo1->bal_ == 1)	//***
			RotacionDI(nodo);
		crece = false;
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::Eliminar(t_dato dato){
	bool decrece = false;
	EliminarRama(ArbolB<t_dato>::get_raiz(), dato, decrece);
}

template <class t_dato>
void ArbolAVL<t_dato>::EliminarRama(nodo_t<t_dato>* &nodo, t_dato dato, bool& decrece){

	if (nodo == NULL)
		return;
	if (dato < nodo->dato_){
		EliminarRama(nodo->izq_, dato, decrece);
		if (decrece)
			EliminarReBalIzq(nodo, decrece);
	}
	else if (dato > nodo->dato_){
		EliminarRama(nodo->der_, dato, decrece);
		if (decrece)
			EliminarReBalDer(nodo, decrece);
	}
	else {
		nodo_t<t_dato> * eliminado = nodo;
		if (nodo->izq_ == NULL){
			nodo = nodo->der_;
			decrece = true;
		}
		else if (nodo->der_ == NULL){
			nodo = nodo->izq_;
			decrece = true;
		}
		else {
			Sustituye(eliminado, nodo->izq_, decrece);
			if (decrece)
				EliminarReBalIzq(nodo, decrece);
		}
		delete eliminado;
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::Sustituye(nodo_t<t_dato>* &eliminado, nodo_t<t_dato>* &sust, bool& decrece){

	if (sust->der_ != NULL){
		Sustituye(eliminado, sust->der_, decrece);
		if (decrece)
			EliminarReBalDer(sust, decrece);
	}
	else {
		eliminado->dato_ = sust->dato_;
		eliminado = sust;
		sust = sust->izq_;
		decrece = true;
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::EliminarReBalIzq(nodo_t<t_dato>* &nodo, bool& decrece){
	nodo_t<t_dato>* nodo1 = nodo->der_;

	switch (nodo->bal_){
	case -1: 
			if (nodo1->bal_ > 0)
				RotacionDI(nodo);
			else {
				if (nodo1->bal_ == 0)
					decrece = false;
				RotacionDD(nodo);
			}
			break;
	case 0: 
			nodo->bal_ = -1;
			decrece = false;
			break;
	case 1: 
			nodo->bal_ = 0;
	}
}

template <class t_dato>
void ArbolAVL<t_dato>::EliminarReBalDer(nodo_t<t_dato>* &nodo, bool& decrece){
	nodo_t<t_dato>* nodo1 = nodo->izq_;

	switch (nodo->bal_){
	case 1:
		if (nodo1->bal_ < 0)
			RotacionID(nodo);
		else {
			if (nodo1->bal_ == 0)
				decrece = false;
			RotacionII(nodo);
		}
		break;
	case 0:
		nodo->bal_ = 1;
		decrece = false;
		break;
	case -1:
		nodo->bal_ = 0;
	}
}