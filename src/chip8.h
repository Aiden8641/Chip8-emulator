#ifndef CHIP8
#define CHIP8
#include <cstdint>
#include <cstring>
#include <random>

constexpr unsigned int START_ADDRESS{0x200};
constexpr unsigned int FONTSET_SIZE{80};
const unsigned int FONT_START_ADDRESS{0x050};
constexpr unsigned int VIDEO_WIDTH{64};
constexpr unsigned int VIDEO_HEIGHT{32};

constexpr uint8_t fontset[FONTSET_SIZE]{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
public:
  Chip8();

  void loadROM(char const *);
  void cycle();

  // instructions
  void OP_00E0();
  void OP_00EE();
  void OP_1nnn();
  void OP_2nnn();
  void OP_3xkk();
  void OP_4xkk();
  void OP_5xy0();
  void OP_6xkk();
  void OP_7xkk();
  void OP_8xy0();
  void OP_8xy1();
  void OP_8xy2();
  void OP_8xy3();
  void OP_8xy4();
  void OP_8xy5();
  void OP_8xy6();
  void OP_8xy7();
  void OP_8xyE();
  void OP_9xy0();
  void OP_Annn();
  void OP_Bnnn();
  void OP_Cxkk();
  void OP_Dxyn();
  void OP_Ex9E();
  void OP_ExA1();
  void OP_Fx07();
  void OP_Fx0A();
  void OP_Fx15();
  void OP_Fx18();
  void OP_Fx1E();
  void OP_Fx29();
  void OP_Fx33();
  void OP_Fx55();
  void OP_Fx65();

  void setKey(int idx, bool state);

  uint8_t registers[16]{}; // 16 8bit general purpose registers
  uint8_t memory[4096]{};  // 4096 bytes of memory
  uint16_t index{}; // special register that holds the memory address to be used
                    // in operations
  uint16_t pc{};    // holds the next instruction
  uint16_t stack[16]{}; // holds pc values of when a function is called, will
                        // place back into pc when return
  uint8_t sp{};         // stack pointer where we are in the stack
  uint8_t delayTimer{}; // both timers are either 0 or not 0
  uint8_t soundTimer{};
  uint8_t keypad[16]{}; // 16 keys for the keypad

  uint32_t video[64 * 32]{}; // using uint32 for compatibility with sdl, screen
                             // of 64 by 32
  uint16_t opcode; // stores the operation, operations are 2 bytes long
  std::default_random_engine randGen;
  std::uniform_int_distribution<uint8_t> randByte;
  void Table0() { ((*this).*(table0[opcode & 0x000Fu]))(); }
  void Table8() { ((*this).*(table8[opcode & 0x000Fu]))(); }
  void TableE() { ((*this).*(tableE[opcode & 0x000Fu]))(); }
  void TableF() { ((*this).*(tableF[opcode & 0x00FFu]))(); }
  void OP_NULL() {};

  typedef void (Chip8::*Chip8Func)();

  Chip8Func table[0xF + 1];
  Chip8Func table0[0xE + 1];
  Chip8Func table8[0xE + 1];
  Chip8Func tableE[0xE + 1];
  Chip8Func tableF[0x65 + 1];

private:
};
#endif // !CHIP8
