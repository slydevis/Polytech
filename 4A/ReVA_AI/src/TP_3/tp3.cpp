#include <dirent.h> // Dir
#include <iostream>
#include <thread> // thread

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Csv.hpp"
#include "Measure.hpp"

using namespace std;
using namespace cv;

// TODO: Comparer les différents résultats

cv::Mat image;
int scale = 1;
int vblur = 9;
int vseuil = 200;

// Util function
std::vector<std::string> explode(std::string const &s, char delim) {
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);) {
        result.push_back(std::move(token));
    }

    return result;
}

void toBinaryPic(Mat &p, int seuil) {
    for (unsigned i = 0; i < p.cols; ++i) {
        for (unsigned j = 0; j < p.rows; ++j) {
            uchar val = p.at<uchar>(i, j);
            if (val > seuil) {
                p.at<uchar>(i, j) = 255;
            } else {
                p.at<uchar>(i, j) = 0;
            }
        }
    }
}

cv::Mat sobel_image;
void sobel() {
    int ddepth = CV_16S;
    cv::Mat bImg;
    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    GaussianBlur(image, sobel_image, Size(vblur, vblur), 0, 0, BORDER_DEFAULT);

    // Gradient X
    Sobel(sobel_image, grad_x, ddepth, 1, 0, 3, scale, 255, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    // Gradient Y
    Sobel(sobel_image, grad_y, ddepth, 0, 1, 3, scale, 255, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    // Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobel_image);

    toBinaryPic(sobel_image, vseuil);

#ifndef RELEASE
    imshow("Sobel", sobel_image);
#endif
}

cv::Mat laplace_image;
void laplace() {
    Mat src_gray, dst;
    int kernel_size = 3;
    int delta = 255;
    int ddepth = CV_16S;
    cv::Mat bImg;

    // Apply Laplace function

    GaussianBlur(image, bImg, Size(vblur, vblur), 0, 0, BORDER_DEFAULT);

    Laplacian(bImg, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(dst, laplace_image);

    toBinaryPic(laplace_image, vseuil);

#ifndef RELEASE
    // Show what you got
    imshow("Laplace", laplace_image);
#endif
}

void updateScale(int, void *) { sobel(); }

void updateScaleLaplace(int, void *) { laplace(); }

int lowThreshold = 1;
cv::Mat canny_image;
cv::Mat negative_image;

void canny() {
    Mat detected_edges;

    int kernel_size = 3;
    int ratio = 1;
    int seuil = 0;

    GaussianBlur(negative_image, detected_edges, Size(vblur, vblur), 0, 0,
                 BORDER_DEFAULT);

    // blur(negative_image, detected_edges, Size(vblur, vblur));

    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio,
          kernel_size);

    for (unsigned i = 0; i < detected_edges.rows; ++i) {
        for (unsigned j = 0; j < detected_edges.cols; ++j) {
            detected_edges.at<uchar>(i, j) =
                (uchar)255 - detected_edges.at<uchar>(i, j);
        }
    }

    canny_image = Scalar::all(0);

    detected_edges.copyTo(canny_image, detected_edges);

#ifndef RELEASE
    imshow("Canny", canny_image);
#endif
}

void updateLowThreshold(int, void *) { canny(); }

std::vector<std::string> getAllPictures(const std::string &directory) {

    std::vector<std::string> files;
    DIR *dp;

    struct dirent *dirp;

    if ((dp = opendir(directory.c_str())) == NULL) {
        std::cout << "Erreur à l'ouverture de " << directory << std::endl;
        exit(-1);
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }

    closedir(dp);

    return files;
}

void runFile(const std::string &directory, const std::string &filename) {
    std::string name = directory + filename;

    image = cv::imread(name, IMREAD_GRAYSCALE);

    if (!image.data) {
        /* Check for invalid input */
        printf("Could not open or find the image\n");
        exit(-1);
    }

    negative_image = Mat::zeros(image.rows, image.cols, CV_8UC1);

    // Negative image
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            negative_image.at<uchar>(row, col) =
                -255 - image.at<uchar>(row, col);
        }
    }

    Measure best_contour;

    std::vector<std::string> names = explode(filename, '.');
    cv::Mat image_ref = cv::imread("images/gt/" + names[0] + "_gt_binary.pgm",
                                   IMREAD_GRAYSCALE);

    if (!image_ref.data) {
        std::cout << "Erreur loading reference image" << std::endl;
        exit(-1);
    }

    for (int b = 1; b < 30; b = b + 2) {
        vblur = b;
        for (int param = 0; param < 100; ++param) {
            // Do sobel and laplace
            Measure m(&image_ref);

            if (param <= 5) {
                scale = param;
                for (int s = 0; s < 255; ++s) {
                    vseuil = s;

                    sobel();
                    m.setParam(SOBEL, b, scale, vseuil);
                    m.setImageSobel(&sobel_image);
                    if (m.isBestSobel(best_contour)) {
                        best_contour.setSobel(m);
                    }

                    laplace();
                    m.setParam(LAPLACE, b, scale, vseuil);
                    m.setImageLaplace(&laplace_image);
                    if (m.isBestLaplace(best_contour)) {
                        best_contour.setLaplace(m);
                    }
                }
            }

            lowThreshold = param;
            canny();
            m.setParam(CANNY, b, lowThreshold);
            m.setImageCanny(&canny_image);
            if (m.isBestCanny(best_contour)) {
                best_contour.setCanny(m);
            }
        }
    }

#ifdef RELEASE
    csv.write(filename + "; " + best_contour.toCSV());
#endif
}

