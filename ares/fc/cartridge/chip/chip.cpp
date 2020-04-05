#include "mmc3.cpp"
#include "mmc5.cpp"
#include "mmc6.cpp"
#include "vrc1.cpp"
#include "vrc2.cpp"
#include "vrc3.cpp"
#include "vrc4.cpp"
#include "vrc6.cpp"
#include "vrc7.cpp"

Chip::Chip(Board& board) : board(board) {
}

auto Chip::tick() -> void {
  board.tick();
}