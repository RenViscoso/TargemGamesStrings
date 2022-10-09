#include <algorithm>
#include <iostream>
#include <vector>
#include "DynamicString.h"

using namespace std;

bool DS_lesser(const DynamicString &left, const DynamicString &right)
{
	return !(left < right);
}

int main()
{
	setlocale(LC_ALL, "Rus");

	vector<DynamicString> strings;
	bool done = false;

	while (!done)
	{
		DynamicString line;
		cout << "Please, enter a line: ";
		char data[1024];
		cin.getline(data, 1024);
		line = data;
		
		strings.push_back(line);
		
		cout << "Enter 'Y' for a new line: ";
		cin.getline(data, 1024);

		if (toupper(data[0]) != 'Y')
		{
			done = true;
		}
	}

	sort(strings.begin(), strings.end(), DS_lesser);

	cout << endl << "Your sorted lines:" << endl << endl;
	
	for (auto string : strings)
	{
		cout << string << endl;
	}
	
	cout << endl;

	system("pause");
	return EXIT_SUCCESS;
}