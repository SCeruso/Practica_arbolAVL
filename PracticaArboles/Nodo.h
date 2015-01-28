#pragma once
#include <iostream>
#include "Tdato.h"
using namespace std;

#define EMPTY -655555

template <class t_dato>
class nodo_t {

public:
	t_dato dato_;
	nodo_t* izq_;
	nodo_t* der_;
	int bal_;

	nodo_t(t_dato, nodo_t* = NULL, nodo_t* = NULL, int = 0);
	~nodo_t(void);

};

template <class t_dato>
nodo_t <t_dato>::nodo_t(t_dato dato, nodo_t* izq, nodo_t* der, int bal) : dato_(dato), izq_(izq), der_(der), bal_(bal) {}

template <class t_dato>
nodo_t <t_dato>::~nodo_t(void) {}
