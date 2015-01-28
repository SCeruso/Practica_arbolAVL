#pragma once
#include "ArbolAVL.h"

template <class t_dato>
class Analisis
{
public:
	ArbolAVL<t_dato>* arbol_;
	Analisis();
	~Analisis();
	virtual void run() = 0;
};

template <class t_dato>
Analisis<t_dato>::Analisis()
{
}

template <class t_dato>
Analisis<t_dato>::~Analisis()
{
	if (arbol_ != NULL){
		delete arbol_;
		arbol_ = NULL;
	}
}
