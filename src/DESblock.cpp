/*
 * DESblock.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Arash
 */

#include "DESblock.h"

const int DESblock::PC1[] = {57, 49, 41, 33, 25, 17, 9,
		 1, 58, 50, 42, 34, 26, 18,
		 10, 2, 59, 51, 43, 35, 27,
		 19, 11, 3, 60, 52, 44, 36,
		 63, 55, 47, 39, 31, 23, 15,
		 7, 62, 54, 46, 38, 30, 22,
		 14, 6, 61, 53, 45, 37, 29,
		 21, 13, 5, 28, 20, 12, 4};

const int DESblock::PC2[] = {14, 17, 11, 24, 1, 5,
			3, 28, 15, 6, 21, 10,
			23, 19, 12, 4, 26, 8,
			16, 7, 27, 20, 13, 2,
			41, 52, 31, 37, 47, 55,
			30, 40, 51, 45, 33, 48,
			44, 49, 39, 56, 34, 53,
			46, 42, 50, 36, 29, 32};

const int DESblock::IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
			 60, 52, 44, 36, 28, 20, 12, 4,
			 62, 54, 46, 38, 30, 22, 14, 6,
			 64, 56, 48, 40, 32, 24, 16, 8,
			 57, 49, 41, 33, 25, 17, 9, 1,
			 59, 51, 43, 35, 27, 19, 11, 3,
			 61, 53, 45, 37, 29, 21, 13, 5,
			 63, 55, 47, 39, 31, 23, 15, 7};


const int DESblock::FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
			 39, 7, 47, 15, 55, 23, 63, 31,
			 38, 6, 46, 14, 54, 22, 62, 30,
			 37, 5, 45, 13, 53, 21, 61, 29,
			 36, 4, 44, 12, 52, 20, 60, 28,
			 35, 3, 43, 11, 51, 19, 59, 27,
			 34, 2, 42, 10, 50, 18, 58, 26,
			 33, 1, 41, 9,  49, 17, 57, 25};


const int DESblock::LEFT_SHIFT[] = {1, 1, 2, 2,
						2, 2, 2, 2,
						1, 2, 2, 2,
						2, 2, 2, 1};


const int DESblock::E[] = {32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13,
			12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21,
			20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29,
			28, 29, 30, 31, 32, 1};


const int DESblock::SBOX[8][4][16] = {
					 {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
					  {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
					  {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
					  {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

					{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
					 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
					 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
					 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

					{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
					 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
					 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
					 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

					{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
					 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
					 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
					 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

					{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
					 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
					 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
					 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

					{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
					 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
					 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
					 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

					{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
					 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
					 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
					 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

					{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
					 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
					 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
					 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
					 };

const int DESblock::P[] = {16, 7, 20, 21,
			29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10,
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25};

int DESblock::pow(const int a, const int n)
{
	int b = 1;
	for (int i = 0; i < n; i++)
		b *= a;
	return b;
}

void DESblock::dec_to_bits(bit bits[4], int d)
{
	for (int i = 0; i < 4; i++)
	{
		if (d >= 2)
		{
			bits[3 - i] = d % 2;
			d /= 2;
		}
		else
		{
			bits[3 - i] = d;
			break;
		}
	}
}

int DESblock::bits_to_dec(bit b[], int size)
{
	int d = 0;

	for (int i = 0; i < size; i++)
		if (b[i])
			d += pow(2, size - (i + 1));
	return d;
}

void DESblock::connect_bits(bit res[], const bit c[], const bit d[], int size)
{
	for (int i = 0; i < size; i++)
	{
		res[i] = c[i];
		res[i + size] = d[i];
	}
}

void DESblock::permute(bit pb[], const bit b[], const int t[], const int size)
{
	for (int i = 0; i < size; i++)
	{

		pb[i] = b[t[i]-1];
	}
}

void DESblock::shift_left(bit a[],const bit b[], unsigned int n)
{
	bit temp[n] = {0};

	for (unsigned int i = 0; i < 28; i++)
	{
		if (i < n)
			temp[i] = b[i];

		if (i >= (28 - n))
			a[i] = temp[i - (28 - n)];
		else
			a[i] = b[i + n];
	}
}

void DESblock::create_subkeys(bit subkeys[16][48], bit key[64])
{

	bit pkey[56];
	DESblock::permute(pkey, key, PC1, 56);

	bit C[17][28];
	bit D[17][28];


	for (unsigned int i = 0; i < 28; i++)
	{
		C[0][i] = pkey[i];
		D[0][i] = pkey[i + 28];
	}

	bit CD[16][56];

	for (int i = 0; i < 16; i++)
	{
		shift_left(C[i + 1], C[i], LEFT_SHIFT[i]);
		shift_left(D[i + 1], D[i], LEFT_SHIFT[i]);
		connect_bits(CD[i], C[i + 1], D[i + 1], 28);

		permute(subkeys[i], CD[i], PC2, 48);
	}
}

void DESblock::feistel(bit pout[], const bit Rn[], const bit Kn[])
{
	bit Er[48];

	permute(Er, Rn, E, 48);
	bit Kr[48];


	for (int i = 0; i < 48; i++)
	{
		Kr[i] = (Er[i] ^ Kn[i]);
	}

	bit out[32], rowb[2], colb[4];
	int col, row;

	for (int i = 0; i < 8; i++)
	{
		rowb[0] = Kr[6 * i];
		rowb[1] = Kr[6 * i + 5];
		row = bits_to_dec(rowb, 2);
		for (int j = 0; j < 4; j++)
			colb[j] = Kr[6 * i + j + 1];
		col = bits_to_dec(colb, 4);

		bit sout[4] = {0};
		dec_to_bits(sout, SBOX[i][row][col]);
		for (int j = 0; j < 4; j++)
			out[4 * i + j] = sout[j];

	}

	permute(pout, out, P, 32);
}

void DESblock::encrypt_block(bit pcrypted[64], bit block[64],bit subkeys[16][48], bool decrypt)
{
	bit pblock[64];
	permute(pblock, block, IP, 64);

	bit L[17][32] = {0};
	bit R[17][32] = {0};

	for (unsigned int i = 0; i < 32; i ++)
	{
		L[0][i] = pblock[i];
		R[0][i] = pblock[i + 32];
	}

	bit crypted_block[64];

	for (int i = 0; i < 16; i++)
	{
		bit temp[32];
		if (decrypt)
			feistel(temp, R[i], subkeys[15 - i]);
		else
			feistel(temp, R[i], subkeys[i]);


		for (int j = 0; j < 32; j++)
		{
			L[i + 1][j] = R[i][j];
			R[i + 1][j] = (L[i][j] ^ temp[j]);
		}
	}
	connect_bits(crypted_block, R[16], L[16], 32);

	permute(pcrypted, crypted_block, FP, 64);
}






