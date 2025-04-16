# Рабочее место кассира

Простой C++-проект, моделирующий рабочее место кассира.

## 📦 Зависимости

Для работы с JSON-файлами используется сторонняя библиотека **jsoncpp**. ([Документация](https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html))

Вы можете установить её с помощью [vcpkg](https://github.com/Microsoft/vcpkg):

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install jsoncpp
```

Также можно вручную собрать библиотеку из исходников:
[GitHub jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## ⚙️ Сборка проекта

Перед сборкой укажите пути к заголовочным файлам и скомпилированной библиотеке jsoncpp в файле `CMakeLists.txt`, установив значения переменных:

- `PATH_TO_INCLUDE_DIRECTORIES`
- `PATH_TO_LINK_DIRECTORIES`

При необходимости изменить входные JSON-файлы с товарами и продавцами — откройте файл `./src/Config.cpp` и скорректируйте пути в соответствующих переменных.

Для сборки проекта выполните:

```bash
mkdir build
cd build
cmake ..
make
```

После успешной сборки в папке `build` появится исполняемый файл `workplace`. Запустите его для работы с приложением:

```bash
./workplace
```
## 📘 Инструкция по работе с приложением

- Если приложение выводит нумерованный список команд, вводить необходимо **только номер** нужного пункта, **без текста** команды.

<details>
<summary>Пример</summary>

```
Please, select the action:
    1. Sign in
    2. Quit the program
1
```
</details>

---

- Для возврата в стартовое меню на этапе авторизации используйте ключевое слово **`back`**, введя его в поле логина.

<details>
<summary>Пример</summary>

```
Please, select the action:
    1. Sign in
    2. Quit the program
1
Type "back" to return to start menu
Enter your login: back
```
</details>

---

- Аналогично, чтобы **изменить способ оплаты** после его выбора, введите **`change`** в поле для ввода суммы.

<details>
<summary>Пример</summary>

```
The amount of order: 399.50
Please, choose a payment type:

    1. Cash
    2. Non-cash
    3. Cancel the order
    
2
To change payment type, please type "change"
Enter the amount of money in the bank account: 
change
```
</details>

---

- При формировании заказа доступны следующие команды:

  - **`add`** — добавить товар
  - **`remove`** — удалить товар
  - **`end`** — завершить формирование заказа

  **Синтаксис команд:**

  ```
  add/remove <название_или_штрихкод> <количество>
  ```

  Параметр `<количество>` необязателен. Если его не указать, по умолчанию будет добавлена или удалена **1 единица** товара.

---

## 💬 Комментарий

В демонстрационных целях пароли сотрудников **не зашифрованы** и хранятся в открытом виде. Это решение принято осознанно — для упрощения проверки корректности работы приложения, особенно при подключении внешнего списка работников.
