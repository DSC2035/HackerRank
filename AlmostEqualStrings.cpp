#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//From Contest: https://www.hackerrank.com/contests/code-cpp-may-2015/challenges/almost-equal-strings/problem

int N;
string str;
int qNum;
int ival, jval, kval, lval;

void CheckQueries();

using BitArrayType = unsigned long long;

BitArrayType* bitArray;

constexpr int TypeSize = sizeof(BitArrayType);
constexpr int TypeSizeInBits = sizeof(BitArrayType) * 8;
constexpr BitArrayType mask1 = BitArrayType{ 0 } -1;

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */


	cin >> N;


	char ch;
	int ArraySize = N / TypeSizeInBits + 1;
	bitArray = new BitArrayType[ArraySize];

	for (int i = 0; i < ArraySize; i++)
	{
		bitArray[i] = 0;
	}

	for (int i = 0; i < N; i++)
	{
		int index = i / TypeSizeInBits;
		cin >> ch;
		if (ch == 'b')
		{
			BitArrayType flag = (BitArrayType{ 1 } << i%TypeSizeInBits);
			bitArray[index] += flag;
		}

	}//*/


	cin >> qNum;

	for (int loop = 0; loop<qNum; loop++)
	{
		cin >> ival >> jval >> lval >> kval;
		--ival; --jval; --lval; --kval;

		CheckQueries();
	}
	return 0;
}

void CheckQueries()
{
	BitArrayType w1, w2;
	int diff = 0;

	int icounter{ ival }, lcounter{ lval };

	int modulus_i = icounter % TypeSizeInBits;
	int restmodulus_i = (TypeSizeInBits - modulus_i);

	int modulus_l = lcounter % TypeSizeInBits;
	int restmodulus_l = (TypeSizeInBits - modulus_l);


	while (icounter <= jval)
	{
		w1 = 0; w2 = 0;
		int index_i = icounter / TypeSizeInBits;
		if ((jval / TypeSizeInBits) == index_i)
		{
			//both inices in one word
			BitArrayType mask = (mask1 << modulus_i)&(mask1 >> (TypeSizeInBits - jval%TypeSizeInBits - 1));

			w1 = (bitArray[index_i] & mask) >> modulus_i;

		}
		else
		{
			w1 += (bitArray[index_i] >> modulus_i);
			if ((jval - icounter) > TypeSizeInBits)
			{
				w1 += (bitArray[index_i + 1] << restmodulus_i);
			}
			else
			{
				w1 += ((bitArray[jval / TypeSizeInBits] & (mask1 - (mask1 << (jval%TypeSizeInBits + 1)))) << restmodulus_i);
			}
		}

		int index_l = lcounter / TypeSizeInBits;
		if ((kval / TypeSizeInBits) == index_l)
		{
			//both inices in one word
			BitArrayType mask = (mask1 << modulus_l)&(mask1 >> (TypeSizeInBits - kval%TypeSizeInBits - 1));


			w2 = (bitArray[index_l] & mask) >> modulus_l;

		}
		else
		{

			w2 += (bitArray[index_l] >> modulus_l);
			if ((kval - lcounter) > TypeSizeInBits)
			{
				w2 += (bitArray[index_l + 1] << restmodulus_l);
			}
			else
			{
				w2 += ((bitArray[kval / TypeSizeInBits] & (mask1 - (mask1 << (kval%TypeSizeInBits + 1)))) << restmodulus_l);
			}
		}


		BitArrayType xordiff = w1^w2;

		if (xordiff != 0)
		{
			if (!(xordiff&(xordiff - BitArrayType{ 1 })))
			{
				//difference in one symbol
				diff++;
				if (diff>1)
				{
					cout << "DIFFERENT" << '\n';
					return;
				}
			}
			else
			{
				//difference in more than two symbols
				cout << "DIFFERENT" << '\n';
				return;

			}
		}


		icounter += TypeSizeInBits;
		lcounter += TypeSizeInBits;
	}
	//compare by formed words
	cout << "SIMILAR" << '\n';
	return;
}