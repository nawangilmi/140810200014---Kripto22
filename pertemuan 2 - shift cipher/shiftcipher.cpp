#include <bits/stdc++.h>
using namespace std;

string enkripsi(string plain_text, int key){
    string cipher_text = "";
    for (int i = 0; i < plain_text.size(); i++){
        if (isupper(plain_text[i])){
            cipher_text += char(int(plain_text[i] + key - 65) % 26 + 65);
        }else if (islower(plain_text[i])){
            cipher_text += char(int(plain_text[i] + key - 97) % 26 + 97);
        }else{
            cipher_text += plain_text[i];
        }
    }
    return cipher_text;
}

string dekripsi(string cipher_text, int key)
{
    string plain_text = "";
    for (int i = 0; i < cipher_text.size(); i++){
        if (isupper(cipher_text[i])){
            plain_text += char((int(cipher_text[i] - key - 65) % 26 + 26) % 26 + 65);
        }else if (islower(cipher_text[i])){
            plain_text += char((int(cipher_text[i] - key - 97) % 26 + 26) % 26 + 97);
        }else {
            plain_text += cipher_text[i];
        }
    }
    return plain_text;
}

int main(){
    string plain_text;
    cout << "PROGRAM SHIFT CIPHER" << endl;
    cout << "Masukan Plaintext : ";
    getline(cin, plain_text);
    int key;
    cout << "Masukan Kunci : ";
    cin >> key;
    string cipher_text = enkripsi(plain_text, key);

    cout << "\nEnkripsi : \n";
    cout << "Ciphertext : " << cipher_text << endl;

    cout << "\nDekripsi:\n";
    cout << "Plaintext : " << dekripsi(cipher_text, key) << endl;
}