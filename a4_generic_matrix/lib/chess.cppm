module;

#include "matrix.h"

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

export module chess;

// Chess_piece definition
export struct Chess_piece {
    std::string name;
    std::string color; // "white" or "black"
    Chess_piece() : name(""), color("none") {}
    Chess_piece(const std::string& n, const std::string& c = "white") : color(c) {
        static const std::vector<std::string> valid_names = {
            "pawn", "knight", "bishop", "rook", "queen", "king"
        };
        static const std::vector<std::string> valid_colors = {
            "white", "black"
        };
        if (std::find(valid_names.begin(), valid_names.end(), n) != valid_names.end()) {
            name = n;
        } else {
            throw std::invalid_argument("Invalid chess piece name: " + n);
        }
        if (std::find(valid_colors.begin(), valid_colors.end(), c) == valid_colors.end()) {
            throw std::invalid_argument("Invalid chess piece color: " + c);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Chess_piece& cp) {
        if (cp.color == "white") {
            if (cp.name == "pawn")      return os << "\u2659";
            if (cp.name == "knight")    return os << "\u2658";
            if (cp.name == "bishop")    return os << "\u2657";
            if (cp.name == "rook")      return os << "\u2656";
            if (cp.name == "queen")     return os << "\u2655";
            if (cp.name == "king")      return os << "\u2654";
        } else if (cp.color == "black") {
            if (cp.name == "pawn")      return os << "\u265F";
            if (cp.name == "knight")    return os << "\u265E";
            if (cp.name == "bishop")    return os << "\u265D";
            if (cp.name == "rook")      return os << "\u265C";
            if (cp.name == "queen")     return os << "\u265B";
            if (cp.name == "king")      return os << "\u265A";
        }
        return os << " ";
    }
};


// Chess board creation function
export Matrix<Chess_piece> CreateChessBoard() {
    Matrix<Chess_piece> board(8, 8);

    // Black pieces
    board(0, 0) = Chess_piece("rook", "black");
    board(0, 1) = Chess_piece("knight", "black");
    board(0, 2) = Chess_piece("bishop", "black");
    board(0, 3) = Chess_piece("queen", "black");
    board(0, 4) = Chess_piece("king", "black");
    board(0, 5) = Chess_piece("bishop", "black");
    board(0, 6) = Chess_piece("knight", "black");
    board(0, 7) = Chess_piece("rook", "black");
    for (int i = 0; i < 8; ++i)
        board(1, i) = Chess_piece("pawn", "black");

    // White pieces
    board(7, 0) = Chess_piece("rook", "white");
    board(7, 1) = Chess_piece("knight", "white");
    board(7, 2) = Chess_piece("bishop", "white");
    board(7, 3) = Chess_piece("queen", "white");
    board(7, 4) = Chess_piece("king", "white");
    board(7, 5) = Chess_piece("bishop", "white");
    board(7, 6) = Chess_piece("knight", "white");
    board(7, 7) = Chess_piece("rook", "white");
    for (int i = 0; i < 8; ++i)
        board(6, i) = Chess_piece("pawn", "white");

    // Empty squares
    for (int row = 2; row <= 5; ++row)
        for (int col = 0; col < 8; ++col)
            board(row, col) = Chess_piece();

    return board;
}

// Helper function to print the chessboard with colored squares
export void PrintChessBoard(const Matrix<Chess_piece>& board) {
    const std::string white_bg = "\033[47m";   // White background
    const std::string black_bg = "\033[100m";  // Bright black (gray) background
    const std::string reset = "\033[0m";

    for (size_t row = 0; row < 8; ++row) {
        for (size_t col = 0; col < 8; ++col) {
            bool is_white_square = (row + col) % 2 == 0;
            std::cout << (is_white_square ? white_bg : black_bg);

            // Always print a 3-character box: [space][piece or space][space]
            if (board(row, col).name.empty()) {
                std::cout << "   ";
            } else {
                std::cout << " " << board(row, col) << " ";
            }

            std::cout << reset;
        }
        std::cout << "\n";
    }
}