#pragma once
#include <iostream>

class DynamicString
{
private:
	char *data;

public:
	// Пустой конструктор
	DynamicString();

	// Конструктор копирования строки
	DynamicString(const char *str);

	// Конструктор копирования динамической строки
	DynamicString(const DynamicString &str);

	// Конструктор перемещения динамической строки
	DynamicString(DynamicString &&str) noexcept;

	// Деструктор
	~DynamicString();

	// Оператор индексации
	char &operator[](size_t number) const;

	// Оператор присваивания строки
	DynamicString &operator=(const char *str);

	// Оператор присваивания динамической строки
	DynamicString &operator=(const DynamicString &str);

	// Оператор присваивания динамической строки с перемещением
	DynamicString &operator=(DynamicString &&str) noexcept;

	// Оператор сложения динамической строки с обычной
	friend DynamicString &operator+(const DynamicString &left, const char *right);

	// Оператор сложения динамических строк
	friend DynamicString &operator+(const DynamicString &left, const DynamicString &right);

	// Оператор вывода
	friend std::ostream &operator<<(std::ostream &out, const DynamicString &str);

	// Оператор сравнения "больше"
	friend bool operator<(const DynamicString &left, const DynamicString &right);

	// Метод получения размера строки
	size_t Size() const;

	// Очистка
	void Clean();

};
