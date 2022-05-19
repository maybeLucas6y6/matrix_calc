#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
//#include <chrono> // pt a masura timpul de executie

using namespace std;

typedef vector<vector<long double>> Matrix;
typedef unsigned short uint16;
typedef long double int96;

Matrix A, B;

string versiune = "0.3.0";

uint16 nrMatrici, putere;

// UTILITATE

void Meniu();
void Optiuni();

uint16 NumarCifreMaxim(Matrix X) {
	uint16 cmax = 0;
	for (uint16 i = 0; i < X.size(); i++) {
		for (uint16 j = 0; j < X[0].size(); j++) {
			string str;
			if (X[i][j] == floor(X[i][j])) {
				str = to_string((long int)X[i][j]);
			}
			else {
				str = to_string(X[i][j]);
			}
			uint16 c = str.length();
			if (c > cmax) {
				cmax = c;
			}
		}
	}
	return cmax;
}

bool Apartine(uint16 a, uint16 b, uint16 x) {
	return (x >= a && x <= b);
}

// INPUT

void CitireNumarMatrici(uint16& nr) {
	cout << "Numar de matrici: ";
	cin >> nr;
	if (Apartine(1, 2, nr)) {
		return;
	}
	else {
		cout << "Numarul de matrici trebuie sa fie 1 sau 2! \n";
		CitireNumarMatrici(nr);
	}
}

uint16 CitireNumarLinii(Matrix& X) {
	cout << "Numar linii: ";
	uint16 nr;
	cin >> nr;
	if (Apartine(1, 100, nr)) {
		return nr;
	}
	else {
		CitireNumarLinii(X);
	}
}

void CitireDimensiuni(Matrix& X) {
	uint16 n = CitireNumarLinii(X);
	cout << "Numar coloane: ";
	uint16 m;
	cin >> m;
	if (Apartine(1, 100, m)) {
		
		X.resize(n, vector<int96>(m));
		return;
	}
	else {
		CitireDimensiuni(X);
	}
}

void CitireMatrice(Matrix& X) {
	cout << "Introduceti valori: \n";
	for (uint16 i = 0; i < X.size(); i++) {
		for (uint16 j = 0; j < X[0].size(); j++) {
			cin >> X[i][j];
		}
	}
}

void CitirePutere(uint16& nr) {
	cout << "Putere (intre 1 si 10) : ";
	cin >> nr;
	if (Apartine(1, 10, nr)) {
		return;
	}
	else {
		CitirePutere(nr);
	}
}

void CitireConstanta(int96& nr) {
	cout << "Constanta : ";
	cin >> nr;
	return;
}

// OUTPUT

void RescrieOptiuni() {
	cin.get();
	Optiuni();
}

void ScrieMatrice(Matrix X) {
	for (uint16 i = 0; i < X.size(); i++) {
		for (uint16 j = 0; j < X[0].size(); j++) {
			cout << setw(NumarCifreMaxim(X) + 1) << X[i][j];
		}
		cout << '\n';
	}
	RescrieOptiuni();
}

// OPERATII

vector<uint16> permutare;
vector<bool> ocupat;
int96 suma,produs;

int Semn(vector<uint16> permutare) {
	uint16 s = 0;
	vector<bool> vf;
	vf.resize(permutare.size() + 1, false); //vf e numerotat de la 1
	s += permutare[0] - 1; //primul element va avea (element - 1) inversiuni
	vf[permutare[0]] = true; 
	for (uint16 i = 1; i < permutare.size() - 1; i++) {
		vf[permutare[i]] = true;
		for (uint16 j = permutare[i] - 1; j >= 1; j--) {
			if (vf[j] == false) {
				s++;
			}
		}
	}
	return (int)pow(-1, s);
}

int Semn2(vector<uint16> p) {
	//auto start = chrono::high_resolution_clock::now();
	vector<bool> vizitat(p.size(), false);
	int semn = 1;
	for (uint16 i = 0; i < p.size(); i++) {
		if (!vizitat[i]) {
			uint16 x = i;
			uint16 lungime = 0;
			while (!vizitat[x]) {
				lungime++;
				vizitat[x] = true;
				x = p[x] - 1;
			}
			if (lungime % 2 == 0) {
				semn = -semn;
			}
		}
	}
	//auto stop = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	//cout << "Semn2 a durat: " << duration.count() << " microsecunde\n";
	return semn;
}

bool Valid(uint16 k) {
	for (int j = k - 2; j >= 0; j--) {
		if (permutare[k-1] == permutare[j]) {
			return false;
		}
	}
	return true;
}

void Backtracking(Matrix X, uint16 k = 1) {
	if (k - 1 == permutare.size()) {
		produs = Semn2(permutare);
		for (uint16 j = 0; j < permutare.size(); j++) {
			produs *= X[j][permutare[j]-1];
		}
		suma += produs;
	}
	else
		for (uint16 i = 0; i < permutare.size(); i++) {
			if (!ocupat[i]) {
				ocupat[i] = true;
				permutare[k - 1] = i + 1;
				Backtracking(X, k + 1);
				ocupat[i] = false;
			}
		}
}

