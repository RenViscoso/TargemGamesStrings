#include "iomanip"
#include "DynamicString.h"

using namespace std;

// �������
void DynamicString::Clean()
{
	delete[] data;
	data = nullptr;
}

// ������ �����������
DynamicString::DynamicString()
{
	data = nullptr;
}

// ����������� ����������� ������
DynamicString::DynamicString(const char *str)
{
	const size_t size = strlen(str);
	data = new char[size + 1];

	for (size_t index = 0; index < size; index++)
	{
		data[index] = str[index];
	}

	data[size] = '\0';
}

// ����������� ����������� ������������ ������
DynamicString::DynamicString(const DynamicString &str)
{
	size_t size = str.Size();
	data = new char[size + 1];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = str[i];
	}

	data[size] = '\0';
}

//����������� ����������� ������������ ������
DynamicString::DynamicString(DynamicString &&str) noexcept
{
	data = str.data;
	str.data = nullptr;
}

// ����������
DynamicString::~DynamicString()
{
	if (data != nullptr)
	{
		Clean();
	}
}

// �������� ����������
char &DynamicString::operator[](const size_t number) const
{
	size_t string_size = Size();
	if (number >= string_size)
	{
		throw out_of_range("DynamicString::operator[] - Too big index!");
	}
	return data[number];
}

// �������� ������������ ������
DynamicString &DynamicString::operator=(const char *str)
{
	if (data != nullptr)
	{
		Clean();
	}

	size_t size = strlen(str);
	data = new char[size + 1];

	for (size_t index = 0; index < size; index++)
	{
		data[index] = str[index];
	}

	data[size] = '\0';
	
	return *this;
}

// �������� ������������ ������������ ������
DynamicString &DynamicString::operator=(const DynamicString &str)
{
	if (&str != this)
	{
		if (data != nullptr)
		{
			Clean();
		}

		size_t size = str.Size();
		data = new char[size + 1];

		for (size_t i = 0; i < size; i++)
		{
			data[i] = str[i];
		}

		data[size] = '\0';
	}
	return *this;
}

// �������� ������������ ������������ ������ � ������������
DynamicString &DynamicString::operator=(DynamicString &&str) noexcept
{
	if (&str != this)
	{
		if (data != nullptr)
		{
			Clean();
		}
		data = str.data;
		str.data = nullptr;
	}
	return *this;
}

// ����� ��������� ������� ������
size_t DynamicString::Size() const
{
	if (data == nullptr)
	{
		return 0;
	}
	return strlen(data);
}

// �������� �������� ������������ ������ � �������
DynamicString &operator+(const DynamicString &left, const char *right)
{
	size_t size_left = left.Size();
	size_t size_right = strlen(right);
	size_t size = size_left + size_right;

	char *string = new char[size + 1];

	size_t index = 0;

	for (size_t j = 0; j < size_left; j++, index++)
	{
		string[index] = left[j];
	}

	for (size_t j = 0; j < size_right; j++, index++)
	{
		string[index] = right[j];
	}

	string[size] = '\0';

	DynamicString *result = new DynamicString(string);

	return *result;
}

// �������� �������� ���� ������������ �����
DynamicString &operator+(const DynamicString &left, const DynamicString &right)
{
	size_t size_left = left.Size();
	size_t size_right = right.Size();
	size_t size = size_left + size_right;
	
	char *string = new char[size + 1];

	size_t index = 0;
	
	for (size_t j = 0; j < size_left; j++, index++)
	{
		string[index] = left[j];
	}

	for (size_t j = 0; j < size_right; j++, index++)
	{
		string[index] = right[j];
	}

	string[size] = '\0';

	DynamicString *result = new DynamicString(string);
	
	return *result;
}

// �������� ������
ostream &operator<<(ostream &out, const DynamicString &str)
{
	if (str.data != nullptr)
	{
		out << str.data;
	}
	return out;
}

// �������� ��������� "������"
bool operator<(const DynamicString &left, const DynamicString &right)
{
	/*
	* ������� ��������� ������, � ������� ������ ����������� ���������� ������. 
	* ���� ������ ��������� - ������ �� ������, ��� ����� ������� ������
	*/

	size_t size_left = left.Size();
	size_t size_right = right.Size();
	size_t size_min = min(size_left, size_right);

	for (size_t i = 0; i < size_min; i++)
	{
		char char_left = (char)toupper(left[i]);
		char char_right = (char)toupper(right[i]);

		if (char_left != char_right)
		{
			if (char_left < char_right)
			{
				return true;
			}
			
			return false;
		}
	}

	if (size_left < size_right)
	{
		return true;
	}
	
	return false;
}
