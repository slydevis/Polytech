#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "compute_histogram.hpp"

using namespace cv;
using namespace std;

cv::Mat image;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: display_image ImageToLoadAndDisplay\n");
        return -1;
    }

    image = cv::imread(argv[1], IMREAD_GRAYSCALE); /* Read the file */

    if (!image.data) { /* Check for invalid input */
        printf("Could not open or find the image\n");
        return -1;
    }

    cv::namedWindow("Display window"); /* Create a window for display */
    cv::imshow("Display window", image);  /* Show our image inside it */
    cv::moveWindow("Display window", 0, 0);

    Histogram histogram(&image, 0, 0);
    histogram.draw("Histogram");
    histogram.expension("Expension");

    cv::waitKey(0);  /* Wait for a keystroke in the window */

    return 0;
}