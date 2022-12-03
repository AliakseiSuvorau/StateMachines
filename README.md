Как запускать проект?
```
git clone https://github.com/AliakseiSuvorau/StateMachines
cd StateMachines
mkdir build
cd build
cmake ..
make
```
Далее для запуска тестов нужно написать:
```
./../bin/Google_Tests_run
```
Для запуска самого проекта:
```
./../bin/prac2
```


1) Используйте в качестве номеров состояний целые числа начиная с 1 подряд.
2) Укажите ввод в файле в следующем формате:
<br/> количество состояний
<br/> количество переходов
<br/> (далее идет описание переходов)
<br/> состояние буква состояние
<br/> ...
<br/> состояние буква состояние
<br/> номер начального состояния
<br/> количество конечных состояний
<br/> все номера конечных состояний через пробел

3) Для ввода epsilon-перехода используйте символ "-".

