#include "instruction.h"

#include <map>

Instruction::Instruction(Turn turn) : _turn(turn) {}

std::map<Instruction::Turn, std::string> Instruction::_turn_names = {
    {Turn::F, "F"},   {Turn::B, "B"},   {Turn::L, "L"},   {Turn::R, "R"},
    {Turn::U, "U"},   {Turn::D, "D"},   {Turn::F_, "F'"}, {Turn::B_, "B'"},
    {Turn::L_, "L'"}, {Turn::R_, "R'"}, {Turn::U_, "U'"}, {Turn::D_, "D'"}};
std::string Instruction::GetName() const { return _turn_names[_turn]; }
