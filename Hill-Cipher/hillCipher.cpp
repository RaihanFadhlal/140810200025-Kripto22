/* Nama                 : Raihan Fadhlal A
   NPM                  : 140810200025
   Kelas                : A
   Deskripsi Program    : Program Hill Cipher 2x2
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int kunciInverse[2][2];

string handleSpasi(string str)
{
	int count = 0;
	for (int i = 0; str[i]; i++)
		if (str[i] == ' ')
			str[i] = 'X';
	return str;
}

int cariGCD(int m, int n)
{
	if (n > m)
		swap(m, n);

	do
	{
		int temp = m % n;
		m = n;
		n = temp;
	} while (n != 0);

	return m;
}

int cariInvers(int m, int n)
{
	int t0 = 0, t1 = 1, invers, q, r, b = m;
	while (r != 1)
	{
		q = m / n;
		r = m % n;
		invers = t0 - q * t1;
		if (invers < 0)
		{
			invers = b - (abs(invers) % b);
		}
		else
		{
			invers %= b;
		}
		t0 = t1;
		t1 = invers;
		m = n;
		n = r;
	}
	return invers;
}

string cariEnkripsi(string plain, int kunci[2][2])
{
	string cipher = "";
	int stringLength = plain.length();
	if (plain.length() % 2 == 1)
		stringLength += 1;
	char plainMatrix[2][stringLength];
	int count = 0;
	for (int i = 0; i < stringLength / 2; i++)
		for (int j = 0; j < 2; j++)
		{
			if (plainMatrix[j][i] == 32)
			{
				break;
			}
			plainMatrix[j][i] = plain[count];
			count++;
		}
	for (int i = 0; i < stringLength / 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int tempCipher = 0;
			for (int k = 0; k < 2; k++)
			{
				int l = kunci[j][k] * (plainMatrix[k][i] % 65);
				tempCipher += l;
			}
			tempCipher = (tempCipher % 26) + 65;
			cipher += (char)tempCipher;
		}
	}
	return cipher;
}

void cariInverseMatriks(int kunci[2][2])
{
	int kunciTemp[2][2];
	kunciTemp[0][0] = (int)(kunci[1][1]);
	kunciTemp[0][1] = (int)((-1) * kunci[0][1]);
	kunciTemp[1][0] = (int)((-1) * kunci[1][0]);
	kunciTemp[1][1] = (int)(kunci[0][0]);
	int determinant = (kunci[0][0] * kunci[1][1]) - (kunci[0][1] * kunci[1][0]);
	int det_inv = 0;
	int flag = 0;
	for (int i = 0; i < 26; i++)
	{
		flag = (determinant * i) % 26;
		if (flag < 0)
		{
			flag = flag + 26;
		}
		if (flag == 1)
		{
			det_inv = i;
		}
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			if (kunciTemp[i][j] < 0)
			{
				int tempNumber = kunciTemp[i][j] * det_inv;
				kunciInverse[i][j] = ((tempNumber % 26) + 26) % 26;
			}
			else
			{
				kunciInverse[i][j] = (kunciTemp[i][j] * det_inv % 26);
			}
		}
}

string cariDekripsi(string cipher, int kunci[2][2])
{
	string plain = "";
	int stringLength = cipher.length();
	if (plain.length() % 2 == 1)
		stringLength = cipher.length() + 1;
	cariInverseMatriks(kunci);
	char cipherMatrix[2][stringLength / 2];
	int count = 0;
	for (int i = 0; i < stringLength / 2; i++)
		for (int j = 0; j < 2; j++)
		{
			cipherMatrix[j][i] = cipher[count];
			count++;
		}

	for (int i = 0; i < cipher.length() / 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int tempPlain = 0;
			for (int k = 0; k < 2; k++)
			{
				int l = kunciInverse[j][k] * (cipherMatrix[k][i] % 65);
				tempPlain += l;
			}
			tempPlain = (tempPlain % 26) + 65;
			plain += (char)tempPlain;
		}
	}
	return plain;
}

void cariKunci()
{
	//mendeklarasikan matriks
	string plainteks, cipherteks;
	int kunci[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter;
	int p, c;
	int transpose[2][2];

	// menginput plainteks
	cout << "Masukan Plainteks : ";
	cin.ignore();
	getline(cin, plainteks);

	//menginput plainteks ke plainMatrix
	counter = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			p = toupper(plainteks[counter]) - 65;
			plainMatrix[i][j] = p;
			counter++;
		}
	}

	//menginput cipherteks
	cout << "Masukan Cipherteks : ";
	getline(cin, cipherteks);

	//menginput cipherteks ke cipMatrix
	counter = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			c = toupper(cipherteks[counter]) - 65;
			cipMatrix[i][j] = c;
			counter++;
		}
	}

	//rumus determinan
	det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
	if (cariGCD(det, 26) == 1)
	{
		//rumus cari inverse dari determinan
		detInv = cariInvers(26, det);

		//mencari matriks adjoin
		adj[0][0] = plainMatrix[1][1];
		adj[0][1] = (-1) * plainMatrix[0][1];
		adj[1][0] = (-1) * plainMatrix[1][0];
		adj[1][1] = plainMatrix[0][0];

		//mencari matriks invers dari plainteks
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				plainteksInv[i][j] = detInv * adj[i][j];
				if (plainteksInv[i][j] < 0)
				{
					plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j]) % 26);
				}
				else
				{
					plainteksInv[i][j] = plainteksInv[i][j];
					plainteksInv[i][j] = plainteksInv[i][j] % 26;
				}
			}
		}

		//mencari kunci
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				kunci[i][j] = 0;
				for (int k = 0; k < 2; k++)
				{
					kunci[i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
				}
				kunci[i][j] %= 26;
			}
		}

		//kunci akhir
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				transpose[j][i] = kunci[i][j];
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << (transpose[i][j]) << "\t";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Determinan tidak sesuai" << endl;
		cout << "Key tidak ditemukan!" << endl
			 << endl;
	}
	system("pause");
	system("cls");
}

int main() {
	bool menuActive = true;
	int kunci[2][2];
	kunci[0][0] = 7;
	kunci[0][1] = 8;
	kunci[1][0] = 19;
	kunci[1][1] = 3;
	string plain, cipher;
	int pil;
	while (menuActive) {
		cout << "\n === Program Hill Cipher Matriks 2x2 === " << endl;
		cout << "1. Tentukan Kunci" << endl;
		cout << "2. Enkripsi" << endl;
		cout << "3. Dekripsi" << endl;
		cout << "4. Cari Kunci" << endl;
		cout << "5. Keluar" << endl;
		cout << "Pilih Opsi: ";
		cin >> pil;
		switch (pil)
		{
		case 1:
			cout << "\nInput kunci (2x2 matrix) : " << endl;
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
				{
					cin >> kunci[i][j];
				}
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					cout << kunci[i][j] << "\t";
				}
				cout << endl;
			}
			break;        
		case 2:
			cout << "\nInput Plaintext: ";
			cin.ignore();
			getline(cin, plain);
			plain = handleSpasi(plain);
			transform(plain.begin(), plain.end(), plain.begin(), ::toupper);
			cout << "Ciphertext : " << cariEnkripsi(plain, kunci) << endl
				 << endl;
			break;
		case 3:
			cout << "\nInput Ciphertext: ";
			cin.ignore();
			getline(cin, cipher);
			cipher = handleSpasi(cipher);
			transform(cipher.begin(), cipher.end(), cipher.begin(), ::toupper);
			cout << "Plaintext : " << cariDekripsi(cipher, kunci) << endl
				 << endl;
			break;
		case 4:
			cout << endl;
			cariKunci();
			break;
		case 5:
			menuActive = false;
			break;
		default:
			cout << "\nPilihan salah" << endl;
			break;
		}
	}
}