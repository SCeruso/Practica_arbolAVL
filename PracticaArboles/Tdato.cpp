#include "Tdato.h"


tester::tester(double n) : n_(n)
{
}


tester::~tester()
{
}

double& tester::valor(){
	return n_;
}

double& tester::presicion(){ return p_; }

int& tester::contador(){ return cont_; }

bool tester::operator >(tester& t) {
	cont_++;
	return (valor() > t.valor()) && (fabs(valor() - t.valor()) > p_) ? true : false;
}

bool tester::operator <(tester& t) {
	cont_++;
	return (valor() < t.valor()) && (fabs(valor() - t.valor()) > p_) ? true : false;
}


bool tester::operator ==(tester& t) {
	cont_++;
	return fabs(valor() - t.valor()) < p_ ? true : false;
}
bool tester::operator !=(tester& t) {
	cont_++;
	return fabs(valor() - t.valor()) > p_ ? true : false;
}
ostream& operator << (ostream& os, tester d){
	os << d.valor();
	return os;
}