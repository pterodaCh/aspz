# README

## Опис

Ця практична робота містить кілька програм на C, які демонструють роботу з пам'яттю, її переповненням і зміною розміру пам'яті за допомогою функцій, таких як `malloc`, `free`, `realloc` та `reallocarray`. Кожна програма має на меті тестувати різні сценарії, пов'язані з динамічним виділенням пам'яті та її маніпуляцією.


## Програми

### 1. Дослідити скільки пам’яті може виділити malloc(3) за один виклик?
У 64-бітному Linux size_t буде дорівнювати 8 байтам, що, звичайно, в бітах дорівнює 8 * 8 = 64. Отже, максимальна кількість пам'яті, яку можна виділити за один виклик malloc(3) дорівнюватиме 2^64

Вивід на x86_64 для 32-біт, передавши компілятору ключ -m32
```
root@:/home/ptero/ASPZ/practice4 # gcc -M32 task1. c -o task1_32 -Wall -1M
root@:/home/ptero/ASPZ/practice4 # ./task1_32
sizeof size_t = 4; Max value of the param to Malloc = 4294967296
```
Це 4 ГБ, вся VAS 32-розрядного процесу.

Вивід на x86_64:
```
root@:/home/ptero/ASPZ/practice4 # gcc task1.c -o task1 -lM
root@:/home/ptero/ASPZ/practice4 # ./task1
sizeof size_t = 8; Max value of the param to Malloc = 18446744073709551616
```
Це 16 EB. Отже, у 64-бітній ОС malloc(3) може виділити максимум 16 EB за один виклик, теоретично.
На практиці, очевидно, це буде неможливо, тому що, звичайно, це весь користувацький режим VAS самого процесу. Насправді, кількість пам'яті, яку можна виділити, обмежена кількістю вільної пам'яті, доступної на купі. Пам'ять для malloc(3) може надходити і з інших областей VAS. Існує обмеження на розмір сегмента даних; за замовчуванням він зазвичай необмежений, що насправді означає, що немає ніякого штучного обмеження, накладеного ОС.

### 2. Що станеться, якщо передати malloc(3) від’ємний аргумент?
Ця програма на C перевіряє поведінку функції `malloc` при виділенні великих блоків пам'яті. Вона перевіряє наступні сценарії:

- Множення двох найбільших значень для типу `int` (`INT_MAX`), що може призвести до переповнення.
- Виділення пам'яті за допомогою функції `malloc` з переповненими підписаними та беззнаковими значеннями.
- Спроба виділити пам'ять з негативним значенням.
```
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # gcc task2_1.c -o task2
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # ./task2

ld_num2alloc = 2147483647000000
szt_num2alloc = 2147483647000000
Malloc(2147483647000000) returns 0x0
Malloc(2147483647000000) returns 0x0
3. short int used: Malloc(6144) returns 0x48020413000
4. short int used: Malloc(-4096) returns 0x0
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 #
```

### 3. Що станеться, якщо використати malloc(0)?
Небагато та в залежності від реалізації. Malloc(3) поверне:
- NULL
- вказівник, відмінний від NULL, який можна передати у free

