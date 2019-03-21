#pragma once

#include <windows.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cmath>
#include <stdarg.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "PrintableObject.h"

template <class T>
class Inscription :	public PrintableObject {
	
public:

	Inscription(const T&);
	Inscription(const Inscription<T>&);
	virtual ~Inscription();

	const T getInscription() const;
	void setInscription(const T&);

	const Inscription<T> &operator= (const T&);
	const Inscription<T> &operator= (const Inscription<T>&);
	
	virtual void write(std::ostream*) const;
	
private:

	T inscr;
};

template <class T>
Inscription<T>::Inscription(const T& ins)
	: inscr(ins) {}

template <class T>
Inscription<T>::Inscription(const Inscription<T> &a)
	: inscr(a.getInscription()) {}

template <class T>
Inscription<T>::~Inscription() {}

template <class T>
const T Inscription<T>::getInscription() const {
	return inscr;
}

template <class T>
void Inscription<T>::setInscription(const T &a) {
	inscr = a;
}

template <class T>
const Inscription<T> &Inscription<T>::operator= (const T &right) {
	setInscription(right);
	return *this;
}

template <class T>
const Inscription<T> &Inscription<T>::operator= (const Inscription<T> &right) {
	if (&right != this) {
		setInscription(right.getInscription());
	}
	return *this;
}

template <class T>
void Inscription<T>::write(std::ostream* fout) const {
	(*fout) << getInscription() << "\n";
}