# АСПЗ 
## 1. Ліміт time_t
Ця задача порушує проблему 2038 року. Ця проблема стосується програм і систем, в яких використовується представлення часу за стандартом POSIX (час Unix). Цей стандарт використовує кількість секунд, які пройшли від початку «епохи», тобто з півночі 1 січня 1970 року. Таке представлення часу — стандарт для Unix-подібних операційних систем. Для зберігання секунд використовується тип даних time_t, визначений як signed int, тобто у форматі 32-бітного цілого числа зі знаком. Найпізніша дата, яка може бути представлена таким форматом в стандарті POSIX — 19 січня 2038. Введення 64-бітного формату вносить нову дату - 4 грудня 292 277 026 596 року.

Для коректного відображення змін, оскільки порівнюються два формати, використовуєтсья прапорець `-m32`
```
root@:/home/ptero/ASPZ/practice2 # gcc task1.c -o task1
root@:/home/ptero/ASPZ/practice2 # ./task1
Word size: 64
Max value time_t: 9223372036854775807
Date and time, when time_t ends: ??? ??? ?? ?? : ?? : ?? ????
root@:/home/ptero/ASPZ/practice2 # gcc -M32 task1.c -o task1
root@:/home/ptero/ASPZ/practice2 # ./task1
Word size: 32
Max value time_t: 2147483647
Date and time, when time_t ends: Tue Jan 19 05:14:07 2038
root@:/home/ptero/ASPZ/practice2 #
```
## 2. Аналіз сегментів файлу
### 1. Використання команд `size` та `ls -l`
- `size`: використовується для відображення розмірів різних секцій (текст, дані, BSS) виконуваного файлу або об'єктного файлу
- `ls -l`: відображає детальну інформацію про файли у каталозі, включаючи права доступу, власника, групу, розмір, дату модифікації 
```
root@:/home/ptero/ASPZ/practice2 # gcc task2.c -o task2.out
root@:/home/ptero/ASPZ/practice2 # ls -1 task2.out
Frwxr-xr-x 1 root ptero 8200 Mar 28 23:36 task2. out
root@:/home/ptero/ASPZ/practice2 # size task2.out
text data bbs  dec hex file name
1077 552 16 1645 0x66d task2_1
```

### 2. Додавання глобального масиву без ініціалізації
Масив потрапляє в сегмент BSS
```
root@:/home/ptero/ASPZ/practice2 # size task2_2
text data bbs  dec hex file name
1077 552 4032 5661 0x161d task2_2
```
### 3. Додавання глобального масиву з ініціалізацією
Тепер масив переміститься із BSS у DATA сегмент
```
root@:/home/ptero/ASPZ/practice2 # size task2_3
text data bbs  dec hex file name
1077 4568 16 5661 0x161d task2_3
```
### 4. Додавання локальних масивів
Результат команди `size` на програмі із локальним неініціалізованим масивом
```
root@:/home/ptero/ASPZ/practice2 # size task2_4
text data bbs  dec hex file name
1085 552 16 1653 0x675 task2_4
```
Та ініціалізованим
```
root@:/home/ptero/ASPZ/practice2 # size task2_4
text data bbs  dec hex file name
1117 552 16 1683 0x695 task2_4
```
Простий локальний масив зберігається у стеку, а ініціалізований потрапляє у DATA сегмент.

### 5. Налагодження та оптимізація
Для налагодження використовувалися прапорці `-g` та `-gdwarf-5`
```
root@:/home/ptero/ASPZ/practice2 # gcc -g task2.c -o task2_5debug
root@:/home/ptero/ASPZ/practice2 # ls -1 task2_5debug
Frwxr-xr-x 1 root ptero 8896 Mar 27 23:16 task2_5debug
root@:/home/ptero/ASPZ/practice2 # size task2_5debug
text data bbs  dec hex file name
1085 552 16 1653 0x675 task2_5debug
root@:/home/ptero/ASPZ/practice2 # gcc -gwarf-5 task2.c -o task2_5debug1
gcc: error: unrecognized debug output level 'warf-5'
root@:/home/ptero/ASPZ/practice2 # gcc -gdwarf-5 task2.c -o task2_5debug1
root@:/home/ptero/ASPZ/practice2 # ls -1 task2_5debug1
-rwxr-xr-x 1 root ptero 8904 Mar 27 23:17 task2_5debug1
root@:/home/ptero/ASPZ/practice2 # size task2_5debug1
text data bbs  dec hex file name
1085 552 16 1653 0x675 task2_5_debug1
```
## 3. Стек та Куча
### 1. Приблизне розташування стека
Скомпілювавши код отримаємо
```
The stack top is near 0x8206b66ec
```
### 2.  Визначення розташування сегментів даних, тексту та купи
```
root@:/home/ptero/ASPZ/practice2 # ./task3_2
Text segment (func): 0x400612
Data segent (global): 0x401a58
Data segment (static): 0x401a5c
Heap segment : 0x3dcf32408008
Stack top: 0x8207045f4
```
### 3. Збільшення розміру стека
Вершина стека змінюється при виклику нових функцій або оголошенні великих масивів.
```
Stack top before allocation: 0x8209810fc
Stack top after allocation: 0x8209774a0
Stack depth 1, address: 0x8209810dc
Stack depth 2, address: 0x8209810ac
Stack depth 3, address: 0x82098107c
Stack depth 4, address: 0x82098104c
Stack depth 5, address: 0x82098101c
```
## 4. Дослідження стек процесу за допомогою утиліти gstack або налагоджувача GDB
У мануалах FreeBSD немає утиліти `gstack` (cеред запропонованих аналогів - pstack), тому це завдання виконується тільки за допомогою GDB. Його може бути використано у декілька способів:
- За його допомогою можна дослідити пам'ять процесора, на якому він працює виконується
- Може використовуватися для аналізу дампа процесора після паніки
- Його можна використовувати для налагодження іншої системи в інтерактивному режимі через послідовний або через дротовий зв'язок.	У цьому режимі процесор можна зупинити і однокроковий
  
Скомпілювана програма виводить наступне
```
in  main; &localvar = 0x8208dd9fc
1182
in foo; &localvar = 0x8208dd9cc
in bar; &localvar = 0x8208dd9ac
in bar_is_now_closed; &localvar = 0x8208dd98c
Now blocking on pause()...
```
Якщо використати `pstack` отримаємо трасування запущеної програми
```
root@:/home/ptero/ASPZ/practice2 # pstack 1182
pstack: unable to open executable '[vdso]': No such file or directory
1182: /home/ptero/ASPZ/practice2/task4
thread -1 (running)
0x8212bb77a _sigsuspend (4006db, 0, 8a5d0044, 5aafda65, 400742, 5) + a
0x4006db bar_is_now_closed (40070d, 0, 8a5d0044, 5aafda65, 400742, 5) + 39
0x40070d bar (40073f, 0, 8a5d0044, 5aafda65, 400742, 5) + 2f
0x40073f foo (40078e, 0, 208dda88, 8, 0, 1) + 2f
0x40078e Main (21207c3a, 8, 1, 0, 208dda88, 8) + 4c
__ libc_start1 (4005f0, 0, 0, 0, bbc03008, 2085) + 12a
start (bbc03008, 2085, 0, 0, 0, 0) + 30
```
Повертаючись до GDB
## Примітки
Для виконання завдання необхідно встановити: 
- pstack
- gdb


