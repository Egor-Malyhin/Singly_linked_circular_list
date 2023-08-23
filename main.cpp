#include "List.h"
#include "Exeption.h"
#include <iostream>
#include <conio.h>


using namespace std;

int main()
{
    system("chcp 65001");
    List <int> list;
    List<int>::Iterator Iter(list);
    int k,val;
    char c;
    while(1)
    {
        cout <<endl<<"Меню:" <<endl
             <<"1 - Добавить в список" <<endl
             <<"2 - Вставка по номеру"<<endl
             <<"3 - Поиск по номеру"<<endl
             <<"4 - Удаление по номеру"<<endl
             <<"5 - Выбрать значение"<<endl
             <<"6 - Поиск по значению"<<endl
             <<"7 - Удаление по значению"<<endl
             <<"8 - Проверка наличия значения"<<endl
             <<"9 - Очистить список"<<endl
             <<"q - Размер списка"<<endl
             <<"w - Проверка на пустоту"<<endl
             <<"e - Показать список"<<endl
             <<"r - Установить итератор в начало"<<endl
             <<"t - Текущее значение итератора"<<endl
             <<"y - Приращение итератора"<<endl
             <<"u - Проверка итератора"<<endl
             <<"0 - Выход"<<endl;
        cin>>c;
        int resetIter=0;		//признак необходимости сброса итератора
        if (c=='4' || c=='7' || c=='9')
            resetIter=1;
        try
        {
            switch(c)
            {
                case '1':				//добавление в конец
                {
                    cout<<endl<<"Введите значение: "<<endl;
                    cin>>val;
                    list.Add(val);
                    cout<<endl<<"Значение было добавлено"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '2':		//вставка по логическому номеру
                {
                    cout<<endl<<"Введите целое значение: "<<endl;
                    cin>>val;

                    cout<<"Введите номер: "<<endl;
                    cin>>k;

                    list.InsertByIndex(k,val);
                    cout<<endl<<"Значение было вставлено"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '3':			//получение по логическому номеру
                {
                    cout<<"Введите номер: "<<endl;
                    cin>>k;
                    cout<<k<<"-ый элемент: "<<list.GetByIndex(k)<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '4':			//удаление по логическому номеру
                {
                    cout<<"Введите номер: "<<endl;
                    cin>>k;
                    list.DeleteByIndex(k);
                    cout<<endl<<"Значение было удалено"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '5':	//изменение значения по логическому номеру
                {
                    cout<<"Введите номер: "<<endl;
                    cin>>k;

                    cout<<"Введите целое значение: "<<endl;
                    cin>>val;

                    list.Change(k,val);
                    cout<<endl<<"Значение было выбрано"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '6':	//получение логического номера по заданному значению
                {
                    cout<<"Введите значение: "<<endl;
                    cin>>val;

                    cout<<"Номер: "<<val<<": "<<list.GetByValue(val)<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '7':	//удаление заданного значения из списка
                {
                    cout<<"Введите значение: "<<endl;
                    cin>>val;
                    list.DeleteByValue(val);
                    cout<<endl<<"Значение было удалено"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '8':		//запрос наличия заданного значения
                {
                    cout<<"Введите значение: "<<endl;
                    cin>>val;

                    if (list.IsValue(val))
                        cout<<"1"<<endl;
                    else
                        cout<<"0"<<endl;

                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '9':			//очистка списка
                {
                    list.Clear();
                    cout<<endl<<"Список был очищен"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'q':				//запрос размера списка
                {
                    cout<<"Размер списка: "<<list.GetCount()<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'w':		//проверка списка на пустоту
                {
                    if (list.IsEmpty())
                        cout<<"1"<<endl;
                    else
                        cout<<"0"<<endl;

                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'e':			//вывод списка на экран
                {
                    if (list.GetCount()==0)
                        cout<<endl<<"Список пуст"<<endl<<endl;
                    else
                    {
                        cout<<endl<< "Элементы списка: "<<endl<<endl;

                        for (int i=0;i<list.GetCount();i++)
                            cout<<i<<"-ый: "<<list.GetByIndex(i)<<endl;
                    }
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'r':			//установка итератора на начало
                {
                    Iter.begin();
                    cout<<endl<<"Итератор был установлен в начало"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 't':	//получить/установить текущее значение
                {
                    int val=*Iter;
                    cout<<"Текущее значение: "<<val<<endl;
                    while(1)
                    {
                        cout<<"Выбрать значение? (y/n)"<<endl;
                        char buf=getch();
                        if (buf=='y')
                        {
                            cout<<"Новое значение: ";
                            cin>>*Iter;
                            break;
                        }
                        if (buf=='n')
                            break;
                    }
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'y':			//инкремент итератора
                {
                    Iter.next();
                    cout<<endl<<"Итератор был увеличен"<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case 'u':		//проверка состояния итератора
                {
                    if (Iter.end())
                        cout<<endl<<false<<endl;
                    else
                        cout<<true<<endl;
                    cout<<endl<<"OK"<<endl;
                    break;
                }
                case '0':
                    return 1;
            }
        }
        catch (Exception *ex)
        {
            ex->PrintError();
            delete ex;
        }
        if (resetIter)	//если список изменился, возможность потери связи					//списка с итератором
        {
            cout<<endl<<"Список был изменен, сбросьте итератор!" <<endl;
            cout<<endl<<"OK"<<endl;
        }
    }

}