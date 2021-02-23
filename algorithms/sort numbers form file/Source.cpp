#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;

void rand_vals_file(unsigned int count, bool status)
{
	status = false;
	ofstream fout;
	fout.open("rand.txt");
	if (!fout)
	{
		cout << "\n!!!file not found!!!\n";
		return;
	}
	srand(time(0));
	for (unsigned int i = 0; i < count; i++)
	{
		fout << rand() % 1000 + 1 << endl;
	}
	fout.close();
	status = true;
}

void sorted_output()
{
	unsigned int arr[1000] = {0};
	
	ifstream fin;
	fin.open("rand.txt");
	if (!fin)
	{
		cout << "\n!!!file not found!!!\n";
		return;
	}

	int temp;
	while (fin >> temp)
	{
		arr[temp]++;
	}

	for (int i = 0; i < 1000; i++)
		while (arr[i] -- > 0)
			cout << i+1 << endl;
}

int main()
{
	//rand_vals_file(pow(10, 6));
	sorted_output();
}