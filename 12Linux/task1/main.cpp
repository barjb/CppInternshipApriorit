#include "copying.hpp"
#include <sys/sendfile.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "usage ./app fileIn fileOut\n");
        exit(EXIT_FAILURE);
    }
    return copy(argv[1], argv[2]);
}