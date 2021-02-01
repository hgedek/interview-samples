/* 01.08.2020 Hakan Gedek
 * 
 * I mostly put shared / common classes,structs,enums... into common or utils
 * So i reduce unnecessary includes & dependencies
 * 
 * Here only movetype is used
 */
#pragma once

/**
 * @brief The MoveType enum players move type
 */
enum class MoveType {
    NONE,
    X,
    O
};
