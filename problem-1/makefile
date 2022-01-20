run: decipher_text.cpp
	g++ -o decrypt decipher_text.cpp

decryptText: run
	make run
	./decrypt $(file) decryptText

extractKey: run
	make run
	./decrypt $(file) extractKey

decrypt: run
	make run
	./decrypt $(file)

clean:
	rm -rf decrypt
