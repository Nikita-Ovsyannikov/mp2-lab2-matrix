﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem = nullptr;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz < 0) {
			throw out_of_range("Vector size should be greater than zero");
		}
		if (sz > MAX_VECTOR_SIZE) {
			throw out_of_range("Vector size should be less MAX_VECTOR_SIZE");
		}
		if (sz != 0) {
			this->pMem = new T[sz];
		}
	}

	TDynamicVector(size_t size, const T& val) : sz(size)
	{
		if (sz < 0) {
			throw out_of_range("Vector size should be greater than zero");
		}
		if (sz > MAX_VECTOR_SIZE) {
			throw out_of_range("Vector size should be less MAX_VECTOR_SIZE");
		}
		if (sz != 0) {
			this->pMem = new T[sz];
		}
		for (int i = 0; i < sz; i++) {
			this->pMem[i] = val;
		}
	}

	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		if (arr == nullptr) length_error("incorrect array");
		this->pMem = new T[sz];
		std::copy(arr, arr + this->sz, this->pMem);
	}

	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		this->pMem = new T[sz]();
		for (int i = 0; i < sz; i++) {
			this->pMem[i] = v.pMem[i];
		}
	}

	TDynamicVector(TDynamicVector&& v) noexcept
	{
		this->sz = v.sz;
		v.sz = 0;

		this->pMem = v.pMem;
		v.pMem = nullptr;
	}

	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v) noexcept
	{
		if (this->pMem != nullptr) {
			delete[] this->pMem;
		}
		this->sz = v.sz;
		this->pMem = new T[sz];
		for (int i = 0; i < sz; i++) {
			this->pMem[i] = v.pMem[i];
		}
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (this != &v) {
			sz = v.sz;
			delete[] this->pMem;
			pMem = v.pMem;
			v.pMem = nullptr;
			v.sz = 0;
		}
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return this->pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return this->pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz) {
			throw out_of_range("Index out of bounds");
		}
		return this->pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind < 0 || ind >= sz) {
			throw out_of_range("Index out of bounds");
		}
		return this->pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (this->sz == v.sz) {
			for (int i = 0; i < sz; i++) {
				if (this->pMem[i] != v.pMem[i]) return 0;
			}
			return 1;
		}
		return 0;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		if (*this == v) return 0;
		return 1;
	}

	// скалярные операции
	TDynamicVector operator+(const T& val) const
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++) {
			res[i] = this->pMem[i] + val;
		}
		return res;
	}
	TDynamicVector operator-(const T& val) const
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++) {
			res[i] = this->pMem[i] - val;
		}
		return res;
	}
	TDynamicVector operator*(const T& val) const
	{
		TDynamicVector<T> res(sz);
		for (int i = 0; i < sz; i++) {
			res[i] = this->pMem[i] * val;
		}
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v) const
	{
		if (this->size() != v.size()) {
			throw "incorrect size";
		}
		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; ++i) {
			res[i] = this->pMem[i] + v.pMem[i];
		}
		return res;
	}
	TDynamicVector operator-(const TDynamicVector& v) const
	{
		if (this->size() != v.size()) {
			throw "incorrect size";
		}
		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; ++i) {
			res[i] = this->pMem[i] - v.pMem[i];
		}
		return res;
	}
	T operator*(const TDynamicVector& v) const
	{
		if (this->size() != v.size()) {
			throw "incorrect size";
		}
		T res = static_cast<T>(0);
		for (size_t i = 0; i < sz; ++i) {
			res += this->pMem[i] * v.pMem[i];
		}
		return res;
	}


	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; 
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; 
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s < 0)
			throw out_of_range("Vector size should be greater than zero");
		if (s > MAX_MATRIX_SIZE)
			throw out_of_range("Vector size should be less MAX_MATRIX_SIZE");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	TDynamicMatrix(size_t size, const T& elem) : TDynamicMatrix(size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				pMem[i][j] = elem;
			}
		}
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	T& at(size_t i, size_t j) {
		if (i < 0 || j < 0 || i >= sz || j >= sz) throw out_of_range("incorrect index");
		return pMem[i][j];
	}

	int size() const noexcept {
		return sz;
	}

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (this->sz != m.sz) return 0;
		for (int i = 0; i < sz; i++) {
			if (this->pMem[i] != m.pMem[i]) return 0;
		}
		return 1;
	}

	// матрично-скалярные операции
	TDynamicMatrix<T> operator*(const T& val)
	{
		TDynamicMatrix<T> res(this->sz);
		for (int i = 0; i < sz; i++) res[i] = pMem[i] * val;
		return res;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (this->sz != v.size()) throw "incorrect operation";
		TDynamicVector<T> res(this->sz);
		for (int i = 0; i < this->sz; i++) {
			res[i] = this->pMem[i] * v;
		}
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (this->sz != m.sz) throw "incorrect operation";
		TDynamicMatrix<T> res(m.sz);
		for (int i = 0; i < this->sz; i++) {
			res[i] = (*this)[i] + m[i];
		}
		return res;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (this->sz != m.sz) throw "incorrect operation";
		TDynamicMatrix<T> res(m.sz);
		for (int i = 0; i < this->sz; i++) {
			res[i] = (*this)[i] - m[i];
		}
		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (this->sz != m.sz) throw "incorrect operation";
		TDynamicMatrix<T> res(this->sz, 0);


		for (size_t i = 0; i < this->sz; i++) {
			for (size_t j = 0; j < this->sz; j++) {
				for (size_t k = 0; k < this->sz; k++) {
					res[i][j] += (*this).pMem[i][k] * m.pMem[k][j];
				}
			}
		}
		return res;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (int i = 0; i < v.sz; i++) {
			cin >> v.pMem[i];
		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (int i = 0; i < v.sz; i++) {
			cout << v.pMem[i] << "\n";
		}
		return ostr;
	}
};

#endif
