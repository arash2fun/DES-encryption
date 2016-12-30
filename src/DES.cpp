/*
 * DES.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: Arash
 */

#include <iostream>
#include <fstream>
#include <string>

#include "DESblock.h"


using namespace std;

int shell();
int getCommand();
void lowerCase(string & text);
void showHelp();
int encrypt(bool decrypt = 0, bool hexText = 1, bool hexKey = 0, bool file = 0, string inadd = "in.txt", string outadd = "out.txt", string key = "");
string getText(int n = 0);
string toHex(string a);
string des(string text, string key, const bool decrypt = 0);
void showCommandlineHelp();




int main(int argc, char * argv[])
{
	string inputfile = "in.txt", outputfile = "out.txt", key = "";
	bool decrypt = 0, hexText = 0, hexKey = 0;

	if (argc == 1)
	{
		shell();
		return 0;
	}

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg(argv[i]);
			if (arg == "-f" || arg == "-F")
				inputfile = argv[i + 1];
			else if (arg == "-fh" || arg == "-FH")
			{
				inputfile = argv[i + 1];
				hexText = true;
			}
			else if (arg == "-o" || arg == "-O")
				outputfile = argv[i + 1];
			else if (arg == "-k" || arg == "-K")
				key = argv[i + 1];
			else if (arg == "-kh" || arg == "-KH")
			{
				key = argv[i + 1];
				hexKey = true;
			}
			else if (arg == "-e" || arg == "-E")
				decrypt = false;
			else if (arg == "-d" || arg == "-D")
				decrypt = true;
			else if (arg == "help" || arg == "-HELP" || arg == "-help" || arg == "HELP")
			{
				showCommandlineHelp();
				return 0;
			}
		}


		encrypt(decrypt, (decrypt ? true : hexText), hexKey, true, inputfile, outputfile, key);
	}

	return 0;
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

int encrypt(bool decrypt, bool hexText, bool hexKey, bool file, string inadd, string outadd, string key)
{
	string text, answer;

	if (!file)
	{
		int command;
		cout << "\nPlease enter your text to " << (decrypt ? "decrypt" : "encrypt") << "." << endl;
		cout <<"Indicate the end of your text with '~' symbol" << endl;

		text = getText();
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
	} else {

		ifstream infile;
		infile.open(inadd.c_str(), ifstream::in);

		char c;

		while (infile.get(c))
			text.push_back(c);

		infile.close();
	}

	answer = des( (hexText ? text : toHex(text)), (hexKey ? key : toHex(key)), decrypt);



	if (!file)
	{
		cout << "\n" << (decrypt ? "Decrypted" : "Encrypted") << " text : " << endl;
		cout << answer << endl;

		cout << "\nKey :" << endl;
		cout << key << endl;
	}
	else
	{
		ofstream outfile;
		outfile.open(outadd.c_str(), ofstream::out);

		outfile << answer;

		outfile.close();

		cout << "\nKey :" << endl;
		cout << key << endl;
	}

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
	char c;
	string text;

	cout << "\nDES >> ";

	do {
		cin.get(c);
		if (n > 0 && text.size() == (unsigned int)n) return text;
		if (c == '~') return text;
		text.push_back(c);
	} while (c);

	return text;

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


void showCommandlineHelp()
{
	cout << "\nThis program can be used to encrypt/decrypt text files\n\n"
		 << "Available options are :\n\n"
		 << "flag 			  usage                                example\n"
		 << "--------------------------------------------------------------------------\n"
		 << "-f or -F         indicating input text file address   -f input.txt\n"
		 << "-fh or -FH       indicating input hex file address    -fh input.txt\n"
		 << "-k or -K         key for encryption / decryption      -k hello\n"
		 << "-kh or -KH       key in hex form                      -kh 68656c6c6f\n"
		 << "-e or -E         for choosing encryption mode         -e\n"
		 << "-d or -D         for choosing decryption mode         -d\n"
		 << "-o or -O         indicating output file address       -o o.txt\n"
		 << "-help or help    showing help section                 -help\n\n"
		 << "example :\n\n"
		 << "DES -d -f text.txt -o encryptedText.txt -k iAmBest" << endl;

}

void showHelp()
{
	cout << "\nThis program can encrypt/decrypt texts with use of\n"
		 << "DES encryption algorithm.\n\n"
		 << "In order to encrypt/decrtypt texts longer than 500 characters it is recommended,\n"
		 << "use the command line to encrypt/decrypt an entire text file.\n\n"
		 << "The commands available in the program are: \n\n"
		 << "'e' or 'encrypt'        choose encryption\n"
		 << "'d' or 'decrypt'        choose decryption\n"
		 << "'c' or 'cancel'         cancel any chosen action\n"
		 << "'exit'                  exit the program\n"
		 << "'help'                  show help" << endl;
}
