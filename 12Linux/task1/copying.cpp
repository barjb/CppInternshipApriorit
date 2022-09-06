#include "copying.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

int copy(char *in, char *out)
{
    FILE *file_in = fopen(in, "r");
    FILE *file_out = fopen(out, "w");
    if (file_in == NULL)
    {
        fprintf(stderr, "Could not open %s. Exiting...\n", in);
        exit(EXIT_FAILURE);
    }
    if (file_out == NULL)
    {
        fprintf(stderr, "Could not open %s. Exiting...\n", out);
        exit(EXIT_FAILURE);
    }
    struct stat st;
    stat(in, &st);

    int in_fd = fileno(file_in);
    int out_fd = fileno(file_out);
    int sent = sendfile(out_fd, in_fd, 0, st.st_size);

    fclose(file_in);
    fclose(file_out);

    return sent;
}