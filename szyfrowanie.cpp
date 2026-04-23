#include <iostream>
#include "szyfrowanie.h"
#include <sodium.h>
#include <sodium/core.h>
#include <sodium/crypto_generichash.h>
#include <sodium/crypto_pwhash.h>
#include <sodium/crypto_secretbox.h>
#include <sodium/randombytes.h>
#include <string>

using namespace std;

constexpr size_t KEY_LEN=crypto_box_SEEDBYTES;

string test(const string& haslo)
{
    cout << "Hello, szyfrowanie" << endl;        
    if (sodium_init() < 0){
        cout << "Biblioteka sodium nie mogła zostać załadowana" << endl;
        return {};
    }

    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char key[KEY_LEN];
    char hash[crypto_pwhash_STRBYTES];
    
    randombytes_buf(salt, sizeof salt);

    if  (crypto_pwhash_str(
            hash,
            haslo.c_str(),
            haslo.size(),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE
        ) !=0){
        cout << "Za mało pamięci" << endl;
        return{};
    }

    cout << "Oto hash hasła:\n" << hash << endl;
    return string(hash);
}   
