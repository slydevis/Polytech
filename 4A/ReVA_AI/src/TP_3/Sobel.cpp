#include "Sobel.hpp"

using namespace ai;
using namespace cv;

int scale = 1;

Sobel::Sobel(std::string window_name, cv::Mat image)
    : m_image(image), window_name(window_name) {
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    createTrackbar("scaleTrackbar", window_name, &m_scale, 100, updateScale);
    execute();
}

// TODO: Faire varier le scale

void Sobel::updateScale(int, void *) { execute(); }

void Sobel::execute() {
    int ddepth = CV_16S;

    cv::Mat grad;

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    // Gradient X
    cv::Sobel(m_image, grad_x, ddepth, 1, 0, 3, m_scale, 255, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    // Gradient Y
    cv::Sobel(m_image, grad_y, ddepth, 0, 1, 3, m_scale, 255, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    // Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    // toBinaryPic(grad, 200); // TODO: Create a trackbar
    imshow(window_name, grad);
}