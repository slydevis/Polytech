#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

cv::Mat image;
cv::Mat histogram;
std::vector<uchar> save_line;
int old_y;

void mouse_callback(int event, int x, int y, int flags, void *param) {
    switch (event) {
        case cv::EVENT_FLAG_LBUTTON:
            std::cout << "Coord (" << x << ", " << y << ')' << std::endl;

            // Reset profile window image
            for (int col = 0; col < histogram.cols; col++) {
                for (int row = 0; row < histogram.rows; row++) {
                    histogram.at<uchar>(row, col) = uchar(0);
                }
            }

            for(unsigned i = 0; i < save_line.size(); ++i) {
                image.at<uchar>(old_y, i) = save_line[i];
            }

            save_line.clear();

            // Get picture profile + draw colored line
            for (int col = 0; col < image.cols; col++) {
                uchar intensity = image.at<uchar>(y, col);

                histogram.at<uchar>(255 - intensity, col) = uchar(255);

                // Draw line
                old_y = y;
                save_line.push_back(image.at<uchar>(y, col));
                image.at<uchar>(y, col) = uchar(255);
            }


            cv::imshow("Profile window", histogram);
            cv::imshow("Display window", image);
            break;
        default:
            break;
    }
}

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

    histogram = Mat::zeros(256, image.cols, CV_8UC1);

    cv::namedWindow("Display window"); /* Create a window for display */
    cv::imshow("Display window", image);  /* Show our image inside it */

    cv::setMouseCallback("Display window", mouse_callback, (void *) &image);

    cv::namedWindow("Profile window");
    cv::imshow("Profile window", histogram);
    cv::moveWindow("Profile window", 1225, 300);

    cv::waitKey(0);  /* Wait for a keystroke in the window */

    return 0;
}