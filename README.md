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
