// .h
// GameBoy Sprite Data Generator
// by Kyle Furey

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <map>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

/** Outputs the inputted sprite data as a C array. */
int main(int argc, const char* argv[]) {

	// Log title
	cout << "GameBoy Sprite Data Generator\n" << endl;

	// Iterate each argument
	for (int i = 0; i < argc; ++i) {

		// Load the image
		const char* path = argv[i];
		int width;
		int height;
		int channels;
		unsigned char* image = stbi_load(path, &width, &height, &channels, 4);
		if (image == nullptr) {

			// Not an image
			continue;
		}
		cout << '\"' << path << '\"' << endl;

		// Validate the image size
		if (width < 8 || height < 8) {

			// Invalid size
			cout << "Error: Image is not at least 8 x 8!" << endl;
			stbi_image_free(image);
			cout << endl;
			continue;
		}

		// Iterate each pixel
		unordered_set<int> colors;
		map<int, int> index_to_color;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {

				// Get color hex
				unsigned char* pixel = image + (y * width + x) * 4;
				int color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | (pixel[3] << 24);

				// Get index with color luminance
				unsigned char r = pixel[0];
				unsigned char g = pixel[1];
				unsigned char b = pixel[2];
				unsigned char a = pixel[3];
				int index = a != 0 ? (int)(255 - ((77 * r + 150 * g + 29 * b) >> 8)) : -1;

				// Track each color and luminance
				colors.insert(color);
				index_to_color[index] = color;
			}
		}

		// Validate colors
		if (colors.size() > 4) {

			// Too many colors
			cout << "Error: Too many colors!" << endl;
			stbi_image_free(image);
			cout << endl;
			continue;
		}
		if (index_to_color.size() < colors.size()) {

			// Bad palette
			cout << "Error: Bad palette! 2+ colors are identical in monochrome!" << endl;
			stbi_image_free(image);
			cout << endl;
			continue;
		}

		// Store the sprite data
		unsigned char indices[8][8]{};
		for (int y = 0; y < 8; ++y) {
			for (int x = 0; x < 8; ++x) {

				// Get index with color luminance
				unsigned char* pixel = image + (y * width + x) * 4;
				unsigned char r = pixel[0];
				unsigned char g = pixel[1];
				unsigned char b = pixel[2];
				unsigned char a = pixel[3];
				int index = a != 0 ? (int)(255 - ((77 * r + 150 * g + 29 * b) >> 8)) : -1;

				// Store each color by its palette index
				indices[y][x] = (unsigned char)distance(index_to_color.begin(), index_to_color.find(index));
			}
		}

		// Process the sprite data
		short palette[4]{};
		int index = 0;
		for (const auto& [luminance, color] : index_to_color) {
			unsigned char r = (color >> 0) & 0xFF;
			unsigned char g = (color >> 8) & 0xFF;
			unsigned char b = (color >> 16) & 0xFF;
			short gb = ((r >> 3) << 0) | ((g >> 3) << 5) | ((b >> 3) << 10);
			palette[index++] = gb;
		}
		unsigned char sprite[16]{};
		for (int y = 0; y < 8; ++y) {
			unsigned char low = 0;
			unsigned char high = 0;
			for (int x = 0; x < 8; ++x) {
				unsigned char index = indices[y][x];
				low |= (unsigned char)((index & 1) << (7 - x));
				high |= (unsigned char)(((index >> 1) & 1) << (7 - x));
			}
			sprite[y * 2] = low;
			sprite[y * 2 + 1] = high;
		}

		// Output the sprite data
		string name = filesystem::path(path).stem().string();
		cout << "const tile_t rom_tile_" << name << " = {\n\t";
		for (int i = 0; i < 16; ++i) {
			cout << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)sprite[i] << dec;
			if (i % 4 == 3) {
				cout << ",\n";
				if (i != 15) {
					cout << "\t";
				}
			}
			else {
				cout << ", ";
			}
		}
		cout << "};\nconst palette_t rom_palette_" << name << " = {\n\t";
		for (int i = 0; i < 4; ++i) {
			cout << "0x" << hex << uppercase << setw(4) << setfill('0') << (int)palette[i] << dec << ", ";
			if (i == 3) {
				cout << '\n';
			}
		}
		cout << "};" << endl;

		// Cleanup
		stbi_image_free(image);
		cout << endl;
	}

	// Await input
	cout << "Press enter to exit." << endl;
	cin.get();

	return 0;
}
