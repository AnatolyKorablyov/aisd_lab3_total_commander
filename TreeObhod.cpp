// TreeObhod.cpp: определяет точку входа для консольного приложения.
//
/*
В файле дерево в виде
Ann
.Boris
..Cat
..Dora
...Eva
...Fred
..Goga
...Helmut
....Marta
.....Bred
.....Stiv
.....Jon
......Tom
...Nata
.Nina
Построить бинарное дерево. Обеспечить выдачу бинарного дерева в
3 порядках обхода. Выдать исходное дерево из бинарного. 
Имя входного файла - через командную строку.
*/

#include "stdafx.h"   
#include <fstream>

const int DL = 20;          // максимальная длина

using namespace std;

struct Tree 
{
    char name[DL];
    int urov;
    Tree *fath;         // отец в исходном дереве
    Tree *left;
    Tree *right;
};

int read_from_file(FILE *F, Tree **r);  // чтение из файла, формирование дерева
void back_from_bin(Tree *p);            // выдача исходное дерева из бинарного 
void print_down_bin(Tree *p, int lev);  // выдача бинарного сверху вниз
void print_up_bin(Tree *p, int lev);    // выдача бинарного снизу вверх
void print_right_bin(Tree *p, int lev); // выдача бинарного слева направо

int main(int argc, char* argv[])
{
    Tree *root = 0;
    FILE *Fin;
    setlocale(LC_ALL, "rus");
    if (argc != 2)
    {
       printf("\nNumber parameters is wrong");
       getchar();
       return -1;
    }
/*	Fin = fopen("input.txt", "r");    // отладка
    if (Fin == NULL )
    {
         printf("\nCan not open file %s", Fin);
         getchar();
	 return -1;
    } */
    Fin = fopen(argv[1], "r");
    if (Fin == NULL )
    {
         printf("\nCan not open file %s", argv[1]);
         getchar();
	 return -1;
    } 
    read_from_file(Fin, &root);
    printf("Бинарое дерево построено\n");
    getchar();
    printf("Вывод из бинарного дерева сильно ветвящегося\n");
    back_from_bin(root);
    getchar();
    printf("Вывод бинарного дерева сверху вниз\n");
    print_down_bin(root, 0);
    getchar();
    printf("Вывод бинарного дерева снизу вверх\n");
    print_up_bin(root, 0);
    getchar();
    printf("Вывод бинарного дерева слева направо\n");
    print_right_bin(root, 0);
    getchar();
}

int read_from_file(FILE *F, Tree **r)
{
    char buf[DL];
    int i, k, m, len;
    Tree *p, *q, *t;       // *root = 0 
    m = 0;                 // уровень вершины
    t = 0;
    while (!feof(F))
    {
		 k = fscanf(F, "%s", buf);
	     len = strlen(buf);              
		 if (len == 0) break;            // если конец файла в следующей строке
	     k = 0;
	     while (buf[k] == '.') k++ ;     // k-уровень вершины
         p = new Tree;
         strncpy(p -> name, &buf[k], len-k+1);  // 0-(k-1) - точки, (k-1)-(len-1) - имя, \0 - конец строки
		 buf[0] = '\0';                  // если конец файла в следующей строке
         p -> urov = k;
         p -> left = 0;
         p -> right = 0;
	     if (k == 0)                    // корень
	     {
	         *r = p;
	         t = *r;
	         continue;
         }
         if (k > m)                  // переход на следующий уровень
	     {
	         t -> left = p;
	         p -> fath = t;
	     }
         else if (k == m)            // тот же уровень
	     {
              t -> right = p;
              p -> fath = t-> fath;  // отец тот же
         }
         else        // подъем по дереву на m-k уровней
         {
              q = t;
              for (i = 0; i < m - k; i++) q = q -> fath;
              // q - предыдущая вершина того же уровня
              p -> fath = q -> fath;   // отец тот же, что у брата
              q -> right = p;
         }
         m = k;      // текущий уровень
         t = p;      // текущая вершина
    }
    fclose( F);
    return 0;
}

void back_from_bin(Tree *p)
{
    int i, j;
    char st[DL];
    if (p)
    {
        for (i = 0; i < p -> urov; i++) st[i] = '.';
        j = 0;
        while ((p -> name)[j] != 0) st[i++] = (p -> name)[j++];
        st[i] = '\0';
        printf("%s\n", st);
        back_from_bin(p -> left);
        back_from_bin(p -> right);
    }
}

void print_right_bin(Tree *p, int level)
{
    if (p)
    {
        print_right_bin(p -> left, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_right_bin(p -> right, level + 1);
    }
}

void print_up_bin(Tree *p, int level)
{
    if (p)
    {
        print_up_bin(p -> left, level + 1);
        print_up_bin(p -> right, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
    }
}

void print_down_bin(Tree *p, int level)
{
    if (p)
    {
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_down_bin(p -> left, level + 1);
        print_down_bin(p -> right, level + 1);
    }
}
