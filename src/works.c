#include <MyStr/MyStr.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260 // * 4

void input(char* user, char* dir, char* paths) {
    printf("user name:");
    scanf("%s", user);
    printf("dir:");
    scanf("%s", dir);
    printf("paths: \n");
    scanf("%s", paths);
}

int check(char delim, char* paths, char* reject, char* dir) {
    int pathNum = 1;
    int character = 1;
    int pathlen = 0;

    if (sspn(paths, reject) != slen(paths)) {
        printf("Have forbidden symbols %d\n", sspn(paths, reject));
        return 0;
    }

    if (paths[0] != '~' && paths[0] != '/') {
        printf("Wrong start, way %d: (symbol %d \"%c\")\n",
               pathNum,
               character,
               paths[0]);
        return 0;
    }

    for (char* bufp = paths; *bufp != '\0'; ++bufp) {
        pathlen++;
        if (*bufp == delim) {
            pathNum++;
            if (*(bufp + 1) != '/' && *(bufp + 1) != '~') {
                printf("Wrong start, way %d: (symbol %d \"%c\")\n",
                       pathNum,
                       character,
                       *bufp);
                return 0;
            }
            if (pathlen > MAX_PATH) {
                printf("Way too long %d", pathNum);
                return 0;
            } else {
                pathlen = 0;
            }
        }

        if (*bufp == '.' && *(bufp + 1) == '/' && *(bufp - 1) != '.'
            && *(bufp - 1) != '/') {
            printf("Invalid path %d: (symbol %d \"%c%c%c\")\n",
                   pathNum,
                   character,
                   *(bufp - 1),
                   *bufp,
                   *(bufp + 1));
            return 0;
        }

        if (*bufp == '/' && *(bufp + 1) == '/') {
            printf("Invalid construction, path %d: (symbol %d \"//\")\n",
                   pathNum,
                   character);
            return 0;
        }

        if (*bufp == '.' && *(bufp - 1) == '/' && *(bufp - 2) == delim) {
            printf("Invalid construction, path %d: (symbol %d \"%c/.\")\n",
                   delim,
                   pathNum,
                   character);
            return 0;
        }
        character++;
    }

    if (sspn(dir, reject) != slen(dir)) {
        printf("There are forbidden characters in the root(%d)\n",
               sspn(paths, reject));
        return 0;
    }

    for (char* bufp = dir; *bufp != '\0'; ++bufp) {
        if (*bufp == '.' && *(bufp + 1) == '/' && *(bufp - 1) != '.'
            && *(bufp - 1) != '/') {
            printf("Invalid root path путь");
            return 0;
        }

        if (*bufp == '/' && *(bufp + 1) == '/') {
            printf("Invalid root path путь");
            return 0;
        }

        if (*bufp == '.' && *(bufp - 1) == '/' && *(bufp - 2) == delim) {
            printf("Invalid root path путь");
            return 0;
        }
    }
    return 1;
}
void process(char* paths, char* user, char* delim, char* dir) {
    char* sc;
    int count;
    dir[slen(dir)] = '/';
    user[slen(user)] = '/';
    char* usersdir = malloc(MAX_PATH * sizeof(char));
    char* subusersdir = malloc(MAX_PATH * sizeof(char));
    scpy(usersdir, dir);
    scpy(subusersdir, dir);
    scpy(subusersdir + slen(dir), user);

    for (sc = paths; *sc != '\0'; sc++) {
        char* buf = malloc(MAX_PATH * sizeof(char));
        if (*sc == '~' && *(sc + 1) == '/') {
            scpy(buf, subusersdir);
            scpy(buf + slen(buf), sc + 2);
            scpy(sc, buf);
        } else if (*sc == '~' && *(sc + 1) != '/') {
            scpy(buf, usersdir);
            scpy(buf + slen(buf), sc + 1);
            scpy(sc, buf);
        }
    }

    int arrSize = slen(paths);
    int currSize = arrSize;

    for (sc = paths; *sc != '\0'; ++sc) {
        if (*sc == '.' && *(sc - 1) == '/' && *(sc + 1) == '/') {
            scpy((sc - 1), (sc + 1));
            paths[arrSize] = '\0';
            paths[arrSize - 1] = '\0';
            arrSize -= 2;
        } else if (*sc == '.' && *(sc - 1) == '.' && *(sc + 1) == '/') {
            sc -= 3;
            count = 4;
            currSize -= 4;
            while (*sc != '/') {
                --sc;
                ++count;
                --currSize;
            }
            scpy(sc, (sc + count));
            paths[currSize] = '\0';
            arrSize = currSize;
        }
    }
}
void output(char* paths) {
    printf("new paths: %s\n", paths);
}
