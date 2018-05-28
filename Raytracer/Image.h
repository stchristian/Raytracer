#pragma once
#include "headers/math/Math.h"

class Image
{
	int width, height;
	Vec3f *data = nullptr;
public:
	Image() = default;
	Image(int _width, int _height);
	~Image();

	Vec3f& operator()(int x, int y) const;
	void set_dimension(int _width, int _height);
	Vec3f* operator&();

	int get_width() const { return width; }
	int get_height() const { return height; }

	bool save_to_bitmap(const char* file_name);
	bool load_from_bitmap(const char* file_name);
private:
	char* bmpdata_to_rgbarray(char* data, int width, int height);
};