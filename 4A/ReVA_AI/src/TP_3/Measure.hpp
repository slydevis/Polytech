#ifndef __MEASURE_HPP__
#define __MEASURE_HPP__

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define SOBEL 0
#define LAPLACE 1
#define CANNY 2
#define REF 3

class Measure {
  public:
    Measure();
    Measure(cv::Mat *image_sobel, cv::Mat *image_laplace, cv::Mat *image_canny,
            cv::Mat *image_ref);
    Measure(cv::Mat *image_ref);

    std::string toCSV() const;

    void setImageSobel(cv::Mat *image_sobel);
    void setImageLaplace(cv::Mat *image_laplace);
    void setImageCanny(cv::Mat *image_canny);

    void update();
    void updateFauxPositif();
    void updateFauxNegatif();
    void updateP();
    void updateTFP();
    void updateTFN();
    void setParam(int index, int b, int param, int s = -1);
    bool isBestSobel(const Measure &m) const;
    void setSobel(const Measure &m);
    bool isBestLaplace(const Measure &m) const;
    void setLaplace(const Measure &m);
    bool isBestCanny(const Measure &m) const;
    void setCanny(const Measure &m);

  private:
    int param_s[3] = {0, 0, 0};
    int param_p[3] = {0, 0, 0};
    int param_b[3] = {0, 0, 0};

    cv::Mat *image_sobel = nullptr;
    cv::Mat *image_laplace = nullptr;
    cv::Mat *image_canny = nullptr;
    cv::Mat *image_ref = nullptr;

    int contours_detectes[4] = {0, 0, 0, 0};
    int contours_correct[3] = {0, 0, 0};
    int faux_positifs[3] = {0, 0, 0};
    int faux_negatifs[3] = {0, 0, 0};

    float P[3] = {0.0f, 0.0f, 0.0f};
    float TFP[3] = {0.0f, 0.0f, 0.0f};
    float TFN[3] = {0.0f, 0.0f, 0.0f};
};

#endif /* __MEASURE_HPP__ */