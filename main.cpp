#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "functii.h"

using namespace std;

int nrMatrici;

Matrice matriceA, matriceB;

int main() {
	CitireNumarMatrici(nrMatrici);
	if (nrMatrici == 1) {
		CitireNumarLinii(matriceA.n);
		CitireNumarColoane(matriceA.m);
		CitireMatrice(matriceA);

		system("CLS");
		ScrieMatrice(matriceA);
	}
	else {
		CitireNumarLinii(matriceA.n);
		CitireNumarColoane(matriceA.m);
		CitireMatrice(matriceA);

		CitireNumarLinii(matriceB.n);
		CitireNumarColoane(matriceB.m);
		CitireMatrice(matriceB);

		/*system("CLS");
		ScrieMatrice(matriceA);
		cout << '\n';
		ScrieMatrice(matriceB);*/

		Adunare(matriceA, matriceB);
	}
	system("pause");
	return 0;
}