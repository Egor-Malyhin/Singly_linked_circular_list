//
// Created by admin on 23.10.2022.
//

#ifndef AISD1_EXEPTION_H
#define AISD1_EXEPTION_H
#pragma once
#include <iostream>
using namespace std;

class Exception
{
public:
    virtual void PrintError()=0;
    Exception(){}
    ~Exception(){}
};
class IndexException: public Exception
{
public:

    IndexException(){}
    void PrintError()
    {
        cout<<endl<<"Ошибка: неправильное значение"<<endl;
    }
};

class ValueException: public Exception
{
public:

    ValueException(){}
    void PrintError()
    {
        cout<<endl<<"Ошибка: такого значения нет в списке"<<endl;
    }
};
class EmptyException: public Exception
{
public:

    EmptyException(){}
    void PrintError()
    {
        cout<<endl<<"Ошибка: невозможно выполнить, список пуст"<<endl;
    }
};
class IterException: public Exception
{
public:

    IterException(){}
    void PrintError()
    {
        cout<<endl<<"Ошибка: итератор заблокирован"<<endl;
    }
};

#endif //AISD1_EXEPTION_H
