#include "MyStr.h"
#include <stdio.h>

unsigned int slen(const char* s) {
    const char* sc = s;
    while (*sc != '\0') {
        ++sc;
    }
    return sc - s;
}
char* stok(char* s, const char* ct) {
    char* sbegin = s;
    const char *sc1, *sc2;

    if (sbegin == NULL) {
        return NULL;
    }

    for (sc1 = sbegin; *sc1 != '\0'; ++sc1) {
        for (sc2 = ct; *sc2 != '\0'; ++sc2) {
            if (*sc1 == *sc2) {
                return (char*)sc1;
            }
        }
    }

    return sbegin;
}
int scmp(const char* p1, const char* p2) {
    const unsigned char* s1 = (const unsigned char*)p1;
    const unsigned char* s2 = (const unsigned char*)p2;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}

unsigned int sspn(const char* string, const char* reject) {
    const char* p;
    const char* r;
    unsigned int count = 0;

    for (p = string; *p != '\0'; ++p) {
        for (r = reject; *r != '\0'; ++r) {
            if (*p == *r) {
                return count;
            }
        }
        ++count;
    }
    return count;
}

char* scpy(char* destination, const char* src) {
    char* temp = destination;

    while (*src != '\0') {
        *destination++ = *src++;
    }
    return temp;
}
