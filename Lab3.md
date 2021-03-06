МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ
Федеральное государственное автономное образовательное учреждение высшего образования
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №3<br/> по дисциплине "Программирование"
<br/>

студентки 1 курса группы ПИ-б-о-191(2)
Павловой Татьяны Викторовны
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
## Лабораторная работа №3
**Дешифровка текста из изображения** <br>
**Цель:**
1. Закрепить навыки разработки программ использующих операторы цикла;
2. Закрепить навыки разработки программ использующих массивы;
3. Освоить методы подключения сторонних библиотек. <br>
**Ход работы:** <br>
**1\.** Для работы с изображением bmp я скачала библиотеку  https://github.com/marc-q/libbmp. Далее я добавила libbmp.cpp в папку созданного мной проекта. На рисунке 1 продеманстрировано, что файл подключен к проекту:

![1](https://github.com/dark-angel-jpg/Lab/blob/master/image%20lab%203/eOJ5QIPJ5gk.jpg?raw=true)
>Рис. 1. Добавленный libbmp.cpp файла к проекту.

Потом в папке с проектом я создала папку include с заголовочным файлом из библиотеки libbmp.h. И чтобы подключить данный файл, как дополнительный файл мне потребовалось: зайти в свойства "Обозревателя решений" -> во всплывающем окне выбираем "Свойства конфигурации">"C/C++">"Общие". Добавляем путь на папку include в "Дополнительные каталоги включаемых файлов" и в коде проекта подключаем файл с помощью директивы *#include "libbmp.h"*. На Рисунке 2 изображено подключенный заголовочный файл к проекту:

![2](https://github.com/dark-angel-jpg/Lab/blob/master/image%20lab%203/iWJcGHbxdYo.jpg?raw=true)
>Рис. 2. Подключенный файл libbmp.h к проекту.

**2\.** Мой номер варианта, в соответствии с журналом, 9, изображенный на Рисунке 3, и ключ прилагающийся к нему: `11b 11g 11r 01b 01g 01r 10b 10g`.

![3](https://raw.githubusercontent.com/dark-angel-jpg/Lab/master/image%20lab%203/pic9.bmp)
>Рис. 3. Изображение, прилагающеся к заданию.

**3\.** Код программы для декодирования сообщения:

C++
```cpp
#include <iostream>
#include"libbmp.h"
#include<cstdlib>
void vv(int mass[8]) {  //преобразовательная функция
    char c = 0;
    for (int i = 7; i >= 0; i--) {
        c = c | (mass[7-i] << i);  //заносим в переменную код побитовым сдвигом 
    }
    if (c == 0) exit(0);  //когда си-строка заканчивается нуль-терминатором, выходит из функции main 
    std::cout << c;
}
void addb(int z) {  //функция, которая записывает 8 младших битов в массив
    static int i = 0;
    static int buff[8];
    buff[i] = z;
    i++;
    if (i == 8) {  //когда массив заполняется восьмью битами, вызывает преобразовательную функцию
        vv(buff);
        i = 0;
    }
}
int main()  //11b 11g 11r 01b 01g 01r 10b 10g
{
    BmpImg img; 
    img.read("pic9.bmp");  //чтение картинки
    int w = img.get_width();  //вычисляем битовые значения ширины
    int h = img.get_height();  //вычисление битовых значений высоты
    for (int y = h - 1; y >= 0; y--) {  //цикл который идет с нижнего правого угла налево и переходит на следующую строку выше, опять же начиная справа
        for (int x = w - 1; x >= 0; x--) {
            int r = img.red_at(x, y);  //заносим в переменную ключ
            int g = img.green_at(x, y);
            int b = img.blue_at(x, y);
            addb(b&1);  //вызываем функцию и заносим в нее младший бит 
            addb(g&1);
            addb(r&1);
        }
    }
```
Вывод программы:

![4](https://github.com/dark-angel-jpg/Lab/blob/master/image%20lab%203/hQAzLkvtxEg.jpg?raw=true)
>Рис. 4. Консольный вывод программы.

**Вывод:** во время данной лабораторной работы, я закрепила навыки работы с операторами цикла, массивами и освила методы подключения сторонних библиотек.
