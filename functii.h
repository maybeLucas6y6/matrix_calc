#pragma once

using namespace std;

class Matrice {
public:
	int n = 0, m = 0;
	vector<vector<int>> valori;
	void SeteazaDimensiuni(int nNou, int mNou) {
		n = nNou;
		m = mNou;
	}
};

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
		X.valori.push_back(vector<int>{});
		for (int j = 0; j < X.m; j++) {
			int val;
			cin >> val;
			X.valori[i].push_back(val);
		}
	}
}

void ScrieMatrice(Matrice X) {
	for (int i = 0; i < X.n; i++) {
		for (int j = 0; j < X.m; j++) {
			cout << setw(4) << X.valori[i][j];
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
		C.valori.push_back(vector<int>{});
		for (int j = 0; j < A.m; j++) {
			C.valori[i].push_back(A.valori[i][j] + B.valori[i][j]);
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
		C.valori.push_back(vector<int>{});
		for (int j = 0; j < A.m; j++) {
			C.valori[i].push_back(A.valori[i][j] - B.valori[i][j]);
		}
	}
	ScrieMatrice(C);
}