#ifndef __COMPUTE_HISTOGRAM_HPP__
#define __COMPUTE_HISTOGRAM_HPP__

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <map>


class Histogram {
public:
    Histogram(cv::Mat *image, unsigned pos_x, unsigned pos_y);
    void expension(std::string nameWindow);
    void draw(std::string nameWindow);
private:
    void updateFrequencies();

    std::map<uchar, float> m_frequencies;
    uchar m_min;
    uchar m_max;
    float m_greyMax;

    unsigned m_pos_x;
    unsigned m_pos_y;
    cv::Mat* m_image;
};

#endif /* __COMPUTE_HISTOGRAM_HPP__ */
