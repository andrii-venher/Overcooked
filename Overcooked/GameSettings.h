#pragma once

const int TILE_SIZE = 32;

enum class MapObjects { PLAYER, TABLE, FLOOR, CHECKOUT, CUTTING_BOARD, STOVE, TRASH, TOMATO_DISPENSER, MUSHROOM_DISPENCER, ONION_DISPENCER };
enum class Rotations { LEFT, UP, RIGHT, DOWN };
enum class Actions { WAIT, TAKE };