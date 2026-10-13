#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define FRAME_COUNT 222
#define ANIM_FPS 24.0f
#define WIN_W 800
#define WIN_H 800
#define FIX_FRAMES 30

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
            fprintf(stderr, "Использование: %s [x y]\nПример: %s -300 100\n",
                    argv[0], argv[0]);
            return 1;
        }
    }

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT |
                   FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH);

    InitWindow(WIN_W, WIN_H, "Hatsune Miku");
    SetExitKey(KEY_NULL);
    SetTargetFPS(30);

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
                int m = pixels[j].r > pixels[j].g ? pixels[j].r : pixels[j].g;
                if (pixels[j].b > m) m = pixels[j].b;

                if (m < 35) {
                    pixels[j] = BLANK;
                } else if (m < 70) {
                    pixels[j].a = (unsigned char)((m - 35) * 255 / 35);
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
