# README

## Опис

Ця практична робота містить кілька програм на C, які демонструють роботу з пам'яттю, її переповненням і зміною розміру пам'яті за допомогою функцій, таких як `malloc`, `free`, `realloc` та `reallocarray`. Кожна програма має на меті тестувати різні сценарії, пов'язані з динамічним виділенням пам'яті та її маніпуляцією.

---

## Програми

1. **Програма 1: Дослідити скільки пам’яті може виділити malloc(3) за один виклик?**

   
8. **Завдання 8: Напишіть програму для імітації витоку пам’яті та засічіть її за допомогою valgrind**

Ця програма демонструє виділення пам'яті та навмисне провокування витоку пам'яті, аби опісля виявити за допомогою valgrind - інструментального фреймворку для побудови інструментів динамічного аналізу. Він може автоматично виявити багато керованих пам'яток та детально профілювати ваші програми.

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
== 1353 ==
== 1353 ==
== 1353 ==
== 1353 ==
== 1353 ==
== 1353 == Rerun with -- leak-check=full to see details of leaked Memory
== 1353 ==
== 1353 == For lists of detected and suppressed errors, rerun with: -s
== 1353 == ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
root@:/home/ptero/ASPZ/practice4/aspz/practice_4 #

== 1353 ==
== 1353 ==
== 1353 ==

definitely lost: 20 bytes in 1 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
still reachable: 0 bytes in 0 blocks
suppressed: 4,096 bytes in 1 blocks
