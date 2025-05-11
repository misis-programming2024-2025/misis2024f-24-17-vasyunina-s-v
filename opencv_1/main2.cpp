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