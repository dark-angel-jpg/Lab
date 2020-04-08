МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ
Федеральное государственное автономное образовательное учреждение высшего образования
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №5<br/> по дисциплине "Программирование"
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
## Лабораторная работа №5
Работа с текстовыми файлами<br>
**Цель:** 1. Научиться работать с текстовыми файлами;<br>2.Закрепить навыки работы со структурами.

**Ход работы:**
**1.** Из предоставленного репозитория был скачан файл **train1.csv**.
**2.** На основании файла **data_dictionary.txt** была создана структура для чтения записей из файла **train1.csv**:
```cpp
enum class Pclass {First=1, Second, Third};
enum class Sex { Male, Female };
enum Embarked { C, Q, S };

struct Passenger{
    int id;
    bool survival;
    Pclass pclass;
    std::string name;
    Sex sex;
    double age;
    short int sibsp;
    short int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    Embarked embarked;
};
```
**3.** Ознакомилась с форматом файлов *CSV* и были считаны все записи в вектор.<br>
**4.** Рассчитаны и сохранены в новый файл **File1.txt** с предоставленными характеристиками (Таблица 1).<br>
Код:
```cpp
#include <iostream>
#include<vector>
#include<fstream>
#include<string>

enum class Pclass {First=1, Second, Third};
enum class Sex { Male, Female };
enum Embarked { C, Q, S };

struct Passenger{
    int id;
    bool survival;
    Pclass pclass;
    std::string name;
    Sex sex;
    double age;
    short int sibsp;
    short int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    Embarked embarked;
};

std::vector<Passenger> passengers;
std::vector<int> children;

std::string readuntil(std::ifstream& fin, char end = '\r') {  //функция, которая принимает 1 строку до '\r' 
    std::string s = "";
    char buffer;
    while (fin.read(&buffer, 1)) {
        if (buffer != end) s += buffer;
        else break;
    }
    return s;
}

int end = -1;
int lastEndSize = 1;

std::string readuntilstr(std::string str, std::string endStr) {  //
    int begin = end + lastEndSize;
    end = str.find(endStr, begin);
    lastEndSize = endStr.size();
    return str.substr(begin, end - begin);
}

std::string shtatw(Embarked max) { // функция дле перевода штатов
    if (max == 0)  return "C";
    else if (max == 1) return "Q";
    else return "S";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::ifstream fin("train1.csv");

    	if (!fin)
    {
        std::cout << "Uh oh, something went wrong!";
        exit(1);
    }

    std::ofstream fout("File1.txt");
    std::string line;
    readuntil(fin, '\r');  //Пропускаем первую строчку файла (заголовки для таблицы);

    while (true) {

        end = -1;  //сбрасываем readuntil в начало;

        line = readuntil(fin, '\r');
        	if (line == "") break;
        Passenger p;
        p.id = std::stoi(readuntilstr(line, ","));
        p.survival = std::stoi(readuntilstr(line, ","));
        p.pclass = (Pclass)std::stoi(readuntilstr(line, ",\""));
        p.name = readuntilstr(line, "\",");
        p.sex = readuntilstr(line, ",") == "male" ? Sex::Male : Sex::Female;

        std::string ag = readuntilstr(line, ",");
        	if (ag == "") p.age = -1;
        	else p.age = std::stod(ag);

        p.sibsp = std::stoi(readuntilstr(line, ","));
        p.parch = std::stoi(readuntilstr(line, ","));
        p.ticket = readuntilstr(line, ",");
        p.fare = std::stod(readuntilstr(line, ","));
        p.cabin = readuntilstr(line, ",");

        std::string em = readuntilstr(line, ",");
        	if (em == "C") p.embarked = Embarked::C;
        	else if (em == "Q") p.embarked = Embarked::Q;
        	else p.embarked = Embarked::S;

        passengers.push_back(p); //добавление заполненой структуры пассажира в вектор
    }

   int calive = 0,
        fclass = 0,
        sclass = 0,
        thclass = 0,
        female = 0,
        male = 0;
    double average_age = 0;
    int female_all = 0,
        male_all = 0;
    double average_female = 0,
           average_male = 0;
    int shtat[3]{};
    int age_all = 0;
    Embarked shtat_max = C;

    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i].survival) {
            calive++;
            	if (passengers[i].pclass == Pclass::First) fclass++;
            	else if (passengers[i].pclass == Pclass::Second) sclass++;
            	else thclass++;
				
            	if (passengers[i].sex == Sex::Female) female++;
            	else male++;
        };
        if (passengers[i].age != -1) {
            average_age += passengers[i].age;
            age_all++;
            	if (passengers[i].sex == Sex::Female) {
            		female_all++;
                	average_female += passengers[i].age;
            	}
            	else {
                	male_all++;
                	average_male += passengers[i].age;
            	}
        }
        
		shtat[passengers[i].embarked]++;
        
      	if (passengers[i].age < 18 && passengers[i].age!=-1) children.push_back(passengers[i].id);
  }
    average_age /= age_all;
    average_female /= female_all;
    average_male /= male_all;
	
    	if (shtat[shtat_max] < shtat[Q]) shtat_max = Q;
    	if (shtat[shtat_max] < shtat[S]) shtat_max = S;

    fout << "Общее число выживших:" << calive << '\n'
        << "Число выживших из 1 класса:" << fclass << '\n'
        << "Число выживших из 2 класса:" << sclass << '\n'
        << "Число выживших из 3 класса:" << thclass << '\n'
        << "Количество выживших женщин:" << female << '\n'
        << "Количество выживших мужчин:" << male << '\n'
        << "Средний возраст пассажира:" << average_age << '\n'
        << "Средний женский возраст:" << average_female << '\n'
        << "Средний мужской возраст:" << average_male << '\n'
        << "Штат, в котором село больше всего пассажиров:" << shtatw(shtat_max) << '\n'
		<< "Список идентификаторов несовершеннолетних (младше 18) пассажиров:" << '\n';
    
    for (int i = 0; i < children.size(); i++) {
        if (i == children.size() - 1) {
            fout << children[i];
            break;
        }
		
        fout << children[i] << ",";
    }
    
    fout.close();
    fin.close();
}

```
Для просмотра результата: [File1](https://github.com/dark-angel-jpg/Lab/blob/master/File1.md).

**Вывод:** В данной лабораторной работе, я ознакомилась с форматом файлов CSV, научилась работать с текстовыми файлами и закрепила навыки работы со структурами.

