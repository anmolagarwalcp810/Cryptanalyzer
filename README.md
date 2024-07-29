# Basic Cryptanalyzer
This implementation finds out the secret key given any ciphertext and decrypts the given ciphertext to plaintext. The implementation is present in `decipher_text.cpp` file.

[readme.pdf](./readme.pdf) contains thorough analysis behind developing logic to decipher ciphertext based on character and word frequencies, and then ultimately using a dictionary to figure out the ciphertext.

## How to Run
```bash
make file="example_ciphertext.txt"
```

Video explaining logic behind substitution cipher: https://drive.google.com/file/d/1uzuL51jF-0B5WmQTzEkIgxPofIkO8yA4/view?usp=sharing
