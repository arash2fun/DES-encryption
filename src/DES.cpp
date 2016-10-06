/*
 * DES.cpp
 *
 *  Created on: Sep 16, 2016
 *      Author: Arash
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>


using namespace std;


typedef bool bit;
typedef vector<bit> bits;
typedef string hexadec;
//typedef vector<int> table;


int _pc1[] = {57, 49, 41, 33, 25, 17, 9,
			 1, 58, 50, 42, 34, 26, 18,
			 10, 2, 59, 51, 43, 35, 27,
			 19, 11, 3, 60, 52, 44, 36,
			 63, 55, 47, 39, 31, 23, 15,
			 7, 62, 54, 46, 38, 30, 22,
			 14, 6, 61, 53, 45, 37, 29,
			 21, 13, 5, 28, 20, 12, 4};


int _pc2[] = {14, 17, 11, 24, 1, 5,
			3, 28, 15, 6, 21, 10,
			23, 19, 12, 4, 26, 8,
			16, 7, 27, 20, 13, 2,
			41, 52, 31, 37, 47, 55,
			30, 40, 51, 45, 33, 48,
			44, 49, 39, 56, 34, 53,
			46, 42, 50, 36, 29, 32};

int _IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
			 60, 52, 44, 36, 28, 20, 12, 4,
			 62, 54, 46, 38, 30, 22, 14, 6,
			 64, 56, 48, 40, 32, 24, 16, 8,
			 57, 49, 41, 33, 25, 17, 9, 1,
			 59, 51, 43, 35, 27, 19, 11, 3,
			 61, 53, 45, 37, 29, 21, 13, 5,
			 63, 55, 47, 39, 31, 23, 15, 7};


int _FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
			 39, 7, 47, 15, 55, 23, 63, 31,
			 38, 6, 46, 14, 54, 22, 62, 30,
			 37, 5, 45, 13, 53, 21, 61, 29,
			 36, 4, 44, 12, 52, 20, 60, 28,
			 35, 3, 43, 11, 51, 19, 59, 27,
			 34, 2, 42, 10, 50, 18, 58, 26,
			 33, 1, 41, 9,  49, 17, 57, 25};


int num_left_shift[] = {1, 1, 2, 2,
						2, 2, 2, 2,
						1, 2, 2, 2,
						2, 2, 2, 1};


int _E[] = {32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13,
			12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21,
			20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29,
			28, 29, 30, 31, 32, 1};


int sbox[8][4][16] = {
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

int _P[] = {16, 7, 20, 21,
			29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10,
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25};



//=================================



void shift_buffer(string& buf)
{
	int s = buf.size();
	for (int i = 0; i < s; i++)
	{
		if (i < (s - 1))
			buf[i] = buf[i + 1];
		else
			buf[i] = 'f';
	}
}

void clear_text(string& text)
{
	text = text.erase(0, 1);
}

string get_text()
{
	string buffer = "ccc";
	string text = "";

	while (buffer != "xxx")
	{
		char c = cin.get();
		text += c;
		shift_buffer(buffer);
		buffer[2] = c;
	}
	text = text.erase(text.size() - 3, 3);

//	clear_text(text);

	return text;
}

void dec_to_bits_k(bit bits[4], int d)
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

bits dec_to_bits(int d)
{
	bits bits(4, 0);

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
	return bits;
}

bits connect_bits(bits f, bits b)
{
	bits a = f;
	for (unsigned int i = 0; i < b.size(); i++)
		a.push_back(b[i]);
	return a;
}

void connect_bits(bit res[], const bit c[], const bit d[], int size)
{
	for (int i = 0; i < size; i++)
	{
		res[i] = c[i];
		res[i + size] = d[i];
	}
}

void print_bits(const bits bits)
{
	for (unsigned int i = 0; i < bits.size(); i++)
		cout << bits[i];
	cout << endl;
}

void print_bits(const bit bits[], const int size = 64)
{
	for (int i = 0; i < size; i++)
		cout << bits[i];
	cout << endl;
}

char get_hex(int a)
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

int get_dec(char h)
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
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		return 0;

	}

}

hexadec char_to_hex(string a)
{
	hexadec h(a.size() * 2,0);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		h[2 * i] = get_hex((int)a[i] / 16);
		h[2 * i + 1] = get_hex((int)a[i] % 16);
	}
	return h;
}

bits char_to_bits(string a)
{
	bits bits(8 * a.size(), 0);

	for (unsigned int j = 0; j < a.size(); j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (a[j] >= 2)
			{
				bits[8 * j + 7 - i] = a[j] % 2;
				a[j] /= 2;
			}
			else
			{
				bits[8 * j + 7 - i] = a[j];
				break;
			}
		}
	}
	return bits;
}

string bits_to_char(bits bits)
{
	string a = "";
	for (unsigned int i = 0; i <= ((bits.size() - 1) / 8); i++)
	{
		char temp = 0;
		for (int j = 0; j < 8; j++)
		{
			if (bits[i * 8  + j])
				temp += pow(2, 7 - j);
		}
		a.push_back(temp);
	}

	return a;
}

bits hex_to_bits(string h)
{
	bits b(0);

	for (unsigned int i = 0; i < h.size(); i++)
	{
		b = connect_bits(b, dec_to_bits(get_dec(h[i])));
	}

	return b;
}

int bits_to_dec(bits b)
{
	int d = 0;

	for (unsigned int i = 0; i < b.size(); i++)
		if (b[i])
			d += pow(2, b.size() - (i + 1));
	return d;
}

int bits_to_dec(bit b[], int size)
{
	int d = 0;

	for (int i = 0; i < size; i++)
		if (b[i])
			d += pow(2, size - (i + 1));
	return d;
}

hexadec bits_to_hex(bits b)
{
	hexadec h = "";

	for (unsigned int i = 0; i <= ((b.size() - 1) / 4); i++)
	{
		int temp = 0;
		bits btemp;
		for (int j = 0; j < 4; j++)
			btemp.push_back(b[4 * i + j]);
		temp = bits_to_dec(btemp);
		h.push_back(get_hex(temp));

	}

	return h;
}

/*
void fill_table(table& a, int b[], int n)
{
	for (int i = 0; i < n; i++)
		a.push_back(b[i]);
}
*/


