#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<float>> readKernelFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<float>> kernel;
    
    if (!file.is_open()) {
        std::cerr << "Could not open kernel file: " << filename << std::endl;
        return kernel;
    }

    int size;
    file >> size;

    kernel.resize(size, std::vector<float>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> kernel[i][j];
        }
    }

    file.close();
    return kernel;
}

void applyCustomKernel(const cv::Mat& input, cv::Mat& output, const std::vector<std::vector<float>>& kernel) {
    int kernelSize = kernel.size();
    int border = kernelSize / 2;
    
    output = cv::Mat::zeros(input.size(), input.type());

    cv::Mat padded;
    cv::copyMakeBorder(input, padded, border, border, border, border, cv::BORDER_REPLICATE);

    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            for (int c = 0; c < input.channels(); c++) {
                float sum = 0.0f;
                
                for (int ky = -border; ky <= border; ky++) {
                    for (int kx = -border; kx <= border; kx++) {
                        float kernelValue = kernel[ky + border][kx + border];
                        sum += padded.at<cv::Vec3b>(y + border + ky, x + border + kx)[c] * kernelValue;
                    }
                }
                
                output.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum);
            }
        }
    }
}

int main(int argc, char** argv) {
    std::string inputPath, outputPath, kernelPath;
    
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--input") {
            inputPath = argv[++i];
        } else if (std::string(argv[i]) == "--output") {
            outputPath = argv[++i];
        } else if (std::string(argv[i]) == "--kernel_file") {
            kernelPath = argv[++i];
        }
    }
    
    if (inputPath.empty() || outputPath.empty() || kernelPath.empty()) {
        std::cout << "Usage: ./lab2 --input input.jpg --output result.jpg --kernel_file kernel.txt" << std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(inputPath);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    std::vector<std::vector<float>> kernel = readKernelFromFile(kernelPath);
    if (kernel.empty()) {
        std::cerr << "Failed to read kernel or kernel is empty" << std::endl;
        return -1;
    }


    if (kernel.size() % 2 == 0) {
        std::cerr << "Kernel size must be odd" << std::endl;
        return -1;
    }

    cv::Mat result;
    applyCustomKernel(image, result, kernel);

    if (!cv::imwrite(outputPath, result)) {
        std::cerr << "Failed to write output image" << std::endl;
        return -1;
    }

    return 0;
}