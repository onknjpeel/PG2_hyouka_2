#pragma once
unsigned int GetColor(int red, int green, int blue, int alpha) {
	unsigned int colorCode = 0;

	colorCode |= static_cast<unsigned int>(red) << 24;
	colorCode |= static_cast<unsigned int>(green) << 16;
	colorCode |= static_cast<unsigned int>(blue) << 8;
	colorCode |= static_cast<unsigned int>(alpha);

	return colorCode;
}