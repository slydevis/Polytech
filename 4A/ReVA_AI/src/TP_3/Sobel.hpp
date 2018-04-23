#ifndef __SOBEL_HPP__
#define __SOBEL_HPP__

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace ai {

class Sobel {
  public:
    Sobel(std::string window_name, cv::Mat image);
    cv::Mat getImage();

  private:
    void execute();
    void updateScale(int, void *);

    int m_scale;
    cv::Mat m_image;
    std::string window_name;
};

} // namespace ai

#endif /* __SOBEL_HPP__ */