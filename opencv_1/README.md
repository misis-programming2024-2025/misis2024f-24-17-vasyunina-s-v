## 1 задача

```c++
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
        int cellY = y / cellSize; // определения номера строки клетки

        for (int x = 0; x < cols * cellSize; x++) { //проход по столбцам
            int cellX = x / cellSize; // определение номера столбца
            bool isWhite = (cellY + cellX) % 2 == 0; // определение цвета клетки
            // для белой клетки - все каналы 255, для черной - 0
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


## 2 задание

```c++
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath> 

struct Config {
    int width = 600;
    int height = 600;
    int thickness = 3;
    int step = 10;
    unsigned char color[3] = {255, 0, 0}; 
};

void parseArguments(int argc, char** argv, Config& cfg) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--width" && i + 1 < argc) cfg.width = std::atoi(argv[++i]);
        else if (arg == "--height" && i + 1 < argc) cfg.height = std::atoi(argv[++i]);
        else if (arg == "--thick" && i + 1 < argc) cfg.thickness = std::atoi(argv[++i]);
        else if (arg == "--step" && i + 1 < argc) cfg.step = std::atoi(argv[++i]);
        else if (arg == "--color" && i + 1 < argc) {
            std::string colorStr = argv[++i];
            size_t c1 = colorStr.find(','), c2 = colorStr.rfind(',');
            cfg.color[0] = std::atoi(colorStr.substr(c2+1).c_str()); 
            cfg.color[1] = std::atoi(colorStr.substr(c1+1, c2-c1-1).c_str());
            cfg.color[2] = std::atoi(colorStr.substr(0, c1).c_str()); 
        }
    }
}

void drawPixel(cv::Mat& img, int x, int y, const unsigned char color[3]) { //установка цвета конкретного пикселя
    if (x >= 0 && x < img.cols && y >= 0 && y < img.rows) {
        unsigned char* pixel = img.data + y * img.step + x * 3;
        pixel[0] = color[0]; 
        pixel[1] = color[1];
        pixel[2] = color[2];
    }
}

void drawLine(cv::Mat& img, cv::Point p1, cv::Point p2, 
                   const unsigned char color[3], int thickness) {
    // вычисляем длину линии
    float length = std::max(abs(p2.x - p1.x), abs(p2.y - p1.y));
    
    //рисуем каждый пиксель вдоль линии
    for (float t = 0; t <= 1.0; t += 1.0/length) {
        int x = p1.x + t * (p2.x - p1.x);
        int y = p1.y + t * (p2.y - p1.y);
        
        //рисуем пиксель с учетом толщины
        for (int dy = -thickness/2; dy <= thickness/2; dy++) {
            for (int dx = -thickness/2; dx <= thickness/2; dx++) {
                drawPixel(img, x + dx, y + dy, color);
            }
        }
    }
}

void drawAngledSpiral(cv::Mat& img, const Config& cfg) {
    cv::Point center(cfg.width/2, cfg.height/2);
    cv::Point current = center;
    
    int segment_length = cfg.step;
    for (int dir = 0, i = 0; i < 100; dir++, i++) {
        cv::Point next = current;
        
        switch(dir % 4) {
            case 0: next.x += segment_length; break;
            case 1: next.y -= segment_length; break; 
            case 2: next.x -= segment_length; break; 
            case 3: next.y += segment_length; break;
        }
        
        drawLine(img, current, next, cfg.color, cfg.thickness);
        current = next;
        
        if (i % 2 == 1) segment_length += cfg.step;
    }
}

int main(int argc, char** argv) {
    Config cfg;
    parseArguments(argc, argv, cfg);

    cv::Mat image(cfg.height, cfg.width, CV_8UC3);
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            unsigned char* pixel = image.data + y * image.step + x * 3;
            pixel[0] = 255; 
            pixel[1] = 255; 
            pixel[2] = 255;
        }
    }
    drawAngledSpiral(image, cfg);
    cv::imwrite("spiral.png", image);
    
    return 0;
}
```

### Как запустить:

g++ main2.cpp -o spiral  `pkg-config --cflags --libs opencv4`

./spiral --width 600 --height 600 --thick 3 --step 10 --color 255,0,0

--width 600 --height 600 --thick 3 --step 10 --color 255,0,0

![1](spiral1.png)

--width 200 --height 200 --thick 5 --step 15 --color 100,100,100

![2](spiral2.png)

--width 800 --height 800 --thick 10 --step 15 --color 150,100,150

![3](spiral3.png)