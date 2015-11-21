#include "rsaroutines.h"

word fastModularExponentiation(word number, word power, word modulo)
{
	uint32 result = 1;

	while (power){
		while (!(power % 2)){
			power = power / 2;
			number = (number * number) % modulo;
		}
		power--;
		result = (result * number) % modulo;
	}
	return result;
}

word getMultiplicativeInverse(word number, word modulo)
{
	int x, y;
	euclidExtended(number, modulo, &x, &y);

	return (x % modulo + modulo) % modulo;
}

word euclidExtended(word a, int b, int *x, int *y){
	int x1, y1;
	unsigned short d;
	if (a == 0){
		*x = 0;
		*y = 1;
		return b;
	}

	d = euclidExtended(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return d;
}

bool isPrime(int number)
{
	bool result = true;

	if (number == 2)
		return true;
	if (number == 1)
		return false;

	for (int i = 3; i <= (int)sqrt(number) && result; i += 2){
		result = (number % 2);
	}

	return result;
}

word gcd(word a, word b)
{
	if (!a)
		return b;

	return gcd(b % a, a);
}

void writeDecipheredByte(word out, QFile *outputFile)
{
	char outByte = out & 255;
	outputFile->write(&outByte, 1);
}

void writeCipheredWord(word out, QFile *outputFile)
{
	char firstByte = out & 255;
	char secondByte = out >> 8;

	outputFile->write(&secondByte, 1);
	outputFile->write(&firstByte, 1);
}

word readCipheredWord(QFile *inputFile)
{
	word result;
	inputFile->read(((char *)&result) + 1, 1);
	inputFile->read((char *)&result, 1);
	return result;
}

word readPlaintextByte(QFile *inputFile)
{
	char result;
	inputFile->read(&result, 1);
	return result & 255;
}