int main(int argc, char **argv) {
#ifdef RELEASE
    CSV csv("log.csv");

    if (argc != 2) {
        printf("Usage: display_image DirectoryToLoadAndDisplay\n");
        return -1;
    }

    std::vector<std::string> pictures = getAllPictures(argv[1]);

    csv.createHeader();

    int nbFileDone = 0;
    for (std::string filename : pictures) {
        if (filename == ".." || filename == "gt" || filename == "." ||
            filename == ".DS_STORE")
            continue;

        runFile(argv[1], filename);
        nbFileDone++;
        std::cout << "PICTURE DONE " << nbFileDone << " / "
                  << (pictures.size() - 3) << std::endl;
    }

    csv.close();
#else
    if (argc != 4) {
        printf("Usage: display_image ImageToLoadAndDisplay blur seuil\n");
        return -1;
    }

    image = cv::imread(argv[1], IMREAD_GRAYSCALE); /* Read the file */

    vblur = atoi(argv[2]);
    vblur = ((vblur % 2) == 0 ? vblur - 1 : vblur);
    vseuil = atoi(argv[3]);

    std::cout << "BLUR = " << vblur << std::endl;

    if (!image.data) {
        /* Check for invalid input */
        printf("Could not open or find the image\n");
        return -1;
    }

    cv::namedWindow("Display window");   /* Create a window for display */
    cv::imshow("Display window", image); /* Show our image inside it */
    cv::moveWindow("Display window", 0, 0);

    // SOBEL
    namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
    createTrackbar("scaleTrackbar", "Sobel", &scale, 100, updateScale);
    sobel();

    // LAPLACE
    namedWindow("Laplace", CV_WINDOW_AUTOSIZE);
    createTrackbar("scaleTrackbarLaplace", "Laplace", &scale, 100,
                   updateScaleLaplace);
    laplace();

    // CANNY
    // Negative image
    negative_image = Mat::zeros(image.rows, image.cols, CV_8UC1);

    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            negative_image.at<uchar>(row, col) =
                -255 - image.at<uchar>(row, col);
        }
    }

    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    createTrackbar("lowThreshold", "Canny", &lowThreshold, 100,
                   updateLowThreshold);

    canny();

    cv::waitKey(0); /* Wait for a keystroke in the window */
#endif
    return 0;
}