void permute(bit pb[], const bit b[], const int t[], const int size)
{
	for (int i = 0; i < size; i++)
	{

		pb[i] = b[t[i]-1];
	}
}

void shift_left(bit a[],const bit b[], unsigned int n)
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

void create_subkeys(bit subkeys[16][48], bits ikey)
{

	bit key[64] = {0};
	for (unsigned int i = 0; i < (ikey.size() < 64 ? ikey.size() : 64); i++)
		key[i] = ikey[i];



	bit pkey[56];
	permute(pkey, key, _pc1, 56);

	bit C[17][28];
	bit D[17][28];


//	print_bits(key, 64);
//	print_bits(pkey, 56);

	for (unsigned int i = 0; i < 28; i++)
	{
		C[0][i] = pkey[i];
		D[0][i] = pkey[i + 28];
	}

	bit CD[16][56];

	for (int i = 0; i < 16; i++)
	{
		shift_left(C[i + 1], C[i], num_left_shift[i]);
		shift_left(D[i + 1], D[i], num_left_shift[i]);
		connect_bits(CD[i], C[i + 1], D[i + 1], 28);

/*		cout << "C" << i << ": ";
		print_bits(C[i+1], 28);
		cout << "D" << i << ": ";
		print_bits(D[i+1], 28);
		cout << "CD" << i << ": ";
		print_bits(CD[i], 56);
*/
		permute(subkeys[i], CD[i], _pc2, 48);

//		cout << "K" << i+1 << ": ";
//		print_bits(subkeys[i], 48);
	}
}

void feistel(bit pout[], const bit Rn[], const bit Kn[])
{
	bit Er[48];
//
//	cout << "R : ";
//	print_bits(Rn, 32);


	permute(Er, Rn, _E, 48);
	bit Kr[48];

//	cout << "ER: ";
//	print_bits(Er, 48);
//
//
//	cout << "Kn: ";
//	print_bits(Kn, 48);


	for (int i = 0; i < 48; i++)
	{
		Kr[i] = (Er[i] ^ Kn[i]);
	}
//
//	cout << "ER: ";
//	print_bits(Er, 48);
//
//
//	cout << "Kr: ";
//	print_bits(Kr, 48);
//	cout << "\n";

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
		dec_to_bits_k(sout, sbox[i][row][col]);
		for (int j = 0; j < 4; j++)
			out[4 * i + j] = sout[j];

	}
//
//	cout << "O : ";
//	print_bits(out, 32);

	permute(pout, out, _P, 32);

//
//	cout << "F : ";
//	print_bits(pout, 32);
}

