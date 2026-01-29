#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>


void rotate_mouse(Display *display, int r, double t)
{

	Window root = DefaultRootWindow(display);
	XWindowAttributes attrs;

	XGetWindowAttributes(display, root, &attrs);

	int width  = attrs.width;
	int height = attrs.height;

    double rad = t * M_PI / 180.0;
    int x = width/2 + (int)(r * cos(rad));
    int y = height/2 + (int)(r * sin(rad));


    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
}

int main()
{
    Display *display = XOpenDisplay(NULL);
	
	if (!display)
	{
		fprintf(stderr, "X11 display gen error");
		return(1);
	}

    if (!display)
        return 1;

    while (1)
    {
        for (int t = 0; t < 360; t++)
        {
            rotate_mouse(display, 100, t);
            XSync(display, 0);
            usleep(2000); // slow it down so you can see it
        }
        sleep(120);
    }

    return 0;
}


// compile with -lX11 -lm
