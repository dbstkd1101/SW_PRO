#include <string>
#include <queue>
using namespace std;

queue<char**> hist;

const int LN = 4e3 + 3;

int W, H;

char img[LN][LN];
char imgTmp[LN][LN];

void init(char image[]) {
	W = image[0] * 100 + image[1];
	H = image[1] * 100 + image[2];

	int k = 0;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			img[j][i] = image[k++];
		}
	}
}
void resize(int scale, char result[]) {
	memset(imgTmp, 0, sizeof(imgTmp));
	if (scale == 1) {
		for (int i = 1; i < H; i+=2) {
			for (int j = 1; j < W; j+=2) {
				imgTmp[i / 2][j / 2] = ((img[i][j] + img[i+1][j] + img[i][j+1] + img[i+1][j+1])/4);
			}
		}
	}
	if (scale == 0) {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				imgTmp[i][j] = img[i][j];
				imgTmp[i+1][j] = img[i][j];
				imgTmp[i][j+1] = img[i][j];
				imgTmp[i+1][j+1] = img[i][j];
			}
		}
	}

	for (int i = 0; imgTmp[i]; i++) {
		result[i] = *imgTmp[i];
	}
}
void rotate(int angle, char result[]) {
	switch (angle) {
	case 0:
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				imgTmp[j][H - 1 - i] = img[i][j];
			}
		}
		break;
	case 1:
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				imgTmp[H-1-i][W - 1 - j] = img[i][j];
			}
		}
		break;

	case 2:
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				imgTmp[W - 1 - j][H - 1 - i] = img[i][j];
			}
		}
		break;
	}

	for (int k = 0; imgTmp[k]; k++) {
		result[k] = *imgTmp[k];
	}
}
void flip(int dir, char result[]) {


}
void pixelEdit(int px, int py, char color, char result[]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (px == i || py == j) {
				result[i * W + j] = img[i][j] = color;
			}
			else result[i * W + j] = img[i][j];
		}
	}
}
void undo(char result[]) {
	

}