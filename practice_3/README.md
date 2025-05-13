# Практична 3
## Завдання 1
У завданні потрібно використати перелічені команди, щоб поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Потрібно виконати завдання з root-правами та без них.
```
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
```
##

Спершу виконаємо та подивимося результат команд з root-правами, оскільки це рівень доступу, який користувач отримує автоматично.

```docker run -it dockeraspz bash```

![image](https://github.com/user-attachments/assets/b418b8dd-bf68-4645-90cd-65eb63b57e80)

Ця команда дозволить нам переглянути результат запропонованих команд без root-прав
```docker run -it --user $USER dockeraspz bash```

![image](https://github.com/user-attachments/assets/8d84fcd6-5be1-488e-9897-6ae975cb81a0)

Порівнюючи результати виконання команд, помічаємо, що відмінності відсутні. Скоріше за все у завданні малося на увазі про привілейовані права доступу. Їх можна отримати використовуючи прапорець `--privileged`. Тоді й справді результат різнитиметься

![image](https://github.com/user-attachments/assets/bff620af-8c2f-43b5-85d2-bb3be3d3747d)

