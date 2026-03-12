#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>
#include <vector>

const unsigned int START_ADDRESS{0x200};

class sample {
public:
  uint8_t memory[4096]{};

private:
  void loadROM(const std::string_view filename);
};

void sample::loadROM(const std::string_view filename) {
  std::ifstream file{filename.data(), std::ios::binary | std::ios::ate};

  if (file.is_open()) {
    // std::filesystem::file_size(filename); // can also use this to get size of
    // file
    std::streampos size{file.tellg()};
    // char *buffer{new char[size]};
    std::vector<char> buffer(size); // using vector is safer
    // std::unique_ptr<char[]> buffer{std::make_unique<char[]>(size)};

    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), size);
    file.close();

    for (int i = 0; i < size; ++i) {
      memory[START_ADDRESS + i] = buffer[i];
    }

    // delete[] buffer;
  }
}
