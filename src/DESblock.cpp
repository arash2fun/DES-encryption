/*
 * DESblock.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Arash
 */

#include "DESblock.h"

const char DESblock::_PC1[] = {57, 49, 41, 33, 25, 17, 9,
		 1, 58, 50, 42, 34, 26, 18,
		 10, 2, 59, 51, 43, 35, 27,
		 19, 11, 3, 60, 52, 44, 36,
		 63, 55, 47, 39, 31, 23, 15,
		 7, 62, 54, 46, 38, 30, 22,
		 14, 6, 61, 53, 45, 37, 29,
		 21, 13, 5, 28, 20, 12, 4};

const char DESblock::_PC2[] = {14, 17, 11, 24, 1, 5,
			3, 28, 15, 6, 21, 10,
			23, 19, 12, 4, 26, 8,
			16, 7, 27, 20, 13, 2,
			41, 52, 31, 37, 47, 55,
			30, 40, 51, 45, 33, 48,
			44, 49, 39, 56, 34, 53,
			46, 42, 50, 36, 29, 32};

const char DESblock::_IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
			 60, 52, 44, 36, 28, 20, 12, 4,
			 62, 54, 46, 38, 30, 22, 14, 6,
			 64, 56, 48, 40, 32, 24, 16, 8,
			 57, 49, 41, 33, 25, 17, 9, 1,
			 59, 51, 43, 35, 27, 19, 11, 3,
			 61, 53, 45, 37, 29, 21, 13, 5,
			 63, 55, 47, 39, 31, 23, 15, 7};

const char DESblock::_FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
			 39, 7, 47, 15, 55, 23, 63, 31,
			 38, 6, 46, 14, 54, 22, 62, 30,
			 37, 5, 45, 13, 53, 21, 61, 29,
			 36, 4, 44, 12, 52, 20, 60, 28,
			 35, 3, 43, 11, 51, 19, 59, 27,
			 34, 2, 42, 10, 50, 18, 58, 26,
			 33, 1, 41, 9,  49, 17, 57, 25};

const char DESblock::_LEFT_SHIFT[] = {1, 1, 2, 2,
						2, 2, 2, 2,
						1, 2, 2, 2,
						2, 2, 2, 1};

const char DESblock::_E[] = {32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13,
			12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21,
			20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29,
			28, 29, 30, 31, 32, 1};

const char DESblock::_SBOX[8][4][16] = {
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

const char DESblock::_P[] = {16, 7, 20, 21,
			29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10,
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25};

char DESblock::get_char(const int & a)
{
	switch (a)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'A';
	case 11:
		return 'B';
	case 12:
		return 'C';
	case 13:
		return 'D';
	case 14:
		return 'E';
	case 15:
		return 'F';
	default:
		return ' ';
	}
}

int DESblock::get_dec(const char & h)
{
	switch (h)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
	case 'a':
		return 10;
	case 'B':
	case 'b':
		return 11;
	case 'C':
	case 'c':
		return 12;
	case 'D':
	case 'd':
		return 13;
	case 'E':
	case 'e':
		return 14;
	case 'F':
	case 'f':
		return 15;
	default:
		return 0;
	}
}

int DESblock::pow(const int & a, const int & n)
{
	int b = 1;
	for (int i = 0; i < n; i++)
		b *= a;
	return b;
}

DESblock::bits DESblock::dec_to_bits(const char & dec, const int & n)
{
	int d = dec;
	bits out(n);
	for (int i = 0; i < n; i++)
	{
		if (d >= 2)
		{
			out[n - 1 - i] = d % 2;
			d /= 2;
		}
		else
		{
			out[n - 1 - i] = d;
			return out;
		}
	}
	return out;
}

unsigned int DESblock::bits_to_dec(const bits & b)
{
	unsigned int d = 0;

	for (int i = 0; i < b.length(); i++)
		if (b[i])
			d += pow(2, b.length() - (i + 1));
	return d;
}

DESblock::bits DESblock::permute(const bits & b, const char t[], const int & size)
{
	bits a(size);
	for (int i = 0; i < size; i++)
		a[i] = b[t[i] - 1];
	return a;
}

DESblock::bits DESblock::shift_left(bits b, const int & n)
{
	for (int i = 0; i < n; i++)
		b.append(b[0]);
	return b;
}

DESblock::bits DESblock::create_bits(const char text[], const int & n)
{
	bits a(n);
	for (int i = 0; i < a.size(); i ++)
		a.listAssign(i, get_dec(text[2 * i]) * 16 + get_dec(text[2 * i + 1]));
	return a;
}

void DESblock::create_hex(char text[], const bits & b)
{
	for (int i = 0; i < b.size(); i++)
	{
		text[2 * i] = DESblock::get_char(b.list(i) / 16);
		text[2 * i + 1] = DESblock::get_char(b.list(i) % 16);
	}
}

