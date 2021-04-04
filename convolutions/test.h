#pragma once
#include<iostream>
#include<fstream>
#include<chrono>

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
8640p = 15360 x 8640 - 16K
*/

class bmpImage {
private:
	char fileHeader[14] = { (char)66,(char)77,(char)255,(char)255,(char)255,(char)255,(char)0,(char)0,(char)0,(char)0,(char)15,(char)0,(char)0,(char)0 };
	char imageHeader[40] = { (char)40,(char)0,(char)0,(char)0,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)1,(char)0,(char)24,(char)0,(char)0,(char)0,(char)0,(char)0,(char)255,(char)255,(char)255,(char)255,(char)35,(char)46,(char)0,(char)0,(char)35,(char)46,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0 };

	void replaceHeader(char* buffer, int x, int position) {
		for (int i = 3; i >= 0; i--) {
			buffer[position + i] = (x >> i * 8) & 0xFF;
		}
	}

	int nibbleToInt(char* nibble) {
		int number = 0;
		for (int i = 0; i < sizeof(*nibble); i+=2) {
			number += (nibble[i] >> 4) * pow(16,i) + (nibble[i]* pow(16, i+1));
		}
		return number;
	}

public:
	int width;
	int height;
	char* pixelBuffer;

	bmpImage(int fwidth, int fheight, char* fpixelBuffer) {
		width = fwidth;
		height = fheight;
		pixelBuffer = fpixelBuffer;
	}
	void load(const char* path) {
		std::streampos size;
		char* buffer;

		std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			buffer = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(buffer, size);
			file.close();
			pixelBuffer = buffer;
			width = nibbleToInt(new char[4]{ buffer[4],buffer[5],buffer[6],buffer[7] });
			height = nibbleToInt(new char[8]{ buffer[9],buffer[10],buffer[11],buffer[12] });
			std::cout << "width: " << width << "\nheight: " << height << "\n" << pixelBuffer << std::endl;
		}
	}

	void save(const char* path) {
		replaceHeader(fileHeader, 54 + width * height * 3, 2);
		replaceHeader(imageHeader, width, 4);
		replaceHeader(imageHeader, height, 8);
		replaceHeader(imageHeader, width * height * 3, 20);

		std::ofstream out(path, std::ios::out | std::ios::binary);
		if (!out) std::cout << "Error : cannot write to" << path << std::endl;
		else {
			out.write(fileHeader, sizeof(fileHeader));
			out.write(imageHeader, sizeof(imageHeader));
			out.write(pixelBuffer, height * (width * 3 + width % 4));
			out.close();
		}
	}
};

class time {
public:
	std::chrono::system_clock::time_point initalTime;
	time() {
		initalTime = std::chrono::system_clock::now();
	}

	void stop() {
		auto finalTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = finalTime - initalTime;
		float fDeltaTime = deltaTime.count();
		std::cout << "finished in " << fDeltaTime << "s" << std::endl;
	}
};