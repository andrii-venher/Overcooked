#pragma once

const int TILE_SIZE = 32;

enum class MapObjects { PLAYER, TABLE, FLOOR, CHECKOUT, TOMATO_DISPENSER };
enum class Rotations { LEFT, UP, RIGHT, DOWN };
enum class Actions { WAIT, TAKE };