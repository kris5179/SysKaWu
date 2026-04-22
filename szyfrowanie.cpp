#include <iostream>
#include "szyfrowanie.h"
#include <sodium.h>
#include <sodium/core.h>
#include <sodium/crypto_generichash.h>
#include <sodium/crypto_secretbox.h>
#include <sodium/randombytes.h>
#include <string>

using namespace std;

#define MESSAGE ((const unsigned char *) "test")
#define MESSAGE_LEN 4
#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)

void test(string haslo)
{
    cout << "Hello, szyfrowanie" << endl;        
    if (sodium_init() < 0){
        cout << "Biblioteka sodium nie mogła zostać załadowana" << endl;
        return;
    }

    unsigned char hash[crypto_generichash_BYTES];
    unsigned char key[crypto_generichash_KEYBYTES];
    
    randombytes_buf(key, sizeof key);

    crypto_generichash(hash, sizeof hash, MESSAGE, MESSAGE_LEN, key, sizeof key);

    cout << "Oto wynik hashowania stringa " << haslo << ": " << endl;
    for(size_t i = 0; i < sizeof hash; i++){
        printf("%02x", hash[i]);
    }

    cout << endl;
}   
