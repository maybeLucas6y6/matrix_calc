#include "functii2.h"

using namespace std;

int main() {
	cout << "Calculator de matrici - v." << versiune << '\n';
	CitireNumarMatrici(nrMatrici);
	CitireDimensiuni(A);
	CitireMatrice(A);
	if (nrMatrici > 1) {
		CitireDimensiuni(B);
		CitireMatrice(B);
	}
	Meniu();
	system("pause");
	return 0;
}