void encrypt_block(bit pcrypted[64], bit block[64],bit subkeys[16][48], bool decrypt = 0)
{
	bit pblock[64];
	permute(pblock, block, _IP, 64);


//	cout << "M : ";
//	print_bits(block);
//	cout << "IP: ";
//	print_bits(pblock);

	bit L[17][32] = {0};
	bit R[17][32] = {0};

	for (unsigned int i = 0; i < 32; i ++)
	{
		L[0][i] = pblock[i];
		R[0][i] = pblock[i + 32];
	}

/*	table E;
	fill_table(E, _E, 48);

	table P;
	fill_table(P, _P, 32);
*/
	bit crypted_block[64];

	for (int i = 0; i < 16; i++)             // ***********************16*************
	{
		bit temp[32];
		if (decrypt)
			feistel(temp, R[i], subkeys[15 - i]);
		else
			feistel(temp, R[i], subkeys[i]);

//		print_bits(temp, 32);

		for (int j = 0; j < 32; j++)
		{
			L[i + 1][j] = R[i][j];
			R[i + 1][j] = (L[i][j] ^ temp[j]);
		}
	}
//
//	for (int i = 0; i < 17; i++)
//	{
//		cout << "L" << i << ": ";
//		print_bits(L[i], 32);
//		cout << "R" << i << ": ";
//		print_bits(R[i], 32);
//	}

	connect_bits(crypted_block, R[16], L[16], 32);

	permute(pcrypted, crypted_block, _FP, 64);
}

bits encrypt(bits text, bits key, bool decrypt = 0)
{
	bit subkeys[16][48];
	create_subkeys(subkeys, key);

/*	table IP;
	fill_table(IP, _ip, 64);

	table FP;
	fill_table(FP, _fp, 64);
*/
	bits crypted_bits;

	for (unsigned int i = 0; i <= ((text.size() - 1)/64); i++)
	{
		bit block[64] = {0};
		for (int j = 0; j < 64; j++)
		{
			unsigned int d = i * 64 + j;
			if (d < text.size())
				block[j] = text[d];
			else
				break;
		}
		bits encrblv;
		bit encrbl[64];
		encrypt_block(encrbl, block, subkeys, decrypt);
		for (int f = 0; f < 64; f++)
			encrblv.push_back(encrbl[f]);
		crypted_bits = connect_bits(crypted_bits, encrblv);

//		print_bits(text);
	}



	return crypted_bits;
}

void welcome(bool& decrypt, bool& htext)
{
	cout << "#####   WELCOME !   #####" << endl;
	cout << "please choose the operation : " << endl;
	cout << "enter 'e' for encryption and 'd' for decryption." << endl;
	char c;
	while ((c != 'e') && (c != 'E') && (c != 'd') && (c != 'D'))
		cin >> c;

	if ((c == 'e') || (c == 'E'))
	{
		cout << "Encryption chosen. " << endl;
		decrypt = 0;
	}
	else
	{
		cout << "Decryption chosen." << endl;
		decrypt = 1;
	}
	if (!decrypt)
	{
		cout << "please choose the type of your text." << endl;
		cout << "enter 'h' for hex code and 't' for plain text." << endl;

		while ((c != 'h') && (c != 'H') && (c != 't') && (c != 'T'))
			cin >> c;

		if ((c == 'h') || (c == 'H'))
		{
			cout << "HEX code chosen. " << endl;
			htext = 1;
		}
		else
		{
			cout << "plain text chosen." << endl;
			htext = 0;
		}
	}
	else
		htext = true;

	cout << "\n\n";
}

int main ()
{
	bool decrypt = 0;
	bool htext = 1;
	welcome(decrypt, htext);

	string text = "";
	string key = "";

	bits textb;
	bits keyb;

	cout << "please enter the " << (htext ? "HEX code" : "text") << " to " << ((decrypt) ? "decrypt : " : "encrypt : ") << endl;
	cout << "enter 'xxx' to indicate the end of your text." << endl;

	text = get_text();

	if (text == "") text = "   ";

	cout << "please enter a key : " << endl;
	key = get_text();
	clear_text(text);
	clear_text(key);

//	text = "0123456789ABCDEF";
//	key =  "133457799BBCDFF1";


	if (htext)
	{
		textb = hex_to_bits(text);
		keyb = hex_to_bits(key);
	}
	else
	{
		textb = char_to_bits(text);
		keyb = char_to_bits(key);
	}

	bits cryptedb = encrypt(textb, keyb, decrypt);

	cout << "your text :" << endl;
	cout << text << endl;
	cout << (decrypt ? "decrypted" : "encrypted") << " text is :" << endl;
	cout << "in HEX : " << endl;
	cout << bits_to_hex(cryptedb) << endl;
//	cout << "in text : \n" << endl;
//	cout << bits_to_char(cryptedb) << endl;


	cout << "\n\nthe key is :" << endl;
	cout << bits_to_hex(keyb) << endl;
	cout << "enter 'x' to exit." << endl;

/*	char exit;
	while (exit != 'x')
		cin >> exit;
*/
	return 0;
}
