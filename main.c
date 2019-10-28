#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char **argv) {
    Display* display;
    int screen_number;
    Window window;
    XSetWindowAttributes attributes;
    unsigned long attributemask;
    Visual *visual;

    GC gc;
    XGCValues gcv;
    XEvent event;

    display = XOpenDisplay("");
    screen_number = DefaultScreen(display);
    visual= CopyFromParent;

    attributes.background_pixel= WhitePixel(display, screen_number);
    attributes.border_pixel = WhitePixel(display, screen_number);

    attributes.event_mask = KeyPressMask|ExposureMask|ButtonPressMask|StructureNotifyMask|EnterWindowMask|LeaveWindowMask|PointerMotionMask;

    attributemask = CWBackPixel|CWBorderPixel|CWEventMask;

    window = XCreateWindow(display, RootWindow(display, screen_number),
            400,400,800,600,0,
            CopyFromParent,InputOutput,visual,attributemask,&attributes);
    XMapRaised(display, window);
    XFlush(display);

    gcv.foreground = 12345;
    gc=XCreateGC(display, window, GCForeground, &gcv);

    while (1) {
        XNextEvent(display,&event);
        printf("An event %d arrived: ", event.type);
        switch (event.type) {
            case Expose:
                //XFillArc(display, window, gc, 10, 10, 150, 150, 0, 10000);
                printf ("We got an expose event, redraw!\n");
                break;

            case KeyPress:
                printf ("We got a key event and the keycode is %d\n", event.xkey.keycode);
                break;

            case ButtonPress:
                printf ("We got a mouse click at (%d,%d)\n", event.xbutton.x, event.xbutton.y);
                break;

            case ConfigureNotify:
                printf ("Structure notify\n");
                break;

            case EnterNotify:
                printf("Pointer enter Window\n");
                break;

            case LeaveNotify:
                printf("Pointer leave Window\n");
                break;

            case MotionNotify:
                printf("Pointer move detected: x = %d, y = %d\n", event.xmotion.x, event.xmotion.y);
                break;

            default:
                printf ("Something else??, type = %d\n", event.type);
        }
    }
}
