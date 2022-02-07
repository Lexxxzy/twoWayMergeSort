#include <iostream>
#include <ctime>
#include <numbers>
#include "windows.h"
#include <locale.h>

using namespace std;

class stack
{
private:
    struct Node // Структура данных для хранения элементов в стеке
    {
        int data;
        Node* link;
    };

    
public:
    Node* top;
    void push(int data);
    bool isEmpty();
    int getTop();
    int pop();
    void display();

    unsigned long long int Nop = 0;

    stack() { top = NULL; }
};

    // Метод для добавление элемента в стек
void stack::push(int data)
    {

        // Создание и выделение памяти для нового элемента
        struct Node* temp;
        temp = new Node();

        // Записать число в стек
        temp->data = data;

        //Добавить указатель на голову
        temp->link = top;

        //Сделать голову текущим элементом
        top = temp;
    }

    // Прверяем пуст ли стек
    bool stack::isEmpty()
    {
        return &top == NULL ? true : false;;
    }

    // Возвращает верхний элемент стэка
    int stack::getTop()
    {

        // Check for empty stack
        if (!isEmpty())
            return top->data;
        else
            exit(1);
    }

    //удаление элемента из стека и возвращение его значения
    int stack::pop()
    {
        struct Node* temp;

        // Если в стеке нет элементов
        if (top == NULL)
        {
            cout << "\nStack is empty" << endl;
            exit(1);
        }
        else
        {

            // Сохраняем top
            temp = top;
            int data = top->data;

            // Присвоить top следующему элементу
            top = top->link;

            // удалить связь между первым и вторым элементом
            temp->link = NULL;

            // Освободить память
            free(temp);
            return data;
        }
    }

    //получение всех элементов
    void stack::display()
    {
        struct Node* temp;

        // Если нет элементов стеке
        if (top == NULL)
        {
            cout << "\nStack is empty";
        }
        else
        {
            temp = top;
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->link;
            }
            cout << "\n";
        }
    }






int getData(stack* d, int n)
{
    int i;
    d->Nop++;
    stack* second = new stack();
    d->Nop+=4;
    int data;
    d->Nop++;

    for (i = 0; i < n; i++)
    {
        second->push(d->pop()); //удаляем из основного стека и переписываем во временнай до n-ого элемента (чтобы получить ичкомое значение)
        d->Nop+=20;
    }
    data = d->pop(); //удаляем искомый элемент из основного стека и получаем его значение
    d->Nop += 12;
    second->push(data); //добавляем во вспомогательный стек чтобы получить начальное расположение
    d->Nop += 9;
    for (i = 0;i<=n; i++)
    {
        d->push(second->pop());//убираем с конца временного списка и добавляем в начало основного (возвращаем все как было)
        d->Nop += 20;
    }
    return data; //возвращаем значение
    d->Nop += 1;
    

    delete second;
    d->Nop += 1;
}

void setValue(stack* d, int n, int data)
{
    int i;
    d->Nop += 1;
    stack* second = new stack();
    d->Nop += 4;
    int return_value;
    d->Nop += 1;
    for (i = 0; i < n; i++)
    {
        second->push(d->pop()); //удаляем из основного стека и переписываем во временнай до n-ого элемента (чтобы получить ичкомое значение)
        d->Nop += 20;
    }
    return_value = d->pop(); //удаляем искомый элемент из основного стека и получаем его значение
    d->Nop += 12;
    second->push(data); //добавляем во вспомогательный стек данное значение
    d->Nop += 9;

    for (i = 0;i<=n; i++)
    {
        d->push(second->pop()); //убираем с конца временного списка и добавляем в начало основного (возвращаем все как было)
        d->Nop += 20;
    }

    delete second; //очищаем память
    d->Nop += 1;
}

/* Функция для объединения двух стеков s[l..m] и s[m+1..r] всего данного стека s */
void merge(stack* s, int l, int m, int r);

