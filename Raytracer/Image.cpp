#include "Image.h"

#include <Windows.h>
#include <cstdio>
#include <fstream>

/*Save image data to bmp file*/
bool Image::save_to_bitmap(const char* file_name)
{
	using namespace std;
	long width_pad = (width * 3 + 3) & 0xfffffffc; //bmp requires rows to be 4 byte (WORD) aligned. This will be the new row size
	long img_size = width_pad * height;

	//Creating & filling neccessary headers
	BITMAPFILEHEADER bmfh;
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	bmfh.bfType = 'B' | ('M' << 8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize =  bmfh.bfOffBits + img_size;

	BITMAPINFOHEADER info;
	memset(&info, 0, sizeof(BITMAPINFOHEADER));
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = BI_RGB;
	info.biSizeImage = img_size;
	info.biXPelsPerMeter = 0x0ec4;
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	//Write data to file.
	ofstream bmpFile(file_name, ios::binary);
	if (bmpFile.is_open()) {
		if (!bmpFile.write((char*)&bmfh, sizeof(BITMAPFILEHEADER))) { bmpFile.close(); return false; }
		if (!bmpFile.write((char*)&info, sizeof(BITMAPINFOHEADER))) { bmpFile.close(); return false; }

		//Color data
		char* pixels = new char[img_size];
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				pixels[i * width_pad + j * 3 + 0] = (int)fmax(fmin(data[i * width + j].z * 255.5, 255), 0);
				pixels[i * width_pad + j * 3 + 1] = (int)fmax(fmin(data[i * width + j].y * 255.5, 255), 0);
				pixels[i * width_pad + j * 3 + 2] = (int)fmax(fmin(data[i * width + j].x * 255.5, 255), 0);
			}
		}

		if (!bmpFile.write(pixels, img_size)) { bmpFile.close(); delete[] pixels; return false; }
		delete[] pixels;
		bmpFile.close();
		return true;
	}
	else {
		return false;
	}
}

bool Image::load_from_bitmap(const char* file_name)
{
	using namespace std;
	ifstream bmpFile(file_name, ios::binary);
	if (bmpFile.is_open())
	{
		//Reading bitmap header
		BITMAPFILEHEADER bmpheader;
		if (!bmpFile.read((char*)&bmpheader, sizeof(BITMAPFILEHEADER))) { bmpFile.close(); return false; }
		//Reading info header
		BITMAPINFOHEADER bmpinfo;
		if (!bmpFile.read((char*)&bmpinfo, sizeof(BITMAPINFOHEADER))) { bmpFile.close(); return false; }

		if (bmpheader.bfType != 'MB') { bmpFile.close(); return false; }
		if (bmpinfo.biCompression != BI_RGB) { bmpFile.close(); return false; }
		if (bmpinfo.biBitCount != 24) { bmpFile.close(); return false; }
		width = bmpinfo.biWidth;
		height = bmpinfo.biHeight;
		long size = bmpheader.bfSize - bmpheader.bfOffBits;

		char* buffer = new char[size];
		bmpFile.seekg(bmpheader.bfOffBits, ios_base::beg);
		if (!bmpFile.read(buffer, size)) { bmpFile.close(); delete[] buffer; return false; }
		bmpFile.close();
		
		char* converted = bmpdata_to_rgbarray(buffer, width, height);
		delete[] buffer;

		if (nullptr != data)
		{
			delete[] data;
		}
		 
	}
	else
	{
		return false;
	}
}

char* Image::bmpdata_to_rgbarray(char* buffer, int width, int height)
{
	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)
		padding++;
	int psw = scanlinebytes + padding;

	char* newbuf = new char[width * height * 3];
	long bufpos = 0;
	long newpos = 0;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < 3 * width; x += 3)
		{
			newpos = y * 3 * width + x;
			bufpos = (height - y - 1) * psw + x;

			newbuf[newpos] = buffer[bufpos + 2];
			newbuf[newpos + 1] = buffer[bufpos + 1];
			newbuf[newpos + 2] = buffer[bufpos];
		}
	return newbuf;
}

Image::Image(int _width, int _height) :width(_width), height(_height) //Vigyazz negativ ertekek
{
	data = new Vec3f[width * height];
}

Image::~Image()
{
	delete[] data;
}

void Image::set_dimension(int _width, int _height)
{
	delete[] data;
	width = _width; height = _height; data = new Vec3f[width * height];
}

Vec3f* Image::operator&()
{
	return data;
}

Vec3f& Image::operator()(int x, int y) const
{
	//Vigyazz tulindexeles!
	return data[y * width + x];
}
