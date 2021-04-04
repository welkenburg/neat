#include<bmpCreator>
#include<random>

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
const char* path = { "noise.bmp" };
const int width = 480;
const int height = 360;
char imageBuffer[height * (width * 3 + width % 4)];

int main() {
	chronometer timer;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float color = (rand() < 0x7fff/2) * 255;
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 0] = color;
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 1] = color;
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 2] = color;
			/*imageBuffer[j * (width * 3 + width % 4) + i * 3 + 0] = rand() * 255;
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 1] = rand() * 255;
			imageBuffer[j * (width * 3 + width % 4) + i * 3 + 2] = rand() * 255;*/
		}
	}

	bmpImage image(width,height,imageBuffer);
	image.save(path);
	timer.stop();

}