void mergeSort(stack* d, int n)
{
    int curr_size;  // Переменная для хранение размеров подсписков
                    // таким образом curr_size принимает значения от  1 до n/2
    d->Nop += 1;
    int left_start; // Для хранения начального индекса левого подсписка который должен быть объединен
    d->Nop += 1;

    // Объединение подсписков методом снизу-вверх.  
    // То есть сначала объединить списки рамером 1
    // чтобы создать отсортированные подсписки рамером 2, 
    // потом объединить подсписки размером 2, чтобы создать отсортированные списки размером 4 и т.д.
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        // Задаем начальное значение(шаг) для разных подмассивов размером current size
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
        {
            //Найти конечную точку левого подсписка. 
            // mid+1 - начальная точка правого подсписка
            int mid = min(left_start + curr_size - 1, n - 1);
            d->Nop += 3;
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            d->Nop += 3;

            // Объединить подсписки c[left_start...mid] и c[mid+1...right_end]
            merge(d, left_start, mid, right_end);
            d->Nop += 4;
        }
    }
}

/* функция для объединения двух саб-списков c[l..m] и c[m+1..r] всего стека c */
void merge(stack* s, int l, int m, int r)
{
    int i, j, k;
    s->Nop += 3;
    int n1 = m - l + 1;
    s->Nop += 3;
    int n2 = r - m;
    s->Nop += 2;

    /* создаем временные подсписки */
    //int L[n1], R[n2];

    stack* L = new stack();
    s->Nop += 4;
    stack* R = new stack();
    s->Nop += 4;

    /* Копируем данные из основного стека в подсписки */
    for (i = 0; i < n1; i++) {
        //L[i] = arr[l + i];
        L->push(0);
        s->Nop += 7;
    }
    for (j = 0; j < n2; j++) {
        //R[j] = arr[m + 1 + j];
        R->push(0);
        s->Nop += 7;
    }

    for (i = 0; i < n1; i++) {
        //L[i] = arr[l + i];
        setValue(L, i, getData(s, l + i));
        s->Nop += 7;
    }

    for (j = 0; j < n2; j++) {
        //R[j] = arr[m + 1 + j];
        setValue(R, j, getData(s, m + 1 + j));
        s->Nop += 7;
    }
    //L->display();
   // cout << "\n";
   // R->display();
    /* объединяем обратно два временных списка в стек c[l..r]*/
    i = 0;
    j = 0;
    k = l;
    s->Nop += 3;
    while (i < n1 && j < n2)
    {
        //if (L[i] <= R[j])
        if (getData(L, i) <= getData(R, j))
        {
            //arr[k] = L[i];
            setValue(s, k, getData(L, i));
            s->Nop += 5;
            i++;
            s->Nop += 1;
        }
        else
        {
            //arr[k] = R[j];
            setValue(s, k, getData(R, j));
            s->Nop += 5;
            j++;
            s->Nop += 1;
        }
        k++;
        s->Nop += 1;
    }

    /* копируем оставшиеся элементы стека L,если таковые остались */
    while (i < n1)
    {
        //arr[k] = L[i];
        setValue(s, k, getData(L, i));
        s->Nop += 6;
        i++;
        k++;
        s->Nop += 2;
    }

    /* копируем оставшиеся элементы временного стека R,если таковые остались */
    while (j < n2)
    {
        //arr[k] = R[j];
        setValue(s, k, getData(R, j));
        s->Nop += 5;
        j++;
        s->Nop += 1;
        k++;
        s->Nop += 1;
    }
}




int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    // Эксперимента
    // Инициализация очереди и заполнение хранилища ключей
    int i, start, end;
    // Хранилище 3000 элементов
    int Key[3000];
    int N = 300;//начальное количество
    stack stack_list;

    for (i = 0; i < 3000; i++)
    {
        // Заполнение хранилища ключей случайными числами до 10000
        Key[i] = rand() % 9999;
    }

    for (i = 0; i < 10; i++)
    {
        for (int z = N - 300; z < N; z++)
        {
            stack_list.push(Key[z]);
        }

        stack_list.Nop = 0;
        start = GetTickCount64();
        //сортируем
        mergeSort(&stack_list, N);
        end = GetTickCount64();

        //stack_list.display();

        cout << "Номер сортировки: " 
            << i + 1 
            << " Колличество отсортированных элементов: "
            << N 
            << " Время сортировки (ms): " 
            << end - start
            << " Колличество операций (N_op): "
            << stack_list.Nop 
            << "\n";
        N = N + 300;//шаг в 300

    }

    //stack *s = new stack();
    //s->push(11);
    //s->push(22);
    //s->push(33);
    //s->push(44);
    //s->display();

    ////cout << getData(s, 3) << endl;
    ////setValue(s, 1, 56);

    //mergeSort(s,4);

    //s->display();

    //int end = clock();
    //cout << "\n" << end << endl;

}