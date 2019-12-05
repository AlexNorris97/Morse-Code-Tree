// Morse-Project-2B.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

struct node {
	char ch;
	node *left;
	node *right;
	node() {
		left = NULL;
		right = NULL;
		ch = 0;
	}
};

class tree {
private:
	node *root;
	void add(node *&temp, string str, char ch) {
		if (temp == NULL) {
			temp = new node();
		}
		if (str.size() == 0) {
			temp->ch = ch;
		}
		else {
			if (str[0] == '.') {
				add(temp->left, str.substr(1), ch);
			}
			else {
				add(temp->right, str.substr(1), ch);
			}
		}
	}
	char get(node *temp, string str) {
		if (temp->ch != 0 && str.size() == 0) {
			return temp->ch;
		}
		else {
			if (str[0] == '.') {
				return get(temp->left, str.substr(1));
			}
			else {
				return get(temp->right, str.substr(1));
			}
		}
	}
public:
	tree() {
		root = NULL;
	}
	void add(string str, char ch) {
		add(root, str, ch);
	};
	char get(string str) {
		return get(root, str);
	}
};

void decode(string morse_text, tree tr);

void encode(string text);

int main() {
	fstream morseCode("morse.txt");
	tree t;
	string str, str2;
	int count = 0;
	if (morseCode.is_open()) {
		// load morse code tree
		while (!morseCode.eof()) {
			morseCode >> str2;
			t.add(str2.substr(1), str2[0]);
		}
		// read character by character
		
		string code = "";
		char inp = ' ';
		string str;

		cout << endl << right << setw(35) << " Decode or Encode? ('d'||'e'): ";
		getline(cin, str);
		inp = str[0];
		inp = toupper(inp);

		while (inp != 'Q') {
			if (inp == 'D') {
				cout << endl << right << setw(35) << "      Enter message to decode: ";
				getline(cin, code);
				decode(code, t);
				cout << endl << right << setw(35) << " Decode or Encode? ('d'||'e'): ";
				getline(cin, str);
				inp = str[0];
				inp = toupper(inp);
			}
			else if (inp == 'E') {
				cout << endl << right << setw(35) << "      Enter message to encode: ";
				getline(cin, code);
				encode(code);
				cout << endl << right << setw(35) << " Decode or Encode? ('d'||'e'): ";
				getline(cin, str);
				inp = str[0];
				inp = toupper(inp);
			}
			else if (inp != 'Q') {
				cout << endl << right << setw(35) <<"input error - enter 'q' to quit: ";
				cout << endl << endl << right << setw(35) << " Decode or Encode? ('d'||'e'): ";
				getline(cin, str);
				inp = str[0];
				inp = toupper(inp);
			}
		}
		morseCode.close();
	}
	else {
		cout << "can not open morse.txt" << endl;
	}
	
	cout << endl;
	system("pause");
	return 0;
}

void decode(string morse_text, tree tr) {
	string str, str2;
	char ch;
	int count = 0;
	for (int i = 0; i < morse_text.size(); ++i) {
		
		ch = morse_text[i];
		if (ch == ' ') {
			if (str != "") {
				str2 = str2 + tr.get(str);
				str = "";
			}
			++count;
			if (count == 3) {
				str2 += " ";
			}
		}
		else if (ch == '.' || ch == '_') {
			str += ch;
			count = 0;

		}
		else {
			cout << endl << right << setw(35) << "input error!" << endl;
			break;
		}
		if (i == morse_text.size() - 1) {
			if (str != "") {
				str2 = str2 + tr.get(str);
				str = "";
			}
			cout << endl << right << setw(35) << " Decoded Message: " << str2 << endl;
		}
	}
	if (str2 == "") {
		cout << endl << right << setw(35) << "decode error!" << endl;
	}
}
void encode(string text) {
	string str;
	for (int i = 0; i < text.size(); ++i) {
		tolower(text[i]);
		switch (text[i])
		{
		case 'a':    str += "._ ";       break;
		case 'b':    str += "_... ";     break;
		case 'c':    str += "_._. ";     break;
		case 'd':    str += "_.. ";      break;
		case 'e':    str += ". ";        break;
		case 'f':    str += ".._. ";     break;
		case 'g':    str += "__. ";      break;
		case 'h':    str += ".... ";     break;
		case 'i':    str += ".. ";       break;
		case 'j':    str += ".___ ";     break;
		case 'k':    str += "_._ ";      break;
		case 'l':    str += "._.. ";     break;
		case 'm':    str += "__ ";       break;
		case 'n':    str += "_. ";       break;
		case 'o':    str += "___ ";      break;
		case 'p':    str += "_._. ";     break;
		case 'q':    str += "__._ ";     break;
		case 'r':    str += "._. ";      break;
		case 's':    str += "... ";      break;
		case 't':    str += "_ ";        break;
		case 'u':    str += ".._ ";      break;
		case 'v':    str += "..._ ";     break;
		case 'w':    str += ".__ ";      break;
		case 'x':    str += "_.._ ";     break;
		case 'y':    str += "_.__ ";     break;
		case 'z':    str += "__.. ";     break;
		case ' ':    str += "  ";		break;
		default:						break;
		}
	}
	cout << endl << right << setw(35) << "Encoded message: " << str << endl;
}