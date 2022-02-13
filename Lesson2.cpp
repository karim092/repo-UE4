// Lesson2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

// Task 1

enum Gender
{
    GENDER_MALE,
    GENDER_FEMALE
};


class Person
{
private:
    std::string m_name;
    int m_age;
    Gender m_gender;
    float m_weight;
public:
    Person(std::string name, int age, Gender gender, float weight) :
        m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}

    void setName(std::string name = "")
    {
        if (name == "")
        {
            std::cout << "Name: ";
            std::cin >> m_name;
        }
        else
            m_name = name;
    }

    void setAge(int age = 0)
    {
        if (age == 0)
        {
            std::cout << "Age: ";
            std::cin >> m_age;
        }
        else
            m_age = age;
    }

    void setWeight(float weight = 0.0)
    {
        if (weight == 0)
        {
            std::cout << "Weight: ";
            std::cin >> m_weight;
        }
        else
            m_weight = weight;
    }

    void printInfo() const
    {
        std::cout << "Name: " << m_name << std::endl
            << "Age: " << m_age << std::endl
            << "Gender: " << (m_gender == GENDER_MALE ? "M" : "F") << std::endl
            << "Weight: " << m_weight << std::endl;
    }
};

class Student : public Person
{
private:
    static int count;
    int m_yos; // year of study
public:
    Student(std::string name, int age, Gender gender, float weight, int yos) :
        Person(name, age, gender, weight), m_yos(yos)
    {
        count++;
    }

    Student(const Student& s) : Person(s)
    {
        count++;

        m_yos = s.m_yos;
    }

    static void printCount()
    {
        std::cout << "number of students: " << count << std::endl;
    }

    void setYearStudy(int yos = 0)
    {
        if (yos == 0)
        {
            std::cout << "in year of study: ";
            std::cin >> m_yos;
        }
        else
            m_yos = yos;
    }

    void incYear()
    {
        m_yos++;
    }

    void printInfo() const
    {
        Person::printInfo();
        std::cout << "year of study: " << m_yos << std::endl;
    }

    ~Student()
    {
        count--;
    }
};

// Task 2

class Fruit 
{
private:
    std::string m_name;
    std::string m_color;
public:
    void setName(std::string name)
    {
        m_name = name;
    }

    void setColor(std::string color)
    {
        m_color = color;
    }

    const std::string& getName() const
    {
        return m_name;
    }

    const std::string& getColor() const
    {
        return m_color;
    }
};

class Apple : public Fruit
{
public:
    Apple(std::string color = "green")
    {
        setName("apple");
        setColor(color);
    }
};

class Banana : public Fruit
{
public:
    Banana(std::string color = "yellow")
    {
        setName("banana");
        setColor(color);
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith()
    {
        setName("Granny Smith " + Apple::getName());
    }
};

using namespace std;

int Student::count = 0;

int main()
{
 
    // Task 1

    cout << "Task 1 \n" << endl;

    Student st1("Marat", 45, GENDER_MALE, 55.2, 2015);
    st1.printInfo();

    cout << " \n" << endl;

    Student st2("Azalia", 20, GENDER_FEMALE, 55.2, 2022);
    st2.printInfo();

    cout << " \n" << endl;

    Student st3("Rustam", 29, GENDER_MALE, 55.2, 2020);
    st3.printInfo();

    cout << " \n" << endl;

    Student::printCount();
    cout << " \n" << endl;

	// Task 2

    cout << "Task 2 \n" << endl;

	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    // Task 3

    /* Для реализации игры в Блэкджек необходимы данные объекты :

    1) Колода карт
    2) Игрок
    3) Дилер

    Исходя из указанных объектов можно определить несколько классов :

    1) Карта
    - номинал
        - масть
        2) Колода
        - массив ссылок на объекты класса Карта
        3) Игрок(абстрактный класс)
        - Имя игрока
        4) Игрок(человек, потомок от абстрактного класса Игрок)
        5) Дилер(человек, потомок от абстрактного класса Игрок)
        6) Рука(набор карт)
        - массив ссылок на карты каждого игрока
        7) Игра
        - текущая Колода
        - текущий Дилер
        - текущий Игрок
        */

}

