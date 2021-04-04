#include <iostream>
#include <complex>
#include <bmpCreator>

/*
360p = 480 x 360
480p = 858 x 480 - SD
720p = 1280 x 720 - HDready
1080p = 1920 x 1080 - FullHD
1200p = 1920 x 1200 - FullHD
1440p = 2560 x 1440 - Quad HD
1600p = 2560 x 1600 - Quad HD
2160p = 3840 x 2160 - 4K
2880p = 5120 x 2880 - 5K
4320p = 7689 x 4320 - 8K
6480p = 11534 x 6480 - 12K
8640p = 15360 x 8640 - 16K too big!
*/

const char* path = { "julias.bmp" };
const int width = 1280;
const int height = 720;
char imageBuffer[height * (width * 3 + width % 4)];


long double centerPoint[2] = { 0,0 };
float zoom = -0.5;
int maxValue = 100;

long double startX = centerPoint[0] - 2 / pow(2, zoom);
long double startY = centerPoint[1] - (2 / pow(2, zoom)) * height / width;
long double coeficient = 4 / (pow(2, zoom) * width);

std::complex<long double> c(-0.12,0.70);

int main() {
	fractal julias;
	julias.rgb = new float[3] {0.5,0.5,0.5};
	julias.setColor[0] = 90;
	julias.setColor[1] = 90;
	julias.setColor[2] = 255;
	chronometer timer;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			std::complex<long double> z(startX + coeficient * i, startY + coeficient * j);
			std::complex<long double> derivative = 1;
			bool in = false;
			int finalN = julias.maxInteration;
			for (int n = 0; n < julias.maxInteration; n++) {
				if (julias.complexAbsolute(derivative) < julias.epsilon * julias.epsilon) {
					in = true;
					finalN = n;
					break;
				}
				if (julias.complexAbsolute(z) > maxValue) {
					finalN = n;
					break;
				}
				derivative = derivative * julias.two * z;
				z = z * z + c;
			}
			char* colors = julias.basic(finalN, in);
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 0] = colors[0];
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 1] = colors[1];
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 2] = colors[2];
		}
	}
	bmpImage set(width, height, imageBuffer);
	set.save(path);
	timer.stop();
	return 0;
}