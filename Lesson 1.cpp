// Lesson 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdint>

// Task 1

class Power {
public:
    int a, b;

    void set() {
        std::cout << "Vvedite chislo A: " << std::endl;
        std::cin >> a;
        std::cout << "Vvedite chislo B: " << std::endl;
        std::cin >> b;
    }

    void calculate() {
        std::cout << pow(a, b);
    }
};

// Task 2

class RGBA {
private:
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;
public:
    RGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255) :
        m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}

    void print()
    {
        std::cout << "r=" << static_cast<int>(m_red) <<
            " g=" << static_cast<int>(m_green) <<
            " b=" << static_cast<int>(m_blue) <<
            " a=" << static_cast<int>(m_alpha) << std::endl;
    }

};

// Task 3

class Stack
{
private:
    int array[10];
    int length = 0;

public:
    Stack() {}

    void reset()
    {
        while (length)
            array[length--] = 0;
    }

    bool push(int num)
    {
        if (length > 9)
            return false;
        else
            array[length++] = num;

        return true;
    }

    int pop()
    {
        if (length)
            return array[length--];
        else
            std::cout << "Stack is empty!" << std::endl;

        return -1;
    }

    void print()
    {
        for (int i = 0; i < length; i++)
            std::cout << array[i] << ' ';
        std::cout << std::endl;
    }
};

int main()
{
   // Task 1

    std::cout << "Task 1 \n" << std::endl;

    Power test;
    
    test.set();
    test.calculate();

    std::cout << " \n" << std::endl;

    // Task 2

    std::cout << "Task 2 \n" << std::endl;

    RGBA rgba_1;
    rgba_1.print();

    RGBA rgba_2(50, 110, 150, 8);
    rgba_2.print();

    std::cout << " \n" << std::endl;

    // Task 3

    std::cout << "Task 3 \n" << std::endl;

    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    std::cout << " \n" << std::endl;

    return 0;
}

