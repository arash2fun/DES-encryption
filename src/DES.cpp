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

#include "DESblock.h"

using namespace std;


typedef bool bit;
typedef vector<bit> bits;
typedef string hexadec;





int pow(const int a, const int n)
{
	int b = 1;
	for (int i = 0; i < n; i++)
		b *= a;
	return b;
}

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

bits encrypt(bits text, bits ikey, bool decrypt)
{
	bit subkeys[16][48];

	bit key[64] = {0};
	for (unsigned int i = 0; i < (ikey.size() < 64 ? ikey.size() : 64); i++)
		key[i] = ikey[i];

	DESblock::create_subkeys(subkeys, key);

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
		DESblock::encrypt_block(encrbl, block, subkeys, decrypt);
		for (int f = 0; f < 64; f++)
			encrblv.push_back(encrbl[f]);
		crypted_bits = connect_bits(crypted_bits, encrblv);
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
//  crpt=  "85E813540F0AB405";

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
	cout << "in text : \n" << endl;
	cout << bits_to_char(cryptedb) << endl;


	cout << "\n\nthe key is :" << endl;
	cout << bits_to_hex(keyb) << endl;


/*	char exit;
 	cout << "enter 'x' to exit." << endl;
	while (exit != 'x')
		cin >> exit;
*/
	return 0;
}
