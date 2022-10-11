/* Nama                 : Raihan Fadhlal A
   NPM                  : 140810200025
   Kelas                : A
   Deskripsi Program    : Program Vigenere Cipher
*/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;
 
string loopKey(string plain, string kunciFull) {
    int x = plain.size();
 
    for (int i = 0; ; i++) {
        if (x == i)
            i = 0;
        if (kunciFull.size() == plain.size())
            break;
        kunciFull.push_back(kunciFull[i]);
    }
    return kunciFull;
}
 
// Mengenkrip teks
string enkripTeks(string plain, string kunciFull) {
    string cipher_text;
 
    for (int i = 0; i < plain.size(); i++) {
        char x = (plain[i] + kunciFull[i]) %26;
 
        x += 'A';
 
        cipher_text.push_back(x);
    }
    return cipher_text;
}
 
// Mendekrip teks
string dekripTeks(string cipher_text, string kunciFull) {
    string orig_text;
 
    for (int i = 0 ; i < cipher_text.size(); i++) {
        char x = (cipher_text[i] - kunciFull[i] + 26) %26;
 
        x += 'A';
        orig_text.push_back(x);
    }
    return orig_text;
}
 
int main() {
    string plain = "KRIPTOSANGATSERU";
    string kunci = "RAIHAN";
 
    string kunciFull = loopKey(plain, kunci);
    string cipher_text = enkripTeks(plain, kunciFull);

    cout << "=== PROGRAM VIGENERE CIPHER ===\n";
    cout << "PlainTeks  : " << plain << "\n";
    cout << "Kunci      : " << kunci << "\n";
    cout << "Cipherteks : " << cipher_text << "\n";
    cout << "Dekripsi   : " << dekripTeks(cipher_text, kunciFull);
    return 0;
}