void DESblock::create_subkeys(bits subkeys[16], const bits & key)
{
	bits pb = DESblock::permute(key, _PC1, 56);

	bits C[17] = bits(28);
	bits D[17] = bits(28);

	for (int i = 0; i < 28; i++)
	{
		C[0][i] = pb[i];
		D[0][i] = pb[i + 28];
	}

	bits CD[16] = bits(56);

	for (int i = 0; i < 16; i++)
	{
		C[i + 1] = DESblock::shift_left(C[i], _LEFT_SHIFT[i]);
		D[i + 1] = DESblock::shift_left(D[i], _LEFT_SHIFT[i]);

		for (int j = 0; j < 28; j++)
		{
			CD[i][j] = C[i + 1][j];
			CD[i][j + 28] = D[i + 1][j];
		}
		subkeys[i] = DESblock::permute(CD[i], _PC2, 48);
	}
}

DESblock::bits DESblock::feistel(const bits & Rn, const bits & Kn)
{
	bits Er = permute(Rn, _E, 48);
	bits Kr(48);

	for (int i = 0; i < 48; i++)
		Kr[i] = (Er[i] ^ Kn[i]);

	bits out(32), rowb(2), colb(4);
	int col, row;

	for (int i = 0; i < 8; i++)
	{
		rowb[0] = Kr[6 * i];
		rowb[1] = Kr[6 * i + 5];
		row = bits_to_dec(rowb);
		for (int j = 0; j < 4; j++)
			colb[j] = Kr[6 * i + j + 1];
		col = bits_to_dec(colb);

		bits sout = dec_to_bits(_SBOX[i][row][col]);
		for (int j = 0; j < 4; j++)
			out[4 * i + j] = sout[j];
	}
	return permute(out, _P, 32);
}

void DESblock::encrypt_block(char crypted[], char text[], char key[], const bool & decrypt)
{
	bits subkeys[16] = bits(48);
	bits bkey = create_bits(key);

	create_subkeys(subkeys, bkey);

	bits block = create_bits(text);
	block = permute(block, _IP, 64);

	bits L[17] = bits(32);
	bits R[17] = bits(32);

	for (int i = 0; i < 32; i++)
	{
		L[0][i] = block[i];
		R[0][i] = block[i + 32];
	}

	bits cryptedBlock(64);

	for (int i = 0; i < 16; i++)
	{
		bits temp(32);
		if (decrypt)
			temp = feistel(R[i], subkeys[15 - i]);
		else
			temp = feistel(R[i], subkeys[i]);

		for (int j = 0; j < 32; j++)
		{
			L[i + 1][j] = R[i][j];
			R[i + 1][j] = (L[i][j] ^ temp[j]);
			if (i == 15)
			{
				cryptedBlock[j] = R[16][j];
				cryptedBlock[j + 32] = L[16][j];
			}
		}
	}

	cryptedBlock = permute(cryptedBlock, _FP, 64);

	create_hex(crypted, cryptedBlock);
}

//**************************************************************************************

bool DESblock::bits::read(const int & digit) const
{
	if (digit > _length) return 0;
	unsigned char byte =  digit / 8;
	unsigned char bitInByte = digit % 8;
	return *_list[byte] >> ( 7 - bitInByte ) & 1;
}

void DESblock::bits::assign(const int & pos, const bool & b)
{
	if (pos >= 0 && pos < _length)
	{
		int byte = pos / 8;
		unsigned char bit = pos % 8;
		unsigned char val = b << (7 - bit);
		unsigned char cleaner = ~ (1 << (7 - bit));
		*_list[byte] &= cleaner;
		*_list[byte] |= val;
	}
}

DESblock::bits::bits(const bits & a)
{
	_length = a.length();
	_size = a.size();
	_list = new unsigned char * [_length];
	for (int i = 0; i < _size; i++)
	{
		_list[i] = new unsigned char;
		*_list[i] = *a._list[i];
	}
}

DESblock::bits::~bits()
{
	for (int i = 0; i < _size; i++)
		delete _list[i];
	delete _list;
}
void DESblock::bits::append(const bool & b)
{
	unsigned char bit = b << (_length % 8 == 0 ? 0 : (8 - _length % 8) );
	for (int i = 0; i < (_size - 1)  ; i++)
	{
		unsigned char temp =  *_list[i + 1] >> 7 & 1;
		*_list[i] = *_list[i] << 1 | temp;
	}
	*_list[_size - 1] = (*_list[_size - 1] << 1) | bit;
}

DESblock::bits & DESblock::bits::operator =(const bits & rhs)
{
	if (this != &rhs)
	{
		this->~bits();
		_length = rhs.length();
		_size = rhs.size();
		_list = new unsigned char * [_length];
		for (int i = 0; i < _size; i++)
		{
			_list[i] = new unsigned char;
			*_list[i] = rhs.list(i);
		}
	}
	return *this;
}

DESblock::bits::bits(const int & a, const bool & allTrue)
{
	_length = a;
	_size = a / 8 + (a % 8 == 0 ? 0 : 1);
	_list = new unsigned char * [_length];
	for (int i = 0; i < _size; i++)
	{
		_list[i] = new unsigned char;
		*_list[i] = (allTrue ? 255 : 0);
	}
	if (allTrue)
		for (int i = _length; i < _size * 8; i ++)
			*_list[_size - 1] <<= 1;
}

