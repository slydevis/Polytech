#include <opencv2/imgproc.hpp>
#include "compute_histogram.hpp"

Histogram::Histogram(cv::Mat *image, unsigned pos_x, unsigned pos_y) : m_image(image), m_pos_x(pos_x), m_pos_y(pos_y) {
    updateFrequencies();
}

void Histogram::updateFrequencies() {
    for(unsigned i = 0; i < 256; ++i) {
        m_frequencies[i] = 0.0f;
    }

    m_max = 0;
    m_min = 255;

    for(int row = 0; row < m_image->rows; ++row) {
        for(int col = 0; col < m_image->cols; ++col) {
            uchar intensity = m_image->at<uchar>(row, col);
            m_frequencies[intensity]++;

            if(intensity >= m_max) {
                m_max = intensity;
            }

            if(intensity < m_min) {
                m_min = intensity;
            }
        }
    }

    m_greyMax = 0.0f;
    for(unsigned i = 0; i < m_frequencies.size(); ++i) {
        m_frequencies[i] = m_frequencies[i] / (m_image->rows * m_image->cols);
        if(m_greyMax < m_frequencies[i]) {
            m_greyMax = m_frequencies[i];
        }
    }
}

void Histogram::draw(std::string nameWindow) {
    cv::Mat histogram = cv::Mat(m_image->rows, m_image->cols, CV_8UC3, CvScalar(255, 255, 255));

    for(std::map<uchar, float>::iterator it = m_frequencies.begin(); it != m_frequencies.end(); ++it) {
        float frequence = (it->second * histogram.rows) / m_greyMax;
        cv::line(histogram, CvPoint((it->first * (histogram.rows/ 256)), histogram.rows), CvPoint((it->first * (histogram.rows/ 256)), histogram.rows - frequence), CvScalar(0, 0, 255), 1, CV_AA);
    }

    cv::namedWindow(nameWindow); /* Create a window for display */
    cv::imshow(nameWindow, histogram);  /* Show our image inside it */
    cv::moveWindow(nameWindow, m_pos_x + m_image->rows, m_pos_y);
}

void Histogram::expension(std::string nameWindow) {
    cv::Mat expension_img = cv::Mat::zeros(m_image->rows, m_image->cols, CV_8UC1);

    for(unsigned row = 0; row < m_image->rows; ++row) {
        for(unsigned col = 0; col < m_image->cols; ++col) {
            uchar val = (uchar) 255*(m_image->at<uchar>(row, col) - m_min)/(m_max - m_min);
            expension_img.at<uchar>(row, col) = val;
        }
    }

    Histogram histogram(&expension_img, m_pos_x, m_pos_y + m_image->cols);
    histogram.draw("Expension histogram");

    cv::namedWindow(nameWindow); /* Create a window for display */
    cv::imshow(nameWindow, expension_img);  /* Show our image inside it */
    cv::moveWindow(nameWindow,  m_pos_x, m_pos_y + m_image->cols);
}