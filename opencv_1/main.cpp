#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

void parseArguments(int argc, char** argv, int& rows, int& cols, int& cellSize) {
    rows = 8;
    cols = 8;
    cellSize = 50;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--rows" && i + 1 < argc) {
            rows = std::stoi(argv[++i]);
        } else if (arg == "--cols" && i + 1 < argc) {
            cols = std::stoi(argv[++i]);
        } else if (arg == "--cell" && i + 1 < argc) {
            cellSize = std::stoi(argv[++i]);
        }
    }
}

void drawChessManual(cv::Mat& img, int rows, int cols, int cellSize) {
    for (int y = 0; y < rows * cellSize; y++) {
        int cellY = y / cellSize;
        for (int x = 0; x < cols * cellSize; x++) {
            int cellX = x / cellSize;
            bool isWhite = (cellY + cellX) % 2 == 0;
            img.data[y * img.step + x * 3 + 0] = isWhite ? 255 : 0; 
            img.data[y * img.step + x * 3 + 1] = isWhite ? 255 : 0;
            img.data[y * img.step + x * 3 + 2] = isWhite ? 255 : 0;
        }
    }
}

int main(int argc, char** argv) {
    int rows, cols, cellSize;
    parseArguments(argc, argv, rows, cols, cellSize);
    
    cv::Mat chessboard(rows*cellSize, cols*cellSize, CV_8UC3);
    drawChessManual(chessboard, rows, cols, cellSize);
    
    cv::imwrite("chessboard.png", chessboard);
    return 0;
}