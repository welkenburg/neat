#pragma once
#include<iostream>
#include<fstream>
#include<chrono>
#include<complex>

class bmpImage {
private:
	char fileHeader[14] = { (char)66,(char)77,(char)255,(char)255,(char)255,(char)255,(char)0,(char)0,(char)0,(char)0,(char)15,(char)0,(char)0,(char)0 };
	char imageHeader[40] = { (char)40,(char)0,(char)0,(char)0,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)1,(char)0,(char)24,(char)0,(char)0,(char)0,(char)0,(char)0,(char)255,(char)255,(char)255,(char)255,(char)35,(char)46,(char)0,(char)0,(char)35,(char)46,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0,(char)0 };

	void replaceHeader(char* buffer, int x, int position) {
		for (int i = 3; i >= 0; i--) {
			buffer[position + i] = (x >> i * 8) & 0xFF;
		}
	}

public:
	int width;
	int height;
	char * pixelBuffer;

	bmpImage(int fwidth, int fheight, char* fpixelBuffer) {
		width = fwidth;
		height = fheight;
		pixelBuffer = fpixelBuffer;
	}

	void save(const char* path) {
		replaceHeader(fileHeader, 54 + width * height * 3, 2);
		replaceHeader(imageHeader, width, 4);
		replaceHeader(imageHeader, height, 8);
		replaceHeader(imageHeader, width * height * 3, 20);

		std::ofstream out(path, std::ios::out | std::ios::binary);
		if (!out) std::cout << "Error : cannot write to the specified path" << std::endl;
		else {
			out.write(fileHeader, sizeof(fileHeader));
			out.write(imageHeader, sizeof(imageHeader));
			out.write(pixelBuffer, height * (width * 3 + width % 4));
			out.close();
		}
	}

	float HueToRGB(float v1, float v2, float vH) {
		if (vH < 0) vH += 1;
		if (vH > 1) vH -= 1;
		if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
		if ((2 * vH) < 1) return v2;
		if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);
		return v1;
	}

	char * rgb(float hue, float l) {
		float h = (hue < 0) ? (atan(1) * 4 + hue) / (atan(1) * 4) : hue / (atan(1) * 4);
		float v2 = (l < 0.5) ? 2 * l : 1;
		float v1 = 2 * l - v2;
		return new char[3]{ (char)round(255 * HueToRGB(v1, v2, h + (1.0f / 3))),(char)round(255 * HueToRGB(v1, v2, h)),(char)round(255 * HueToRGB(v1, v2, h - (1.0f / 3))) };
	}
};

class chronometer {
public:
	std::chrono::system_clock::time_point initalTime;
	chronometer() {
		initalTime = std::chrono::system_clock::now();
	}

	void stop() {
		auto finalTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = finalTime - initalTime;
		float fDeltaTime = deltaTime.count();
		std::cout << "finished in " << fDeltaTime << "s" << std::endl;
	}
};

class fractal {
public:
	const std::complex<long double> one = 1;
	const std::complex<long double> two = 2;

	int maxInteration = 500;
	long double epsilon = 0.001;
	char setColor[3] = { (char)220,(char)220,(char)220 };
	char outsideColor[3] = { (char)255,(char)255,(char)255 };
	float * rgb = new float[3] { 0.5,0.3,0.8 };

	long double complexAbsolute(std::complex<long double> z) {
		return std::real(z) * std::real(z) + std::imag(z) * std::imag(z);
	}

	char* basic(long double n, bool in = false) {
		if (n < maxInteration && in == false)
			return outsideColor;
		else
			return setColor;
	}

	char* escapedTime(long double n, bool in = false) {
		if (n == maxInteration || in)
			return setColor;
		else
			return new char[3]{ (char)((cos(n * rgb[0]) + 1) * 255 / 2),
								(char)((cos(n * rgb[1]) + 1) * 255 / 2),
								(char)((cos(n * rgb[2]) + 1) * 255 / 2) };
	}

	char* potential(long double n, long double abs, bool in = false) {
		if (n == maxInteration || in)
			return setColor;
		else {
			float K = 1; //K est une variable
			long double V = log(abs) / pow(2, n);
			long double x = log(V) / K;
			return new char[3]{ (char)((cos(x * rgb[0]) + 1) * 255 / 2),
								(char)((cos(x * rgb[1]) + 1) * 255 / 2),
								(char)((cos(x * rgb[2]) + 1) * 255 / 2) };
		}
	}
};