run: decrypt.cpp
	g++ -o decrypt decrypt.cpp

decryptText: run
	make run
	./decrypt $(file) decryptText

extractKey: run
	make run
	./decrypt $(file) extractKey

getText: run
	make run
	./decrypt $(file)