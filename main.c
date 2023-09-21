#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: x11-on-resolutionchange COMMAND\n");
    return 1;
  }

  const char *command = argv[1];
  system(command);

  Display *display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Failed to open display\n");
    return 1;
  }

  Window root = DefaultRootWindow(display);
  XSelectInput(display, root, StructureNotifyMask);

  int width = 0;
  int height = 0;
  XEvent event = {0};

  while (true) {
    XNextEvent(display, &event);
    if (event.type == ConfigureNotify) {
      if (width != event.xconfigure.width || height != event.xconfigure.height) {
        fprintf(stdout, "Resolution changed to %dx%d\n", event.xconfigure.width, event.xconfigure.height);
        system(command);
      }
      width = event.xconfigure.width;
      height = event.xconfigure.height;
    }
  }

  return 0;
}