void Determinant(Matrix X) {
	if (X.size() != X[0].size()) {
		cout << "Matricea nu este patratica \n";
		return;
	}
	permutare.resize(X.size());
	ocupat.resize(X.size(), false);
	Backtracking(X);
	cout << "Determinantul este: " << suma << '\n';
	RescrieOptiuni();
}

void Adunare(Matrix A, Matrix B) {
	if (A.size() != B.size() || A[0].size() != B[0].size()) {
		cout << "Dimensiuni diferite";
		return;
	}
	Matrix C;
	C.resize(A.size(), vector<int96>(A[0].size()));
	for (uint16 i = 0; i < C.size(); i++) {
		for (uint16 j = 0; j < C[0].size(); j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	ScrieMatrice(C);
}

void Scadere(Matrix A, Matrix B) {
	if (A.size() != B.size() || A[0].size() != B[0].size()) {
		cout << "Dimensiuni diferite";
		return;
	}
	Matrix C;
	C.resize(A.size(), vector<int96>(A[0].size()));
	for (uint16 i = 0; i < C.size(); i++) {
		for (uint16 j = 0; j < C[0].size(); j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
	ScrieMatrice(C);
}

void InmultireMatrici(Matrix A, Matrix B) {
	if (A[0].size() != B.size()) {
		cout << "Dimensiuni incompatibile";
		return;
	}
	Matrix C;
	C.resize(A.size(), vector<int96>(A[0].size()));
	for (uint16 i = 0; i < A.size(); i++) {
		for (uint16 j = 0; j < B[0].size(); j++) {
			int96 s = 0;
			for (uint16 z = 0; z < B.size(); z++) {
				s += A[i][z] * B[z][j];
			}
			C[i][j] = s;
		}
	}
	ScrieMatrice(C);
}

void InmultireConstanta(Matrix A) {
	int96 constanta;
	Matrix B;
	CitireConstanta(constanta);
	B = A;
	for (uint16 i = 0; i < B.size(); i++) {
		for (uint16 j = 0; j < B[0].size(); j++) {
			B[i][j] = B[i][j] * constanta;
		}
	}
	ScrieMatrice(B);
}

void Putere(Matrix A, uint16 putere) {
	if (A[0].size() != A.size()) {
		cout << "Dimensiuni incompatibile";
		return;
	}
	CitirePutere(putere);
	Matrix C, D;
	D.resize(A.size(), vector<int96>(A[0].size()));
	C = A;
	while (putere != 1) {
		for (uint16 i = 0; i < A.size(); i++) {
			for (uint16 j = 0; j < A[0].size(); j++) {
				int96 s = 0;
				for (uint16 z = 0; z < C.size(); z++) {
					s += A[i][z] * C[z][j];
				}
				D[i][j] = s;
			}
		}
		C = D;
		putere--;
	}
	ScrieMatrice(C);
}

void Transpusa(Matrix A) {
	Matrix C;
	C = A;
	for (uint16 i = 0; i < A.size(); i++) {
		for (uint16 j = i + 1; j < A[0].size(); j++) {
			swap(C[i][j], C[j][i]);
		}
	}
	ScrieMatrice(C);
}

// bruh

void Optiuni() {
	if (nrMatrici == 1) {
		cout << "1. Ridicare la putere \n"
			<< "2. Transpusa \n"
			<< "3. Determinant \n"
			<< "4. Inmultire cu o constanta \n";
		uint16 optiune;
		cin >> optiune;
		switch (optiune) {
		case 1: {
			Putere(A, putere);
			break;
		}
		case 2: {
			Transpusa(A);
			break;
		}
		case 3: {
			Determinant(A);
			break;
		}
		case 4: {
			InmultireConstanta(A);
			break;
		}
		default: {
			Meniu();
		}
		}
	}
	else {
		cout << "1. Adunare \n"
			<< "2. Scadere \n"
			<< "3. Inmultire \n";
		uint16 optiune;
		cin >> optiune;
		switch (optiune) {
		case 1: {
			Adunare(A, B);
			break;
		}
		case 2: {
			Scadere(A, B);
			break;
		}
		case 3: {
			InmultireMatrici(A, B);
			break;
		}
		default: {
			Meniu();
		}
		}
	}
}

void Meniu() {
	system("CLS");
	cout << "Calculator de matrici - v." << versiune << '\n';
	if (!A.empty()) {
		for (uint16 i = 0; i < A.size(); i++) {
			for (uint16 j = 0; j < A[0].size(); j++) {
				cout << setw(NumarCifreMaxim(A) + 1) << A[i][j];
			}
			cout << '\n';
		}
	}
	cout << '\n';
	if (!B.empty()) {
		for (uint16 i = 0; i < B.size(); i++) {
			for (uint16 j = 0; j < B[0].size(); j++) {
				cout << setw(NumarCifreMaxim(B) + 1) << B[i][j];
			}
			cout << '\n';
		}
	}
	Optiuni();
}