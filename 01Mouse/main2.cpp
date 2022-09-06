#include <stdio.h>
#include <gpm.h>

int my_handler(Gpm_Event *event, void *data)
{
    if (event->type & GPM_DOWN)
    {
        if (event->buttons & GPM_B_LEFT)
            system("./l.sh");
        if (event->buttons & GPM_B_RIGHT)
            system("./r.sh");
        if (event->buttons & GPM_B_MIDDLE)
            system("./m.sh");
    }
    return 0;
}

int main()
{
    Gpm_Connect conn;
    int c;
    conn.eventMask = ~0;  /* Want to know about all the events */
    conn.defaultMask = 0; /* don't handle anything by default */
    conn.minMod = 0;      /* want everything */

    if (Gpm_Open(&conn, 0) == -1)
        printf("Cannot connect to mouse server\n");
    gpm_handler = my_handler;
    while ((c = Gpm_Getc(stdin)) != EOF)
        Gpm_Close();
    return 0;
}