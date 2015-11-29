#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <queue>

const int DL = 20;          // ������������ �����

using namespace std;

struct Tree {
	char name[DL];
	int select = 0, countBranch;
	int urov;
	Tree *fath;         // ���� � �������� ������
	Tree *left;
	Tree *right;
};

struct file {
	string path[DL];
	vector<string> allPath;
	string pathFac[DL];
	vector<string> allPathFac;
	int count = 0;
};

void read_from_file(string nameFile, Tree **r) {
	ifstream f(nameFile);
	if (!f.is_open()) {
		cout << "Error open file" << endl;
		system("pause");
		exit(1);
	}
	char buf[DL];
	int i;
	int k;
	int m;
	int len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // ������� �������
	t = 0;
	while (!f.eof())
	{
		f.getline(buf, DL);
		len = strlen(buf);
		if (len == 0)
			break;            // ���� ����� ����� � ��������� ������
		k = 0;
		while (buf[k] == '.')
			k++;     // k-������� �������
		p = new Tree;
		strncpy(p->name, &buf[k], len - k + 1);  // 0-(k-1) - �����, (k-1)-(len-1) - ���, \0 - ����� ������
		buf[0] = '\0';                  // ���� ����� ����� � ��������� ������
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // ������
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // ������� �� ��������� �������
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // ��� �� �������
		{
			t->right = p;
			p->fath = t->fath;  // ���� ��� ��
		}
		else        // ������ �� ������ �� m-k �������
		{
			q = t;
			for (i = 0; i < m - k; i++)
				q = q->fath;
			// q - ���������� ������� ���� �� ������
			p->fath = q->fath;   // ���� ��� ��, ��� � �����
			q->right = p;
		}
		m = k;      // ������� �������
		t = p;      // ������� �������
	}
	f.close();
}

void back_from_bin(Tree *p){
	int i, j;
	char st[DL];
	if (p){
		for (i = 0; i < p->urov; i++) st[i] = '.';
		j = 0;
		while ((p->name)[j] != 0) st[i++] = (p->name)[j++];
		st[i] = '\0';
		printf("%s\n", st);
		back_from_bin(p->left);
		back_from_bin(p->right);
	}
}

void write_menu() {
	cout << "����:" << "\n" << "1 ����� ���� �� �����" << "\n" << "2 �����" << "\n" << "3 ����" << "\n" << "4 ��������" << "\n" << "5 ���������" << "\n";
	cout << "6 ����������" << "\n" << "7 ��������" << "\n" << "8 �������" << "\n" << "9 �������������" << "\n" << "10 ��������"<<"\n";
	cout << "11 ������� ���� ��� �����" << "\n" << "0 ��������� � �����"<<"\n";
}

void print_catalog(Tree *p, int curSel, int sel){
	if (p) {
		if (curSel == sel)
			printf(" >");
		else
			printf("  ");
		printf("%s\n", p->name);
		if (p->right != nullptr)
			print_catalog(p->right, curSel + 1, sel);
	}
}

int main() {
	file file;
	Tree *treeMNT = 0;
	Tree *localTree = 0;
	string nameFile;
	string keyCom;
	//treeMNT->Select = 0;
	//treeMNT->lvl = 0;
	setlocale(LC_ALL, "rus");
	//cout << "������� ��� ����� ������: " << "\n";
	//cin >> nameFileComputers;
	nameFile = "input.txt";
	read_from_file(nameFile, &treeMNT);
	//cin >> nameFileAudience;
	//back_from_bin(treeMNT);
	treeMNT = treeMNT->left;
	print_catalog(treeMNT, 0, treeMNT->select);
	write_menu();
	std::cin >> keyCom;
	while (keyCom != "0") {
		if (keyCom == "1")
			write_menu();
		if (keyCom == "2" && treeMNT->select != 0)
			treeMNT->select -= 1;
		if (keyCom == "3")
			treeMNT->select += 1;
		if (keyCom == "4") {
			for (int i = 0; i < treeMNT->select; i++) {
				treeMNT = treeMNT->right;
			}
			if (treeMNT->left != nullptr)
				treeMNT = treeMNT->left;
			else
				cout << "������!";
		}
		if (keyCom == "5") {
			treeMNT = treeMNT->fath;
		}
		if (keyCom == "6") {
			for (int i = 0; i < treeMNT->select - 1; i++) {
				treeMNT = treeMNT->right;
			}
			localTree = treeMNT->right;
		}
		if (keyCom == "7") {
			localTree = treeMNT;
			keyCom = "8";
		}
		if (keyCom == "8") {
			for (int i = 0; i < treeMNT->select; i++) {
				treeMNT = treeMNT->right;
			}
			delete treeMNT->left;
			treeMNT = treeMNT->fath;
			if (treeMNT->select != 0) {
				treeMNT = treeMNT->left;
				for (int i = 0; i < treeMNT->select - 1; i++) {
					treeMNT = treeMNT->right;
				}
				treeMNT->right = nullptr;
			}
			else {
				treeMNT->left = treeMNT->left->right;
				treeMNT = treeMNT->left;
			}
		}
		if (keyCom == "9") {
			if (treeMNT->select != 0) {
				for (int i = 0; i < treeMNT->select; i++)
					treeMNT = treeMNT->right;
			}
			const char* newName;
			printf("����� ����� ���: ");
			std::cin >> nameFile;
			cout << "\n";
			newName = nameFile.c_str();
			strcpy(treeMNT->name, newName);
			treeMNT = treeMNT->fath;
			treeMNT = treeMNT->left;
		}
		if (keyCom == "10") {
			while (treeMNT->right != nullptr)
				treeMNT = treeMNT->right;
			treeMNT->right = new Tree;
			treeMNT->right = localTree;
			treeMNT->right->fath = treeMNT->fath;
			treeMNT = treeMNT->right;
			treeMNT->right = nullptr;
			treeMNT = treeMNT->fath;
			treeMNT = treeMNT->left;
			treeMNT->select = 0;
			delete localTree;
		}
		if (keyCom == "11") {
			while (treeMNT->right != nullptr)
				treeMNT = treeMNT->right;
			treeMNT->right = new Tree;
			treeMNT->right->fath = treeMNT->fath;
			treeMNT = treeMNT->right;
			const char* newName;
			printf("����� ����� ���: ");
			std::cin >> nameFile;
			cout << "\n";
			newName = nameFile.c_str();
			strcpy(treeMNT->name, newName);
			treeMNT->right = nullptr;
			treeMNT = treeMNT->fath;
			treeMNT = treeMNT->left;
			treeMNT->select = 0;
		}
		print_catalog(treeMNT, 0, treeMNT->select);
		std::cin >> keyCom;
	}
	system("pause");
	delete localTree;
	delete treeMNT;
	return 0;
}