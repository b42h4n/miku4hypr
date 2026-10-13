#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRAME_COUNT 222
#define ANIM_FPS 24.0f
#define WIN_W 800
#define WIN_H 800
#define FIX_FRAMES 30

#ifdef USE_X11
typedef unsigned long XID;
typedef XID Atom;
typedef XID Window;
typedef struct _XDisplay Display;

extern Display *XOpenDisplay(const char *);
extern int XCloseDisplay(Display *);
extern Atom XInternAtom(Display *, const char *, int);
extern int XChangeProperty(Display *, Window, Atom, Atom, int, int,
                           const unsigned char *, int);
extern Window XRootWindow(Display *, int);
extern int XSendEvent(Display *, Window, int, long, void *);
extern int XFlush(Display *);

typedef struct {
    int type;
    unsigned long serial;
    int send_event;
    Display *display;
    Window window;
    Atom message_type;
    int format;
    long data[5];
} XClientMessageEventCustom;

static void ForceAlwaysOnTopX11(void) {
    void *handle = GetWindowHandle();
    if (!handle) return;
    Window window = (Window)(uintptr_t)handle;
    if (!window) return;

    Display *display = XOpenDisplay(NULL);
    if (!display) return;

    Atom wmState        = XInternAtom(display, "_NET_WM_STATE", 0);
    Atom wmStateAbove   = XInternAtom(display, "_NET_WM_STATE_ABOVE", 0);
    Atom wmStateSticky  = XInternAtom(display, "_NET_WM_STATE_STICKY", 0);
    Atom wmWindowType   = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 0);
    Atom wmTypeDock     = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", 0);

    XChangeProperty(display, window, wmWindowType, 4, 32, 0,
                    (const unsigned char *)&wmTypeDock, 1);

    XClientMessageEventCustom xev = {0};
    xev.type = 33;                 
    xev.window = window;
    xev.message_type = wmState;
    xev.format = 32;
    xev.data[0] = 1;              
    xev.data[1] = (long)wmStateAbove;
    xev.data[2] = (long)wmStateSticky;
    xev.data[3] = 1;

    XSendEvent(display, XRootWindow(display, 0), 0, 0x100000L | 0x80000L, &xev);
    XFlush(display);
    XCloseDisplay(display);
}
#endif

static int parse_int(const char *s, int *out) {
    char *end;
    long v = strtol(s, &end, 10);
    if (end == s || *end != '\0') return 0;
    *out = (int)v;
    return 1;
}

int main(int argc, char **argv) {
    int hasPos = 0, posX = 0, posY = 0;

    if (argc >= 3) {
        if (parse_int(argv[1], &posX) && parse_int(argv[2], &posY)) {
            hasPos = 1;
        } else {
            fprintf(stderr, "Usage: %s [x y]n",
                    argv[0], argv[0]);
            return 1;
        }
    }

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT |
                   FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH);

    InitWindow(WIN_W, WIN_H, "Hatsune Miku");
    SetExitKey(KEY_NULL);
    SetTargetFPS(30);

#ifdef USE_X11
    ForceAlwaysOnTopX11();
#endif

    int targetX, targetY;

    if (hasPos) {
        targetX = posX;
        targetY = posY;
    } else {
        int mon = GetCurrentMonitor();
        Vector2 monPos = GetMonitorPosition(mon);
        targetX = (int)monPos.x + GetMonitorWidth(mon) - WIN_W;
        targetY = (int)monPos.y + GetMonitorHeight(mon) - WIN_H;
    }

    SetWindowPosition(targetX, targetY);
    int posApplied = 0;

    Texture2D frames[FRAME_COUNT] = {0};
    char fileName[64];

    for (int i = 0; i < FRAME_COUNT; i++) {
        snprintf(fileName, sizeof(fileName), "assets/frame_%03d.png", i + 1);

        Image img = LoadImage(fileName);

        if (img.data != NULL) {
            ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            Color *pixels = (Color *)img.data;
            int totalPixels = img.width * img.height;

            for (int j = 0; j < totalPixels; j++) {
                if (pixels[j].r < 35 && pixels[j].g < 35 && pixels[j].b < 35) {
                    pixels[j].a = 0;
                }
            }

            frames[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    while (!WindowShouldClose()) {
        if (posApplied < FIX_FRAMES) {
            SetWindowPosition(targetX, targetY);
            posApplied++;
        }

        int currentFrame = (int)(GetTime() * ANIM_FPS) % FRAME_COUNT;

        BeginDrawing();
            ClearBackground(BLANK);
            if (frames[currentFrame].id != 0) {
                DrawTexture(frames[currentFrame], 100, -340, WHITE);
            }
        EndDrawing();
    }

    for (int i = 0; i < FRAME_COUNT; i++) {
        if (frames[i].id != 0) UnloadTexture(frames[i]);
    }

    CloseWindow();
    return 0;
}
