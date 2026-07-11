// .h
// GameBoy Sprite Data Generator
// by Kyle Furey

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

class pixel {
public:

	uint8_t a = 0;
	bool transparent = true;
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint32_t rgba8888 = 0;
	uint16_t bgr555 = 0;
	uint8_t luminance = 0;
	int32_t order = 0;

	pixel(stbi_uc* image) {
		a = image[3];
		if (a != 0) {
			transparent = false;
			r = image[0];
			g = image[1];
			b = image[2];
			rgba8888 = (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(b) << 16) | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(r);
			bgr555 = (b >> 3 << 10) | (g >> 3 << 5) | r >> 3;
			luminance = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
			order = UINT8_MAX - luminance;
		}
		else {
			order = -1;
		}
	}

	struct sort {
		bool operator()(const pixel& a, const pixel& b) const {
			if (a.bgr555 != b.bgr555 && a.luminance == b.luminance) {
				throw runtime_error("Bad palette! 2+ colors are identical in monochrome!");
			}
			return a.order < b.order;
		}
	};
};

class tile {
public:
	int raw_width = 0;
	int raw_height = 0;
	int raw_channels = 0;
	stbi_uc* image = nullptr;
	string path{};
	string name{};
	int width = 0;
	int height = 0;
	int channels = 0;
	size_t size = 0;
	vector<pixel> pixels{};
	set<pixel, pixel::sort> colors{};
	uint16_t palette[4]{};
	int grid_x = 0;
	int grid_y = 0;
	size_t sprite_size = 0;
	vector<uint8_t> sprite{};

	int palette_index(const pixel& pixel) const {
		int i = 0;
		for (const auto& color : colors) {
			if (pixel.bgr555 == color.bgr555 && pixel.transparent == color.transparent) {
				return i;
			}
			++i;
		}
		return 0;
	}

	tile(const char* path) {
		cout << '\"' << path << '\"' << endl;
		image = stbi_load(path, &raw_width, &raw_height, &raw_channels, 4);
		if (image == nullptr) {
			throw runtime_error("Not an image!");
		}
		if (raw_width < 8 || raw_height < 8) {
			stbi_image_free(image);
			throw runtime_error("Image is not at least 8 x 8 pixels!");
		}
		this->path = path;
		name = filesystem::path(path).stem().string();
		width = raw_width & ~7;
		height = raw_height & ~7;
		channels = 4;
		size = width * height;
		pixels.reserve(size);
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				size_t offset = (static_cast<size_t>(y) * raw_width + x) * 4;
				pixel pixel(image + offset);
				pixels.push_back(pixel);
				try {
					colors.insert(pixel);
				}
				catch (const runtime_error& error) {
					stbi_image_free(image);
					throw;
				}
				if (colors.size() > 4) {
					stbi_image_free(image);
					throw runtime_error("Too many colors! Limit is 4 (including transparency).");
				}
			}
		}
		int i = 0;
		for (const pixel& pixel : colors) {
			palette[i++] = pixel.bgr555;
		}
		grid_x = width / 8;
		grid_y = height / 8;
		sprite_size = size / 4;
		sprite.reserve(sprite_size);
		for (int tile_y = 0; tile_y < grid_y; ++tile_y) {
			for (int tile_x = 0; tile_x < grid_x; ++tile_x) {
				for (int y = 0; y < 8; ++y) {
					uint8_t low = 0;
					uint8_t high = 0;
					for (int x = 0; x < 8; ++x) {
						int pixel_x = tile_x * 8 + x;
						int pixel_y = tile_y * 8 + y;
						uint8_t index = palette_index(pixels[pixel_y * width + pixel_x]);
						low |= ((index & 1)) << (7 - x);
						high |= ((index & 2) >> 1) << (7 - x);
					}
					sprite.push_back(low);
					sprite.push_back(high);
				}
			}
		}
	}

	~tile() {
		stbi_image_free(image);
		image = nullptr;
	}

	string format_palette() {
		stringstream result;
		result << "const palette_t rom_" << name << "_palette = {\n\t";
		for (int i = 0; i < 4; ++i) {
			result << "0x" << hex << uppercase << setw(4) << setfill('0') << static_cast<int>(palette[i]) << ", ";
		}
		result << "\n};";
		return result.str();
	}

	string format_sprite() const {
		stringstream result;
		result << "const sprite_t rom_" << name << "_sprite = {\n";
		int rows = height / 2;
		for (int r = 0; r < rows; ++r) {
			int y_a = (r * 2) % 8;
			int y_b = (r * 2 + 1) % 8;
			int tile_y_a = (r * 2) / 8;
			int tile_y_b = (r * 2 + 1) / 8;
			result << "\t";
			for (int tile_x = 0; tile_x < grid_x; ++tile_x) {
				size_t idx_a = ((static_cast<size_t>(tile_y_a) * grid_x + tile_x) * 8 + y_a) * 2;
				size_t idx_b = ((static_cast<size_t>(tile_y_b) * grid_x + tile_x) * 8 + y_b) * 2;
				uint8_t bytes[4] = { sprite[idx_a], sprite[idx_a + 1], sprite[idx_b], sprite[idx_b + 1] };
				for (uint8_t byte : bytes) {
					result << "0x" << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(byte) << ", ";
				}
			}
			result << "\n";
		}
		result << "};";
		return result.str();
	}

	string format_metasprite() const {
		stringstream result;
		result << "const metasprite_t rom_" << name << "_metasprite[] = {\n";
		for (int tile_y = 0; tile_y < grid_y; ++tile_y) {
			for (int tile_x = 0; tile_x < grid_x; ++tile_x) {
				int dtile = tile_y * grid_x + tile_x;
				result << "\tMETASPR_ITEM(" << (tile_y * 8) << ", " << (tile_x * 8) << ", " << dtile << ", 0),\n";
			}
		}
		result << "\tMETASPR_TERM,\n";
		result << "};";
		return result.str();
	}
};

int main(int argc, const char* argv[]) {
	cout << "GameBoy Sprite Data Generator\n" << endl;
	for (int i = 1; i < argc; ++i) {
		try {
			tile tile(argv[i]);
			cout << tile.format_palette() << endl;
			cout << tile.format_sprite() << endl;
			if (tile.grid_x > 1 || tile.grid_y > 1) {
				cout << tile.format_metasprite() << endl;
			}
		}
		catch (const runtime_error& error) {
			cout << "Error: " << error.what() << endl;
		}
		cout << endl;
	}
	cout << "Press enter to exit." << endl;
	cin.get();
	return 0;
}