Відкомпілюємо через `ltrace`
```
root@:/home/ptero/ASP2/practice4/aspz/practice_4 # ltrace ./task3.out
couldn't determine base address of [vdso]
couldn't load ELF object [vdso]: No such file or directory
_libc_start1(1, 0x821338608, 0x821338618, 0x2df7cfe1bcc0, 0x4005c2 <unfinished.. >
malloc (0) = 0x203da4008008
free (0x203da4008008) = <void>
exited (status 0)
```
### 4. Знаходження помилок
Якщо одразу викликається free(), а потім знову malloc() з тією самою величиною буде повернено той самий адрес пам'яті. 
```
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # gcc -Wall task4.c -o task4
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # ./task4
iterayion 0: using 0x31a8fb009000
iterayion 1: using 0x31a8fb009000
iterayion 2: using 0x31a8fb009000
iterayion 3: using 0x31a8fb009000
iterayion 4: using 0x31a8fb009000
```
Втім можна додати `ptr = NULL`` і тоді отримаємо такий результат. Адреси зміняться
```
iterayion 0: using 0x5561040
iterayion 1: using 0x55620c0
iterayion 2: using 0x5564810
iterayion 3: using 0x5569670
iterayion 4: using 0x5570be0
```
### 5. Що станеться, якщо realloc(3) не зможе виділити пам’ять?
Функція `realloc()` використовується для зміни розміру деякого блоку пам'яті. Якщо це вдається зробити без переміщення даних, то результуючий показник буде співпадати з вихідним ptr. Якщо змінити розмір блоку пам'яті без його переміщення неможливо, функція поверне вказівник на новий блок, а старий буде звільнено. Але якщо зміна розміру блоку пам'яті в даний момент взагалі неможлива навіть з його переміщенням, функція поверне нульовий показник, що може спричинити сегфолт.
```
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # gcc -Wall task5.c -o task5
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # ./task5
Segmentation fault (core dumped)
```
### 6. Якщо realloc(3) викликати з NULL або розміром 0, що станеться?
Якщо ptr є нульовим вказівником, функція realloc поводиться як функція malloc для вказаного розміру.
```
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # gcc task6.c -o task6
root@:/home/ptero/ASP2/practice4/aspz/practice_4 # ./task6
realloc (NULL, 10)
Success: ptr1 = 0xb8755c13000, Memory allocated
realloc (ptr, 0)
MeMory1: 0xb8755c16000
```
### 7. Перевірка коду за допомогою `ltrace`
Ця програма на C демонструє використання функції `reallocarray` для динамічного виділення та зміни розміру пам'яті для масиву структур. Вона спочатку виділяє пам'ять для масиву з 1000 елементів типу `struct sbar`, а потім зменшує його розмір до 500 елементів. 
`ltrace ./task7. out`
```
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # ltrace ./task7. out
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
libc_start1(1, 0x820703de0, 0x820703df0, 0x3adb16eabcc0, 0x400622 <unfinished
>
reallocarray (0, 1000, 4, 0x270a3b604dee1e7d, 0x400622) = 0x48505a09000
reallocarray (0x48505a09000, 500, 4, 0x270a3b604dee1e7d, 10) = 0x48505a13000
free(0x48505a13000) = <void>
exited (status 0) ++++4+
```
### 8. Імітація витоку пам’яті та засічіть її за допомогою valgrind

Ця програма демонструє виділення пам'яті та навмисне провокування витоку пам'яті за допомогою інструменту `valgrind` 
- Профілює програми
- Автоматично виявляє витоки пам'яті
- Інстурмент динамічного аналізу
  
Використавши `valgrind ./task8. out` було виявлено втрату 20 байтів пам'яті.
```
### Виконання програми у терміналі root@:/home/ptero/ASP2/practice4/aspz/practice_4 # gcc task_var3. c -o task8. out
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 # valgrind ./task8. out
== 1353 == Memcheck, a Memory error detector
== 1353 == Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
== 1353 == Using Valgrind-3.24.0 and LibVEX; rerun with -h for copyright info
== 1353 == COMMand: ./task8.out
== 1353 ==
hHel1o
== 1353 ==
== 1353 == HEAP SUMMARY:
in use at exit: 4,116 bytes in 2 blocks
total heap usage: 2 allocs, 0 frees, 4,116 bytes allocated

== 1353 == LEAK SUMMARY:
definitely lost: 20 bytes in 1 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
still reachable: 0 bytes in 0 blocks
suppressed: 4,096 bytes in 1 blocks

== 1353 == Rerun with -- leak-check=full to see details of leaked Memory

== 1353 == For lists of detected and suppressed errors, rerun with: -s
== 1353 == ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 #

```
