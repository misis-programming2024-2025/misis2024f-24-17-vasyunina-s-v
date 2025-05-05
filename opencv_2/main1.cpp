#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void applyBlur(const Mat& input, Mat& output, int kernelSize) {
    if (kernelSize % 2 == 0) {
        cerr << "Kernel size must be odd" << endl;
        return;
    }
    int border = kernelSize / 2;
    output = Mat::zeros(input.size(), input.type());
    Mat padded;
    copyMakeBorder(input, padded, border, border, border, border, BORDER_REPLICATE);
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            for (int c = 0; c < input.channels(); c++) {
                float sum = 0.0;
                for (int ky = -border; ky <= border; ky++) {
                    for (int kx = -border; kx <= border; kx++) {
                        sum += padded.at<Vec3b>(y + border + ky, x + border + kx)[c];
                    }
                }
                output.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(sum / (kernelSize * kernelSize));
            }
        }
    }
}

int main(int argc, char** argv) {
    String inputPath, outputPath;
    int kernelSize = 3;
    
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--input") {
            inputPath = argv[++i];
        } else if (string(argv[i]) == "--output") {
            outputPath = argv[++i];
        } else if (string(argv[i]) == "--kernel") {
            kernelSize = atoi(argv[++i]);
        }
    }
    
    if (inputPath.empty() || outputPath.empty()) {
        cout << "Usage: ./lab2 --input input.jpg --output blur.jpg --kernel 3" << endl;
        return -1;
    }
    Mat image = imread(inputPath);
    if (image.empty()) {
        cerr << "Could not open or find the image" << endl;
        return -1;
    }
    Mat blurredImage;
    applyBlur(image, blurredImage, kernelSize);
    imwrite(outputPath, blurredImage);

    return 0;
}