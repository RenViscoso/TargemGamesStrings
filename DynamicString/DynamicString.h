#pragma once
#include <iostream>

class DynamicString
{
private:
	char *data;

public:
	// ������ �����������
	DynamicString();

	// ����������� ����������� ������
	DynamicString(const char *str);

	// ����������� ����������� ������������ ������
	DynamicString(const DynamicString &str);

	// ����������� ����������� ������������ ������
	DynamicString(DynamicString &&str) noexcept;

	// ����������
	~DynamicString();

	// �������� ����������
	char &operator[](size_t number) const;

	// �������� ������������ ������
	DynamicString &operator=(const char *str);

	// �������� ������������ ������������ ������
	DynamicString &operator=(const DynamicString &str);

	// �������� ������������ ������������ ������ � ������������
	DynamicString &operator=(DynamicString &&str) noexcept;

	// �������� �������� ������������ ������ � �������
	friend DynamicString &operator+(const DynamicString &left, const char *right);

	// �������� �������� ������������ �����
	friend DynamicString &operator+(const DynamicString &left, const DynamicString &right);

	// �������� ������
	friend std::ostream &operator<<(std::ostream &out, const DynamicString &str);

	// �������� ��������� "������"
	friend bool operator<(const DynamicString &left, const DynamicString &right);

	// ����� ��������� ������� ������
	size_t Size() const;

	// �������
	void Clean();

};
