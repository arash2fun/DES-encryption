/*
 * DESb.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: Arash
 */

#include <iostream>
#include "DESblock.h"
#include <string>

using namespace std;

int shell();
int getCommand();
void lowerCase(string & text);
void showHelp();
int encrypt(bool decrypt = 0);
string getText(int n = 500);
string toHex(string a);
string des(string text, string key, const bool decrypt = 0);




int main(int argc, char * argv[])
{
	if (argc == 1)
	{
		shell();
		return 0;
	}

}


int shell()
{
	cout << "\n\nWelcome to DES shell \nIf you don't know what to do enter 'help'." << endl;

	int command;
	do
	{
		command = getCommand();

		switch (command)
		{
		case 1:
		case 4:
		case 5:
		case 9:
			cout << "\nError : Invalid input !" << endl;
			cout << command;
			break;
		case 2:
			command = encrypt();
			break;
		case 3:
			command = encrypt(1);
			break;
		case 6:
			showHelp();
			break;
		}
	} while (command);


	cout << "\nExiting.." << endl;
	return 0;

}

int encrypt(bool decrypt)
{
	bool hexText = true, hexKey = false;
	string text, key;
	int command;
	cout << "\nPlease enter your text to " << (decrypt ? "decrypt" : "encrypt") << "." << endl;
	cout << "You can text up to 500 characters. Indicate the end of your text with '~' symbol" << endl;

	text = getText(500);
	cin.ignore(100, '\n');

	cout << "\nYour text is : " << text << endl;

	if (!decrypt)
	{
		cout << "\nPlease specify that either your text is a hex code or just simple text?\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;

		do
		{
			command = getCommand();

			switch (command)
			{
			case 0:
				return 0;
			case 1:
				cout << "\nCanceled.." << endl;
				return 1;
			case 2:
			case 3:
			case 9:
				cout << "\nWrong input!\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;
				continue;
			case 6:
				cout << "\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;
				continue;
			case 5:
				hexText = false;
				break;
			case 4:
				hexText = true;
				break;
			}

			break;
		} while (1);
	}

	cout << "\nPlease specify that either your key is a hex code or just simple text?\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;

	do
	{
		command = getCommand();

		switch (command)
		{
		case 0:
			return 0;
		case 1:
			cout << "\nCanceled.." << endl;
			return 1;
		case 2:
		case 3:
		case 9:
			cout << "\nWrong input!\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;
			continue;
		case 6:
			cout << "\nEnter 'hex' or 'h' for hex code and 'text' or 't' for simple text." << endl;
			continue;
		case 5:
			hexKey = false;
			break;
		case 4:
			hexKey = true;
			break;
		}
		break;
	} while (1);

	cout << "\nPlease enter your key for " << (decrypt ? "decryption" : "encryption") << endl;
	cout << "The key must be " << (hexKey ? 16 : 8) << " characters." << endl;

	key = getText(hexKey ? 16 : 8);
	cin.ignore(100, '\n');

	cout << "\nYour key is : " << key << endl;

	string answer;
	answer = des( (hexText ? text : toHex(text)), (hexKey ? key : toHex(key)), decrypt);

	cout << "\n" << (decrypt ? "Decrypted" : "Encrypted") << " text : " << endl;
	cout << answer << endl;

	cout << "\nKey :" << endl;
	cout << key << endl;

	return 1;
}


string des(string text, string k, const bool decrypt)
{
	bit subkeys[16][48];
	char block[16], pblock[16], key[16];
	string answer;

	for (unsigned int i = 0; i < 16; i++)
	{
		if ((text.size() % 16) != 0) text.push_back('0');
		if ((k.size() % 16) != 0) k.push_back('0');
		key[i] = k[i];
	}

	DESblock::create_subkeys(subkeys, key);


	for (unsigned int i = 0; i < (text.size()/16); i++)
	{
		for (unsigned int j = 0; j < 16; j++)
			block[j] = text[i*16 + j];
		DESblock::encrypt_block(pblock, block, subkeys, decrypt);
		answer.append(pblock, 16);
	}

	return answer;
}


string getText(int n)
{
	char text[500];
	cout << "\nDES >> ";
	cin.get(text, n +1, '~');
	string Text = text;
	return Text;

}


int getCommand()
{
	string command;
	char com[256];
	cout << "\nDES >> ";
	cin.getline(com, 256);
	command = com;

	lowerCase(command);

	if 		(command == "exit") 						return 0;
	else if (command == "cancel" || command == "c")		return 1;
	else if (command == "encrypt" || command == "e") 	return 2;
	else if (command == "decrypt" || command == "d") 	return 3;
	else if (command == "hex" || command == "h") 		return 4;
	else if (command == "text" || command == "t") 		return 5;
	else if (command == "help") 						return 6;

	else 												return 9;
}

string toHex(string a)
{
	string h(a.size() * 2,0);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		h[2 * i] = DESblock::get_char((int)a[i] / 16);
		h[2 * i + 1] = DESblock::get_char((int)a[i] % 16);
	}
	return h;
}

void lowerCase(string& text)
{
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if (text[i] > 64 && text[i] < 91)
			text[i] += 32;
	}
}


void showHelp()
{
	cout << "this is help !!!" << endl;
}
