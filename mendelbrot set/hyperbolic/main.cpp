#include <bmpCreator>
#include <iostream>
#include <complex>

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
const char* path = { "hyperbolic.bmp" };
const int width = 480;
const int height = 360;
char imageBuffer[height * (width * 3 + width % 4)];


long double centerPoint[2] = { 0,0 };
float zoom = 0;
int maxValue = 100;

long double startX = centerPoint[0] - 2 / pow(2, zoom);
long double startY = centerPoint[1] - (2 / pow(2, zoom)) * height / width;
long double coeficient = 4 / (pow(2, zoom) * width);

int main() {
	fractal mendelbrot;
	mendelbrot.rgb = new float[3]{ 0.5,0.5,0.5 };
	chronometer timer;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			std::complex<long double> c(startX + coeficient * i, startY + coeficient * j);
			std::complex<long double> z = c;
			std::complex<long double> derivative = 1;
			bool in = false;
			int finalN = mendelbrot.maxInteration;
			for (int n = 0; n < mendelbrot.maxInteration; n++) {
				if (mendelbrot.complexAbsolute(derivative) < mendelbrot.epsilon * mendelbrot.epsilon) {
					in = true;
					finalN = n;
					break;
				}
				if (mendelbrot.complexAbsolute(z) > maxValue) {
					finalN = n;
					break;
				}
				derivative = derivative * mendelbrot.two * z;
				z = z * z + c;
			}
			char* colors = mendelbrot.potential(finalN, mendelbrot.complexAbsolute(z), in);
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