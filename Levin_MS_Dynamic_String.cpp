#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


class DynamicString 
{
private:
    int size;
    char* data;
public:
    //Пустой конструктор.
    DynamicString() 
    {
        size = 0;
        data = nullptr;
    }
    
    //Конструктор с размером строки.
    DynamicString(const int str_size) 
    {
        size = str_size;
        data = new char[size + 1];
    }

    //Конструктор с размером и данными строки.
    DynamicString(const int str_size, const char str[]) 
    {
        size = str_size;
        data = new char[size + 1];
        for (int i = 0; i < size; i++) 
        {
            data[i] = str[i];
        }
        data[size] = '\0';
    }

    //Конструктор копирования.
    DynamicString(DynamicString& str) 
    {
        size = str.getSize();
        data = new char[size];
        char* new_data = str.getData();
        for (int i = 0; i < size; i++) 
        {
            data[i] = new_data[i];
        }
    }
    
    //Конструктор перемещения.
    DynamicString(DynamicString&& str) noexcept 
    {
        size = str.getSize();
        data = new char[size];
        char* new_data = str.getData();
        for (int i = 0; i < size; i++) 
        {
            data[i] = new_data[i];
        }
        str.change(0);
    }

    //Оператор присваивания.
    DynamicString& operator = (DynamicString& str) 
    {
        if (this != &str) 
        {
            delete[] data;
            size = str.getSize();
            data = new char[size];
            char* new_data = str.getData();
            for (int i = 0; i < size; i++) 
            {
                data[i] = new_data[i];
            }
        }
        return *this;
    }

    //Оператор присваивания с перемещением.
    DynamicString& operator = (DynamicString&& str) noexcept
    {
        if (this != &str) 
        {
            if (size != 0) 
            {
                delete[] data;
            }
            size = str.getSize();
            data = new char[size];
            char* new_data = str.getData();
            for (int i = 0; i < size; i++) 
            {
                data[i] = new_data[i];
            }
            str.change(0);
        }
        return *this;
    }

    /*
    //Оператор индексации символа. По неизвестной мне причине не хочет работать
    char& operator [] (const int number) 
    {
        if (number > 0 && number < size) 
        {
            return data[number];
        }
    }
    */

    //Деструктор.
    ~DynamicString() 
    {
        delete[] data;
    }

    //Метод получения размера строки.
    int getSize() 
    {
        return size;
    }

    //Метод получения данных строки.
    char* getData() 
    {
        if (data != nullptr) 
        {
            return data;
        }
    }

    //Метод получения символа.
    char& getChar(int number) 
    {
        if (number > 0 && number < size) 
        {
            return data[number];
        }
    }

    //Метод изменения строки.
    void change(int new_size, char *new_data = nullptr) 
    {
        delete[] data;
        size = new_size;
        if (size != 0) 
        {
            data = new char[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = new_data[i];
            }
        }
        else 
        {
            data = nullptr;
        }
    }
};

//Оператор сложения.
DynamicString* operator + (DynamicString& left, DynamicString& right) 
{
    //Считываем данные.
    int left_size = left.getSize() - 1;
    int right_size = right.getSize();
    char* left_data = left.getData();
    char* right_data = right.getData();

    //Создаём и инициализируем временные переменные для создания временной строки.
    int temp_size = left_size + right_size;
    char* temp_data = new char[temp_size];
    int i = 0;
    for (int j = 0; j < left_size; j++) 
    {
        temp_data[i++] = left_data[j];
    }
    for (int j = 0; j < right_size; j++) 
    {
        temp_data[i++] = right_data[j];
    }

    //Создаём временную строку для возврата.
    DynamicString* temp_string = new DynamicString(temp_size, temp_data);

    //Очищаем временную строку.
    delete[] temp_data;
    return temp_string;
}

//Тестовая функция для демонстрации возможностей класса.
void test(bool move) 
{
    DynamicString* str1 = new DynamicString(14, "Hello world!\n");
    DynamicString* str2 = new DynamicString(16, "Hello darkness!");
    str1 = *str1 + *str2;
    DynamicString* str3;
    if (move) 
    {
        //Перемещение.
        str3 = new DynamicString(std::move(*str1)); 
    }
    else 
    {
        //Копирование.
        str3 = new DynamicString(*str1);
    }
    
    DynamicString* str4 = new DynamicString();
    
    if (move) 
    {
        //Перемещение.
        *str4 = std::move(*str3);
    }
    else 
    {
        //Копирование.
        *str4 = *str3;
    }

    cout << "1: " << str1->getSize();
    cout << '\n' << "1: " << str1->getData();
    cout << '\n' << "3: " << str3->getSize();
    cout << '\n' << "3: " << str3->getData();
    cout << '\n' << "4: " << str4->getData();
    cout << '\n' << "4: " << str4->getChar(7);
}

//Функция для сортировки строк.
bool cmp(DynamicString* left, DynamicString* right)
{
    //Считываем данные.
    int left_size = left->getSize();
    int right_size = right->getSize();
    char* left_data = left->getData();
    char* right_data = right->getData();

    //Определяем наименьший размер строки.
    int size = min(left_size, right_size);

    for (int i = 0; i < size; i++)
    {
        //Если i-тый символ левой строки идёт позже по алфавиту, то левая строка считается большей.
        if (toupper(left_data[i]) > toupper(right_data[i]))
        {
            return true;
        }
        //Если раньше - то правая.
        else if (toupper(left_data[i]) < toupper(right_data[i]))
        {
            return false;
        }
    }
    //Наконец, большим считается строка с большей длиной.
    if (left_size > right_size)
    {
        return true;
    }
    else {
        return false;
    }
}

//Функция с тестовым заданием.
void test2()
{
    //Создаём вектор строк.
    vector<DynamicString*> strings;
    int count;
    cout << "Enter the number of lines: ";
    cin >> count;
    cout << "Enter lines: " << '\n';
    for (int i = 0; i < count; i++)
    {
        char data[256];
        cin >> data;
        int size = strlen(data);
        DynamicString* new_string = new DynamicString(size, data);
        strings.push_back(new_string);
    }

    //Сортируем вектор.
    sort(strings.begin(), strings.end(), cmp);

    //Выводим вектор.
    cout << '\n' << "Sorted strings: " << '\n';
    for (int i = 0; i < count; i++)
    {
        cout << strings[i]->getData() << '\n';
    }
}

int main()
{
    //Вызов тестовой функции для проверки возможностей класса динамической строки.
    /*
    bool useMove;
    char input;
    cout << "Use move semantics? (Y - yes): ";
    cin >> input;
    if (toupper(input) == 'Y')
    {
        useMove = true;
    }
    else
    {
        useMove = false;
    }
    test(useMove);
    */

    test2();
    system("pause");
    return EXIT_SUCCESS;
}