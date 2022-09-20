/* Nama                 : Raihan Fadhlal A
   NPM                  : 140810200025
   Kelas                : A
   Deskripsi Program    : Program Shift Cipher
*/

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string.h>

using namespace std;

string enkripsi(string plain, int kunci);
string dekripsi(string cipher, int kunci);

string enkripsi(string plain, int kunci) {
	int i;
	string cipher = "";

	for (i = 0; i < plain.length(); i++) {
        if (plain[i] == ' ') {
            cipher += ' ';
        }
		// Huruf Kapital
		else if (isupper(plain[i])) {

			cipher += char(int((plain[i] + kunci - 65) % 26) + 65);
		}
		// Huruf Kecil
		else
			cipher += char(int((plain[i] + kunci - 97) % 26) + 97);
	}
	return cipher;
}

string dekripsi(string cipher, int kunci) {
	int i;
	string plain = "";

	for (i = 0; i < cipher.length(); i++) {
        if (plain[i] == ' ') {
            cipher += ' ';
        }
		// Huruf Kapital
		else if (isupper(cipher[i])) {
			if (cipher[i] - kunci < 65) {
				plain += char(int(26 + (cipher[i] - kunci)));
			}
			else
				plain += char(int((cipher[i] - kunci - 65) % 26) + 65);
		}
		// Huruf Kecil
		else if (cipher[i] - kunci < 97) {
			plain += char(int(26 + (cipher[i] - kunci)));
		}
		else
			plain += char(int((cipher[i] - kunci - 97) % 26) + 97);
	}
	return plain;
}

int main() {
	string plain, cipher, jawab;
	int kunci;

	cout << "=== Program Shift Cipher ===" << endl;

    ulang:
	cout << "Input Plainteks: "; cin >> plain;
	cout << "Input Key      : "; cin >> kunci;

	string chiper = enkripsi(plain, kunci);
	cout << "Hasil Enkripsi: " << chiper << endl;
	cout << "Hasil Deskripsi: " << dekripsi(chiper, kunci) << endl;

	cout << "Ulang Program ? (Y/N) : ";
	cin >> jawab;
	cout << endl;

	if (jawab == "Y" || jawab == "y")
	{
		goto ulang;
	}
	else
	{
		return 0;
	}
}