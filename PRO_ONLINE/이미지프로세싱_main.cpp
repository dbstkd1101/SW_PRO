// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAIN_SIZE    2000
#define MAX_N        1000
#define MAX_SCALE    4

#define RESIZE       0
#define ROTATE       1
#define FLIP         2
#define PIXELEDIT    3
#define UNDO         4
#define END          5

const int THRESHOLD = 0x07FFFFFF;

extern void init(char image[]);
extern void resize(int scale, char result[]);
extern void rotate(int angle, char result[]);
extern void flip(int dir, char result[]);
extern void pixelEdit(int px, int py, char color, char result[]);
extern void undo(char result[]);

static char mainImage[MAIN_SIZE][MAIN_SIZE];
static char originalImage[(MAX_N * MAX_N) + 4];
static char userResult[(MAX_N * MAX_SCALE) * (MAX_N * MAX_SCALE) + 4];

static void inputImage(void)
{
    int w, h;
    scanf("%d %d", &w, &h);

    for (int i = 0; i < h; i++)
        scanf("%s", mainImage[i]);
}

static void extractImage(void)
{
    int x, y, w, h;
    scanf("%d %d %d %d", &x, &y, &w, &h);

    originalImage[0] = w / 100;
    originalImage[1] = w % 100;
    originalImage[2] = h / 100;
    originalImage[3] = h % 100;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            originalImage[i * w + j + 4] = mainImage[y + i][x + j];
}

static int getAnswer(char userResult[])
{
    int sum = 0;
    int size = (userResult[0] * 100 + userResult[1]) * (userResult[2] * 100 + userResult[3]);

    if (size > (MAX_N * MAX_SCALE) * (MAX_N * MAX_SCALE))
        return THRESHOLD + 1;

    for (int i = 0; i < size + 4; ++i) {
        sum += userResult[i] * (i + 1);
        sum &= THRESHOLD;
    }

    return sum;
}

static int run()
{
    int cmd = 0;
    int flag = 0;
    int answerSum = 0;
    int correct = 1;

    while (1) {
        scanf("%d", &cmd);

        //0
        if (cmd == RESIZE) {
            int scale;
            scanf("%d %d %d", &scale, &flag, &answerSum);
            resize(scale, userResult);
        }
        else if (cmd == ROTATE) {
            int angle;
            scanf("%d %d %d", &angle, &flag, &answerSum);
            rotate(angle, userResult);
        }
        else if (cmd == FLIP) {
            int direction;
            scanf("%d %d %d", &direction, &flag, &answerSum);
            flip(direction, userResult);
        }
        else if (cmd == PIXELEDIT) {
            int x, y, color;
            scanf("%d %d %d %d %d", &x, &y, &color, &flag, &answerSum);
            pixelEdit(x, y, (char)color, userResult);
        }
        else if (cmd == UNDO) {
            scanf("%d %d", &flag, &answerSum);
            undo(userResult);
        }
        else if (cmd == END) {
            break;
        }

        if (flag) {
            if (answerSum != getAnswer(userResult)) {
                correct = 0;
            }
        }
    }

    return correct;
}

int main(void)
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, success;
    scanf("%d %d", &T, &success);

    inputImage();

    for (int tc = 1; tc <= T; ++tc) {
        extractImage();
        init(originalImage);
        printf("#%d %d\n", tc, run() * success);
    }
    return 0;
}