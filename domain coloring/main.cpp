#include<bmpCreator>
#include<complex>

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
const char* path = { "function.bmp" };
const int width = 1280;
const int height = 720;
char imageBuffer[height * (width * 3 + width % 4)];

long double centerPoint[2] = { 0,0 };
float zoom = -1;
int maxValue = 100;

long double startX = centerPoint[0] - 2 / pow(2, zoom);
long double startY = centerPoint[1] - (2 / pow(2, zoom)) * height / width;
long double coeficient = 4 / (pow(2, zoom) * width);

const std::complex<long double> one(1, 0);
const std::complex<long double> onei(0, 1);

long double TWOPI = acos(-1) * 2;

char* basic(std::complex<long double> z) {
	return rgb(arg(z), 2 * atan(abs(z)) / (atan(1) * 4));
}

char* constlight(std::complex<long double> z) {
	return rgb(arg(z), 0.5);
}

char* magnitude(std::complex<long double> z) {
	//si e change : condition change
	int e = -10;
	int eMax = 100;
	while (e < eMax) {
		if ((pow(2, e) < abs(z) && pow(2, e + 1) >= abs(z)) || abs(z) <= pow(2, -10)) {
			break;
		}
		e++;
	}
	return rgb(arg(z), 0.2 + (1 - pow(0.5, fmod(abs(z), pow(2, e)))) / 2);
}

char* colorcells(std::complex<long double> z) {
	char hue[4][3] = {
		{0x00,0x64,0xFF},
		{0xFF,0x00,0x00},
		{0xFF,0xFF,0x00},
		{0x00,0xFF,0x00} };
	int pos = 4 * (arg(z) + acos(-1)) / TWOPI;
	if (pos > -1) return hue[pos];
	return new char[3]{ 0,0,0 };
}


char* blend(std::complex<long double> z) {
	long double h = (arg(z) + acos(-1)) / TWOPI;
	return new char[3]{ (char)(h * 255),(char)(h * 255),(char)(h * 255) };
}

int main() {
	chronometer timer;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::complex<long double> z(startX + coeficient * i, startY + coeficient * j);

			//z = z * z;
			//z = z * z * z * z * z - one;
			//z = (z - one) * (z + one) * (z + one) / ((z + onei) * (z - onei) * (z - onei));
			//z = exp(one / (z * z));
			z = cos(z) / sin(pow(z, 4) - one);

			char* color = basic(z);
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 0] = color[0];
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 1] = color[1];
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 2] = color[2];
		}
	}

	bmpImage image(width, height, imageBuffer);
	image.save(path);
	timer.stop();

}