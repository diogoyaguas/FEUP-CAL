#include "ExcessaoBase.h"
#include <string>
#include <iostream>

using namespace std;

ExcessaoBase::ExcessaoBase(const string& argRazao) {
	razao = argRazao;
}

ostream& operator<<(ostream& out, const ExcessaoBase& excessao) {
	out << excessao.razao << endl;
	return out;
}

const string& ExcessaoBase::getReason() const {
	return razao;
}