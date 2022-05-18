#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef vector<vector<long double>> Matrix;
typedef unsigned short uint16;
typedef long double int96;

Matrix A, B;

string versiune = "0.3.0";

uint16 nrMatrici, putere;

// UTILITATE

void Meniu();

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

// OUTPUT

void ScrieMatrice(Matrix X) {
	for (uint16 i = 0; i < X.size(); i++) {
		for (uint16 j = 0; j < X[0].size(); j++) {
			cout << setw(NumarCifreMaxim(X) + 1) << X[i][j];
		}
		cout << '\n';
	}

	// to be changed
	char buff;
	cin >> buff;
	Meniu();
}

// OPERATII

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

void Inmultire(Matrix A, Matrix B) {
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

void Putere(Matrix A, uint16 putere) {
	if (A[0].size() != A.size()) {
		cout << "Dimensiuni incompatibile";
		return;
	}
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
			<< "2. Transpusa \n";
		uint16 optiune;
		cin >> optiune;
		switch (optiune) {
		case 1: {
			CitirePutere(putere);
			Putere(A, putere);
			break;
		}
		case 2: {
			Transpusa(A);
			break;
		}
		default: {
			Optiuni();
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
			Inmultire(A, B);
			break;
		}
		default: {
			Optiuni();
		}
		}
	}
	//Meniu();
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