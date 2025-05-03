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

int main(int argc, char** argv) {
    int rows, cols, cellSize;
    parseArguments(argc, argv, rows, cols, cellSize);
    
    cv::Mat chessboard(rows * cellSize, cols * cellSize, CV_8UC3, cv::Scalar::all(255));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Scalar color = (i + j) % 2 == 0 ? cv::Scalar(255, 255, 255) : cv::Scalar(0, 0, 0);
            cv::rectangle(chessboard,
                        cv::Point(j * cellSize, i * cellSize),
                        cv::Point((j + 1) * cellSize, (i + 1) * cellSize),
                        color,
                        cv::FILLED);
        }
    }
    
    cv::imwrite("chessboard.png", chessboard);
    cv::imshow("Chessboard", chessboard);
    cv::waitKey(0);
    
    return 0;
}