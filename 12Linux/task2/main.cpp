#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int pipesfds[2];
    pipe(pipesfds);
    pid_t pid = fork();

    if (pid > 0)
    {
        close(pipesfds[1]);
        char *outString = NULL;
        char *tempString = NULL;
        int outStringLen = 0;
        int outStringSize = 1024;
        outString = (char *)malloc(outStringSize);
        if (outString == NULL)
        {
            fprintf(stderr, "Out of memory. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        FILE *fd_out = fopen("outfile.txt", "w+");
        char buf[1024];
        int readLen = 0;
        int outFD = fileno(fd_out);

        while ((readLen = read(pipesfds[0], buf, 1024)))
        {
            while (outStringLen + readLen > outStringSize)
            {
                outStringSize *= 2;
                tempString = (char *)realloc(outString, outStringSize);
                if (tempString == NULL)
                {
                    fprintf(stderr, "Out of memory. Exiting...\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    outString = tempString;
                }
            }
            strncat(outString, buf, readLen);
            outStringLen += readLen;
        }

        const char *additionalResponse = "\nHi!";
        int additionalResponseLen = 4;

        if (additionalResponseLen + outStringLen > outStringSize)
        {
            outStringSize *= 2;
            tempString = (char *)realloc(outString, outStringSize);
            if (tempString == NULL)
            {
                fprintf(stderr, "Out of memory. Exiting...\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                outString = tempString;
            }
        }

        strncat(outString, additionalResponse, additionalResponseLen);
        outStringLen += additionalResponseLen;
        write(outFD, outString, outStringLen);
        close(pipesfds[0]);
        fclose(fd_out);
        free(outString);
    }
    else
    {
        const char *message = "Hi daddy, I\'m your child!\0";
        close(pipesfds[0]);
        write(pipesfds[1], message, strlen(message));
        close(pipesfds[1]);
    }
}