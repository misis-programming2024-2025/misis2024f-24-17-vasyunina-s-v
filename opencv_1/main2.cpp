#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

struct Config {
    int width = 600;
    int height = 600;
    int thickness = 3;
    int step = 10;
    cv::Scalar color = cv::Scalar(255, 0, 0);
};

void parseArguments(int argc, char** argv, Config& cfg) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--width" && i + 1 < argc) cfg.width = std::stoi(argv[++i]);
        else if (arg == "--height" && i + 1 < argc) cfg.height = std::stoi(argv[++i]);
        else if (arg == "--thick" && i + 1 < argc) cfg.thickness = std::stoi(argv[++i]);
        else if (arg == "--step" && i + 1 < argc) cfg.step = std::stoi(argv[++i]);
        else if (arg == "--color" && i + 1 < argc) {
            std::string colorStr = argv[++i];
            size_t c1 = colorStr.find(','), c2 = colorStr.rfind(',');
            cfg.color = cv::Scalar(
                std::stoi(colorStr.substr(0, c1)),
                std::stoi(colorStr.substr(c1+1, c2-c1-1)),
                std::stoi(colorStr.substr(c2+1))
            );
        }
    }
}

void drawAngledSpiral(cv::Mat& img, const Config& cfg) {
    cv::Point center(cfg.width/2, cfg.height/2);
    std::vector<cv::Point> points;
    
    int segments = 4; // Количество прямых отрезков на один виток
    int segment_length = cfg.step;
    int direction = 0; // 0=вправо, 1=вверх, 2=влево, 3=вниз
    
    points.push_back(center);
    
    for (int i = 1; i < 100; ++i) { // 100 - максимальное количество точек
        cv::Point last = points.back();
        cv::Point next = last;
        
        switch (direction % 4) {
            case 0: next.x += segment_length; break; // вправо
            case 1: next.y -= segment_length; break; // вверх
            case 2: next.x -= segment_length; break; // влево
            case 3: next.y += segment_length; break; // вниз
        }
        
        points.push_back(next);
        
        // Увеличиваем длину отрезка после каждых двух поворотов
        if (i % 2 == 0) segment_length += cfg.step;
        
        direction++;
    }
    
    // Рисуем ломаную линию
    for (size_t i = 1; i < points.size(); ++i) {
        cv::line(img, points[i-1], points[i], cfg.color, cfg.thickness);
    }
}

int main(int argc, char** argv) {
    Config cfg;
    parseArguments(argc, argv, cfg);
    
    cv::Mat image(cfg.height, cfg.width, CV_8UC3, cv::Scalar(255, 255, 255));
    drawAngledSpiral(image, cfg);
    
    cv::imwrite("spiral.png", image);
    cv::imshow("Spiral", image);
    cv::waitKey(0);
    
    return 0;
}