#include <stdio.h>
#define foo(x, ...) _Generic(x, char*: printf(x), int: printf("%d %d", x, ...), default: printf("non"))


int main() {

}