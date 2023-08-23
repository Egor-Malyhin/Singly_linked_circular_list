//
// Created by admin on 23.10.2022.
//

#ifndef AISD1_LIST_H
#define AISD1_LIST_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Exeption.h"

template <class T>		//класс список
class List
{
    class Node				//класс элемент списка
    {
        Node *next;
        T data;
    public:
        Node(T& data);
        //friend class List<T>::Iterator;
        friend class List<T>;
    };


    Node *first;
    Node *last;
    int count;
    int test;
public:
    class Iterator			//итератор
    {
        Node *itcur;
        List *list;
        int m_End;
    public:
        Iterator(List<T> &l):list(&l)
        {
            begin();
        }
        void begin()
        {
            itcur=list->first;
            m_End=itcur==NULL;
        }
        int end()
        {
            return m_End;
        }
        void next()
        {
            if (m_End)
                throw new IterException();
            itcur=itcur->next;
        }
        T& operator *()
        {
            if (m_End)
                throw new IterException();
            return itcur->data;
        }
        Iterator operator++()
        {}
        Iterator operator--(){}
        bool operator==(Iterator&){}
        bool operator!=(Iterator&){}

    };
    void Add(T& data);															//добавление элемента в список
    void InsertByIndex(int index,T& data);												//вставка в список по логическому номеру
    T& GetByIndex(int index);														//получение значения по логическому номеру
    void DeleteByIndex(int index);													//удаление значения по логическому номеру
    void Change(int index, T& value);													//изменение значения по логическому номеру
    int GetByValue(T& value);												//получение логического номера по заданному значению
    void DeleteByValue(T& value);														//удаление заданного значения
    bool IsValue(T& value);															//запрос наличия заданного значения
    void Clear();																//очистка списка
    int GetCount();																//запрос размера списка
    bool IsEmpty();																//проверка списка на пустоту
    List();
    ~List();
};

template <class T> List<T>::Node::Node(T& d)							//конструктор класса Elem
{
    data=d;
}
template <class T> List<T>::List()										//конструктор класса List (без параметра)
{
    first=last=NULL;
    count=0;
    test=0;
}
template <class T> List<T>::~List()										//деструктор
{
    Clear();
}
template <class T> void List<T>::Add(T& data)							//добавление элемента в список
{
    if (first==NULL)													//если список пуст (добавление первого элемента)
    {
        first=last=new Node (data);
        first->next=last;
    }
    else																//добавление в конец существующего списка
    {
        Node  *p=new Node (data);
        last->next=p;
        last=p;
        last->next=first->next;
    }
    count++;
}
template <class T> void List<T>::InsertByIndex(int index,T& data)		//вставка по логическому номеру
{
    test=0;

    if (index>=0 && index<=count)
    {
        Node  *q=new Node (data);

        if (index==0)													//если вставляем в голову (перед first)
        {
            if (first==NULL)											//если список пуст (добавление первого элемента)
            {
                first=last=q;
                first->next=last;
            }
            else
            {
                last->next=q;
                q->next=first;
                first=q;
            }
            test++;
        }
        else
        {
            if (index==count)											//если вставляем после последнего
            {
                last->next=q;
                q->next=first;
                last=q;

                test++;
            }
            else														//если вставляем в середину
            {
                Node  *p,*tmp;
                int i;

                for (i=0,p=first;i<index-1;i++,p=p->next)test++;		//поиск элемента перед вставляемым

                tmp=p->next;
                p->next=q;
                q->next=tmp;
            }
        }
        count++;
    }
    else																//если элемента с таким индексом нет
        throw new IndexException();
}

template <class T> T& List<T>::GetByIndex(int index)					//извлечение по логическому номеру
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    if (index>=0 && index<=count-1)
    {
        Node  *p;
        int i;

        for (i=0,p=first;i<index;i++,p=p->next);						//поиск элемента по индексу

        return p->data;
    }
    else																//если элемента с таким индексом нет
        throw new IndexException();
}

template <class T> void List<T>::DeleteByIndex(int index)				//удаление по логическому номеру
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    test=0;

    if (index>=0 && index<=count-1)
    {
        if (index==0)													//если удаляем first
        {
            if (first->next==first)										//если first - единственный элемент в списке
            {
                delete first;
                first=last=NULL;
            }
            else
            {
                Elem *tmp=first;
                first=first->next;
                last->next=first;
                delete tmp;
            }
            test++;
        }
        else															//если удаляем из середины
        {
            Node  *p, *tmp;
            int i;

            for (i=0,p=first;i<index-1;i++,p=p->next)test++;			//поиск элемента перед удаляемым
            tmp=p->next;
            p->next=tmp->next;
            if (index==count-1)											//поправка на случай удаления последнего элемента
                last=p;
            delete tmp;
        }
        count--;
    }
    else																//если элемента с таким индексом нет
        throw new IndexException();
}

template <class T> void List<T>::Change(int index, T& value)			//изменение значения по логическому номеру
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    if (index>=0 && index<=count-1)
    {
        Node  *p;
        int i;

        for (i=0,p=first;i<index;i++,p=p->next);						//поиск элемента по индексу

        p->data=value;													//изменение значения на заданное
    }
    else																//если элемента с таким индексом нет
        throw new IndexException();
}

template <class T> int List<T>::GetByValue(T& value)					//получение индекса заданного значения
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    Node  *p;
    int i;

    for (i=0,p=first;i<count;i++,p=p->next)								//поиск индекса заданного значения
    {
        if (p->data==value)
            return i;
    }
    throw new ValueException();											//если заданное значение не найдено
}

template <class T>	void List<T>::DeleteByValue(T& value)				//удаление заданного значения
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    Node  *p,*tmp;
    int i;

    for (i=0,p=first;i<count && p->data!=value;i++,tmp=p,p=p->next);	//поиск индекса заданного значения
    if (i==count)														//если заданное значение не найдено
        throw new ValueException();

    if (i==0)															//если удаляем first
    {
        if (first->next==first)											//если first - единственный элемент в списке
        {
            delete first;
            first=last=NULL;
        }
        else
        {
            last->next=first;
            first=first->next;
            delete p;
        }
    }
    else																//если удаляем из середины
    {
        tmp->next=p->next;
        if (i==count-1)													//поправка на случай удаления последнего элемента
            last=tmp;
        delete p;
    }
    count--;
}


template <class T>	bool List<T>::IsValue(T& value)						//запрос наличия заданного значения
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    test=0;

    Node  *p;
    int i;
    for (i=0,p=first;i<count;i++,p=p->next)								//поиск заданного значения
    {
        test++;
        if (p->data==value)												//значение найдено
            return 1;
    }
    return 0;															//значение не найдено
}

template <class T> void List<T>::Clear()								//очистка списка
{
    if (first==NULL) 													//если список пуст
        throw new EmptyException();

    Node  *p, *tmp;

    for (p=first;p!=last;)
    {
        tmp=p;															//запомнить текущее
        p=p->next;														//перейти к следующему
        if (tmp) delete tmp;											//удалить текущее
    }
    delete last;														//удалить last

    count=0;
    first=last=NULL;
}


template <class T> int List<T>::GetCount()								//возвращает количество элементов списка
{
    return count;
}

template <class T> bool List<T>::IsEmpty()								//проверка списка на пустоту
{
    if (count==0)														//если список пуст
        return 1;
    else
        return 0;
}
/*template <class T> int List<T>::GetTest()								//возвращает количество итераций
{
    return test;
}*/

#endif //AISD1_LIST_H
