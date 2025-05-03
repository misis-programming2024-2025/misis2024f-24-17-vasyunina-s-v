## 1 задача

```c++
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

//считываем аргументы из консоли(парсинг), по умолчанию задаем доску 8*8
void parseArguments(int argc, char** argv, int& rows, int& cols, int& cellSize) {
    rows = 8;
    cols = 8;
    cellSize = 50;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--rows" && i + 1 < argc) {
            rows = std::stoi(argv[++i]); //преобразование строки в число
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
    
    cv::Mat chessboard(rows * cellSize, cols * cellSize, CV_8UC3, cv::Scalar::all(255)); //создание матрицы нужного размера
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Scalar color = (i + j) % 2 == 0 ? cv::Scalar(255, 255, 255) : cv::Scalar(0, 0, 0);// сумма индексов четная - белый цвет, сумма индексов нечетная - черный цвет
            cv::rectangle(chessboard, cv::Point(j * cellSize, i * cellSize), cv::Point((j + 1) * cellSize, (i + 1) * cellSize), color, cv::FILLED); //рисуем клетку нужного цвета
        }
    }
    
    cv::imwrite("chessboard.png", chessboard); //название картинки
    cv::imshow("Chessboard", chessboard); //имя, которое показывается при открытии
    cv::waitKey(0);
    
    return 0;
}
```

### Как запустить:

g++ main.cpp -o chessboard `pkg-config --cflags --libs opencv4`  

./chessboard --rows 12 --cols 12 --cell 50

### Пимеры:
--rows 12 --cols 12 --cell 50

![1](chessboard1.png)

--rows 5 --cols 5 --cell 100

![2](chessboard2.png)

--rows 10 --cols 10 --cell 90

![2](chessboard3.png)