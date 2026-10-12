#include <raylib.h>
#include <stdio.h>

#define FRAME_COUNT 222
#define ANIM_FPS 24.0f

int main(void) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT |
                   FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH);

    InitWindow(800, 800, "Hatsune Miku");
    SetExitKey(KEY_NULL);
    SetTargetFPS(30);

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
