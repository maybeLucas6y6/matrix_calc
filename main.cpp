#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "functii.h"

using namespace std;

int nrMatrici, putere;

Matrice matriceA, matriceB;

int main() {
	CitireNumarMatrici(nrMatrici);
	if (nrMatrici == 1) {
		CitireNumarLinii(matriceA.n);
		CitireNumarColoane(matriceA.m);
		matriceA.SeteazaDimensiuni(matriceA.n, matriceA.m);
		CitireMatrice(matriceA);

		/*system("CLS");
		ScrieMatrice(matriceA);*/

		CitirePutere(putere);
		Putere(matriceA, putere);

		/*Transpusa(matriceA);*/
	}
	else {
		CitireNumarLinii(matriceA.n);
		CitireNumarColoane(matriceA.m);
		matriceA.SeteazaDimensiuni(matriceA.n, matriceA.m);
		CitireMatrice(matriceA);

		CitireNumarLinii(matriceB.n);
		CitireNumarColoane(matriceB.m);
		matriceB.SeteazaDimensiuni(matriceB.n, matriceB.m);
		CitireMatrice(matriceB);

		/*system("CLS");
		ScrieMatrice(matriceA);
		cout << '\n';
		ScrieMatrice(matriceB);*/

		//Adunare(matriceA, matriceB);
		//Inmultire(matriceA, matriceB);
	}
	system("pause");
	return 0;
}