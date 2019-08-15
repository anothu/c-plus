#pragma once
struct student
{
	char num[10];
	char name[10];
	int grade;
};
void menu();
void input(int n, student s[]);
void output(int n, student s[]);
void search(int n, student s[]);