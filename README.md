# Basic Cryptanalyzer
This implementation finds out the secret key given any ciphertext and decrypts the given ciphertext to plaintext. The implementation is present in `decipher_text.cpp` file.

[readme.pdf](./readme.pdf) contains thorough analysis behind developing logic to decipher ciphertext based on character and word frequencies, and then ultimately using a dictionary to figure out the ciphertext.

## How to Run
```bash
make file="example_ciphertext.txt"
```
