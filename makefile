run: decipher_text.cpp
	g++ -o decrypt decipher_text.cpp
	./decrypt $(file)

decryptText: run
	make run
	./decrypt $(file) decryptText

extractKey: run
	make run
	./decrypt $(file) extractKey

clean:
	rm -rf decrypt
