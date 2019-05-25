/* clang-format off */
/*
Задание

Для заданного имени текущего пользователя обновить список входных файлов,
преобразовав пути, заданные относительно его домашнего каталога (вида
~/somedir), к абсолютным путям. Имя каталога (dir), в котором находятся домашние
каталоги пользователей, вводится с клавиатуры.

Вход:

delim: +
user name: jack
dir: /home/stud
paths:              ~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc

Выход:

new paths: /home/stud/games/packman.cpp + ~alex/docs + /home/stud/study/Prog/lab4.c + /usr/bin/gcc
*/
// gcc ./src/*.c -L../STR/ -lMyStr -o main
/* clang-format on */
#include <MyStr/MyStr.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH 260
#define MAX_USERNAME 15

int check(char delim, char* paths, char* reject);
void input(char* user, char* dir, char* paths);
void process(char* paths, char* user, char* delim, char* dir);
void output(char* paths);

int main() {
    char* user = malloc(MAX_USERNAME * sizeof(char));
    char* dir = malloc(MAX_PATH * sizeof(char));
    char delim = '+';
    char* paths = malloc(MAX_PATH * 4 * sizeof(char));
    char reject[10] = {'\\', ':', '*', '?', '\"', '<', '>', '|'};
    input(user, dir, paths);

    char* istr;
    istr = stok(paths, "+");
    while (istr != NULL) {
        istr = stok(NULL, "+");
        if (check(delim, paths, reject)) {
            process(paths, user, &delim, dir);
            output(paths);
        }
    }
    return 0;
}
