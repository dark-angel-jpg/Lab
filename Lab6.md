МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования<br>

<br/><br/>

### Отчёт по лабораторной работе №6<br/> по дисциплине "Программирование"
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

Симферополь, 2020
## Лабораторная работа №6
### Погодный информер<br>
**Цель:**<br> 1. Закрепить навыки разработки многофайловых приложений;<br>
2. Изучить способы работы с API web-сервиса;<br>
3. Изучить процесс сериализации/десериализации данных.<br>

**Ход работы:**<br>
**1.** Мой API ключ от **openweathermap.org** : 5969ed9944347a8190a2d06de0207006.<br>
**2.** Полный код программы:<br>
```cpp
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <fstream>

std::string extractIcon(const nlohmann::json& json)
{
    auto weather = json["weather"];
    for (auto& el : weather.items())
    {
        return el.value()["icon"];
    }
}

std::string doubleToStr(double d)
{
    std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << d;
    return ss.str();
}

void replace(std::string* str, std::string what, std::string replaceWith) {
	int a = str->find(what);
	if (a != -1) str->replace(a, what.length(), replaceWith);
}

void gen_response(const httplib::Request& req, httplib::Response& res) {
    httplib::Client cli("api.openweathermap.org", 80);

    auto wres = cli.Get("/data/2.5/forecast?q=Simferopol&appid=5969ed9944347a8190a2d06de0207006&units=metric");
    if (wres && wres->status == 200) 
    {
        auto json = nlohmann::json::parse(wres->body);

        std::ifstream fin("Template.html");
        std::stringstream buffer;
        buffer << fin.rdbuf();

        std::string templ;
        templ = buffer.str();

        replace(&templ, "{city.name}", json["city"]["name"].get<std::string>());

        int dateIndex = 0, iconIndex = 0, tempIndex = 0, amount = 5;
        std::string lDate = "";
        for (int i = 0; i < json["cnt"].get<int>(); i++) {
            dateIndex = templ.find("{list.dt}", dateIndex);
            iconIndex = templ.find("{list.weather.icon}", iconIndex);
            tempIndex = templ.find("{list.main.temp}", tempIndex);

            std::string date = json["list"][i]["dt_txt"].get<std::string>();
            if (date.substr(0, date.find(' ')) != lDate) {
                replace(&templ, "{list.dt}", date);
                replace(&templ, "{list.weather.icon}", json["list"][i]["weather"][0]["icon"].get<std::string>());
                replace(&templ, "{list.main.temp}", doubleToStr(json["list"][i]["main"]["temp"].get<double>()));
            
                lDate = date.substr(0, date.find(' '));
                amount--;
            }

            if (amount == 0) break;
        }

        res.set_content(templ, "text/html");
    }
    else
        res.set_content("Failed to open api.openweather.org", "text/plain");
}

int main(void)
{
    httplib::Server serv;           // cервер
    serv.Get("/", gen_response);    // gen_response
    serv.listen("localhost", 3000); // порт 3000
}
```
**3.** Рисунок 1 с демонстрацией работы программы:

![](https://github.com/dark-angel-jpg/Lab/blob/master/image%20for%20lab%206/Аннотация%202020-06-18%20133840.jpg?raw=true)

>Рисунок 1 - Работа программы. 

**Вывод:** На данной лабораторной работе, я закрепила навыки разработки многофайловых приложений, изучила способы работы с API web-сервиса и процесс сериализации/десериализации данных. 
