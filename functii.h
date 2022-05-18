#pragma once

using namespace std;

class Matrice {
public:
	int n = 0, m = 0;
	vector<vector<int>> valori;
	void SeteazaDimensiuni(int nNou, int mNou) {
		n = nNou;
		m = mNou;
		for (int i=0; i < n; i++) {
			valori.push_back(vector<int>{});
			for (int j = 0; j < m; j++) {
				valori[i].push_back(0);
			}
		}
	}
};

int NrCifMax(Matrice X) {
	int cmax = 0;
	for (int i = 0; i < X.n; i++) {
		for (int j = 0; j < X.m; j++) {
			int nr = X.valori[i][j], c = 0;
			while (nr){
				c++;
				nr = nr / 10;
			}
			if (c > cmax) {
				cmax = c;
			}
		}
	}
	return cmax;
}

bool Apartine(int a, int b, int x) {
	if (x >= a && x <= b)
		return true;
	else
		return false;
}

void CitireNumarMatrici(int &nr) {
	cout << "Numar de matrici: ";
	cin >> nr;
	if (Apartine(1,2,nr)) {
		return;
	}
	else {
		cout << "Numarul de matrici trebuie sa fie 1 sau 2! \n";
		CitireNumarMatrici(nr);
	}
}

void CitireNumarLinii(int& nr) {
	cout << "Numar linii: ";
	cin >> nr;
	if (Apartine(1, 100, nr)) {
		return;
	}
	else {
		CitireNumarLinii(nr);
	}
}

void CitireNumarColoane(int& nr) {
	cout << "Numar coloane: ";
	cin >> nr;
	if (Apartine(1, 100, nr)) {
		return;
	}
	else {
		CitireNumarColoane(nr);
	}
}

void CitireMatrice(Matrice &X) {
	for (int i = 0; i < X.n; i++) {
		for (int j = 0; j < X.m; j++) {
			cin >> X.valori[i][j];
		}
	}
}

void CitirePutere(int& nr) {
	cout << "Putere: ";
	cin >> nr;
	if (Apartine(1, 10, nr)) {
		return;
	}
	else {
		CitirePutere(nr);
	}
}

void ScrieMatrice(Matrice X) {
	for (int i = 0; i < X.n; i++) {
		for (int j = 0; j < X.m; j++) {
			cout << setw(NrCifMax(X)+1) << X.valori[i][j];
		}
		cout << '\n';
	}
}

void Adunare(Matrice A, Matrice B) {
	system("CLS");
	if (A.n != B.n || A.m != B.m) {
		cout << "Dimensiuni diferite";
		return;
	}
	Matrice C;
	C.SeteazaDimensiuni(A.n, A.m);
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < A.m; j++) {
			C.valori[i][j]=(A.valori[i][j] + B.valori[i][j]);
		}
	}
	ScrieMatrice(C);
}

void Scadere(Matrice A, Matrice B) {
	system("CLS");
	if (A.n != B.n || A.m != B.m) {
		cout << "Dimensiuni diferite";
		return;
	}
	Matrice C;
	C.SeteazaDimensiuni(A.n, A.m);
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < A.m; j++) {
			C.valori[i][j]=(A.valori[i][j] - B.valori[i][j]);
		}
	}
	ScrieMatrice(C);
}

void Inmultire(Matrice A, Matrice B) {
	system("CLS");
	if (A.m != B.n) {
		cout << "Dimensiuni incompatibile";
		return;
	}
	Matrice C;
	C.SeteazaDimensiuni(A.n, B.m);
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < B.m; j++) {
			int s = 0;
			for (int z = 0; z < B.n; z++) {
				s += A.valori[i][z] * B.valori[z][j];
			}
			C.valori[i][j] = s;
		}
	}
	ScrieMatrice(C);
}

void Putere(Matrice A, int putere) {
	system("CLS");
	if (A.m != A.n) {
		cout << "Dimensiuni incompatibile";
		return;
	}
	Matrice C,D;
	D.SeteazaDimensiuni(A.n, A.m);
	C = A;
	while (putere!=1) {
		for (int i = 0; i < A.n; i++) {
			for (int j = 0; j < C.m; j++) {
				int s = 0;
				for (int z = 0; z < C.n; z++) {
					s += A.valori[i][z] * C.valori[z][j];
				}
				D.valori[i][j] = s;
			}
		}
		C.valori = D.valori;
		putere--;
	}
	ScrieMatrice(C);
}

void Transpusa(Matrice A) {
	Matrice C;
	C = A;
	for (int i = 0; i < A.n; i++) {
		for (int j = i + 1; j < A.m; j++) {
			swap(C.valori[i][j], C.valori[j][i]);
		}
	}
	ScrieMatrice(C);
}