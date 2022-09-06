#include <stdio.h>
#include <X11/Xlib.h>

#include <iostream>

char *key_name[] = {
    "first",
    "second (or middle)",
    "third",
    "fourth",
    "fivth"};

int main(int argc, char **argv)
{
    Display *display;
    XEvent xevent;
    Window window;

    // create Display structure from NULL,
    // compare to NULL, XOpenDisplay returns null when fails to create Disply
    if ((display = XOpenDisplay(NULL)) == NULL)
        return -1;

    // all of the screens on display can be now used
    std::cout << XDefaultScreen(display) << std::endl;
    // Applications should not directly modify any part of the Display and Screen structures.
    // The members should be considered read-only, although they may change as the result of other operations on the display.

    // window = DefaultRootWindow(display);
    window = XCreateSimpleWindow(display, XDefaultRootWindow(display), 0, 0, 800, 600, 1, 0, 0);

    XWindowAttributes attribs;
    std::cout << XGetWindowAttributes(display, window, &attribs);
    std::cout << " w,h: " << attribs.width << ", " << attribs.height << std::endl;

    Window child = XCreateSimpleWindow(display, window, 0, 0, 800, 600, 0, 0, 0);

    XAllowEvents(display, AsyncBoth, CurrentTime);
    //  | EnterWindowMask | LeaveWindowMask
    XGrabPointer(display,
                 window,
                 1,
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
                 GrabModeAsync,
                 GrabModeAsync,
                 None,
                 None,
                 CurrentTime);
    XMapWindow(display, window);
    while (1)
    {
        XNextEvent(display, &xevent);

        switch (xevent.type)
        {
        case MotionNotify:
            printf("Mouse move      : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
            break;
        case ButtonPress:
            printf("Button pressed  : %s\n", key_name[xevent.xbutton.button - 1]);
            break;
        case ButtonRelease:
            printf("Button released : %s\n", key_name[xevent.xbutton.button - 1]);
            break;
        case EnterWindowMask:
            printf("Enter window ");
            break;
        case LeaveWindowMask:
            printf("Leave window ");
            break;
        }
    }
    return 0;
}