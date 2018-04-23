#include <sstream>

#include "Measure.hpp"

Measure::Measure() {}

Measure::Measure(cv::Mat *image_sobel, cv::Mat *image_laplace,
                 cv::Mat *image_canny, cv::Mat *image_ref) {
    this->image_sobel = image_sobel;
    this->image_laplace = image_laplace;
    this->image_canny = image_canny;
    this->image_ref = image_ref;

    update();
}

Measure::Measure(cv::Mat *image_ref) { this->image_ref = image_ref; }

void Measure::update() {
    for (unsigned i = 1; i < image_ref->rows - 1; ++i) {
        for (unsigned j = 1; j < image_ref->cols - 1; ++j) {
            if (image_sobel != nullptr && image_sobel->at<uchar>(i, j) == 0) {
                contours_detectes[SOBEL]++;
            }

            if (image_laplace != nullptr &&
                image_laplace->at<uchar>(i, j) == 0) {
                contours_detectes[LAPLACE]++;
            }

            if (image_canny != nullptr && image_canny->at<uchar>(i, j) == 0) {
                contours_detectes[CANNY]++;
            }

            if (image_ref->at<uchar>(i, j) == 0) {
                contours_detectes[REF]++;

                bool alreadysob = false;
                bool alreadylap = false;
                bool alreadycan = false;

                // Contour correct
                for (int x = -1; x < 2; ++x) {
                    for (int y = -1; y < 2; ++y) {
                        if (image_sobel != nullptr &&
                            image_sobel->at<uchar>(i + x, j + y) == 0 &&
                            !alreadysob) {
                            alreadysob = true;
                            contours_correct[SOBEL]++;
                        }

                        if (image_laplace != nullptr &&
                            image_laplace->at<uchar>(i + x, j + y) == 0 &&
                            !alreadylap) {
                            alreadylap = true;
                            contours_correct[LAPLACE]++;
                        }

                        if (image_canny != nullptr &&
                            image_canny->at<uchar>(i + x, j + y) == 0 &&
                            !alreadycan) {
                            alreadycan = true;
                            contours_correct[CANNY]++;
                        }
                    }
                }
            }
        }
    }

    updateFauxPositif();
    updateFauxNegatif();
    updateP();
    updateTFP();
    updateTFN();
}

void Measure::updateFauxPositif() {
    // Faux positif
    // if (contours_detectes[SOBEL] > 0) {
    faux_positifs[SOBEL] = (contours_detectes[SOBEL] - contours_correct[SOBEL]);
    // }

    // if (contours_detectes[LAPLACE] > 0) {
    faux_positifs[LAPLACE] =
        (contours_detectes[LAPLACE] - contours_correct[LAPLACE]);
    // }

    // if (contours_detectes[CANNY] > 0) {
    faux_positifs[CANNY] = (contours_detectes[CANNY] - contours_correct[CANNY]);
    // }
}

void Measure::updateFauxNegatif() {
    // if (contours_detectes[SOBEL] > 0) {
    faux_negatifs[SOBEL] = (contours_detectes[REF] - contours_correct[SOBEL]);
    // }

    // if (contours_detectes[LAPLACE] > 0) {
    faux_negatifs[LAPLACE] =
        (contours_detectes[REF] - contours_correct[LAPLACE]);
    // }

    // if (contours_detectes[CANNY] > 0) {
    faux_negatifs[CANNY] = (contours_detectes[REF] - contours_correct[CANNY]);
    // }
}

void Measure::updateP() {
    // Performance
    if (contours_detectes[SOBEL] > 0) {
        P[SOBEL] = (double)contours_correct[SOBEL] /
                   (double)(contours_correct[SOBEL] + faux_positifs[SOBEL] +
                            faux_negatifs[SOBEL]);
    }

    if (contours_detectes[LAPLACE] > 0) {
        P[LAPLACE] = (double)contours_correct[LAPLACE] /
                     (double)(contours_correct[LAPLACE] +
                              faux_positifs[LAPLACE] + faux_negatifs[LAPLACE]);
    }

    if (contours_detectes[CANNY] > 0) {
        P[CANNY] = (double)contours_correct[CANNY] /
                   (double)(contours_correct[CANNY] + faux_positifs[CANNY] +
                            faux_negatifs[CANNY]);
    }
}

void Measure::updateTFP() {
    // Taux faux positif
    TFP[SOBEL] = (double)faux_positifs[SOBEL] /
                 (double)(contours_correct[SOBEL] + faux_positifs[SOBEL] +
                          faux_negatifs[SOBEL]);

    TFP[LAPLACE] = (double)faux_positifs[LAPLACE] /
                   (double)(contours_correct[LAPLACE] + faux_positifs[LAPLACE] +
                            faux_negatifs[LAPLACE]);

    TFP[CANNY] = (double)faux_positifs[CANNY] /
                 (double)(contours_correct[CANNY] + faux_positifs[CANNY] +
                          faux_negatifs[CANNY]);
}

void Measure::updateTFN() {
    // Taux faux négatif
    TFN[SOBEL] = (double)faux_negatifs[SOBEL] /
                 (double)(contours_correct[SOBEL] + faux_positifs[SOBEL] +
                          faux_negatifs[SOBEL]);

    TFN[LAPLACE] = (double)faux_negatifs[LAPLACE] /
                   (double)(contours_correct[LAPLACE] + faux_positifs[LAPLACE] +
                            faux_negatifs[LAPLACE]);

    TFN[CANNY] = (double)faux_negatifs[CANNY] /
                 (double)(contours_correct[CANNY] + faux_positifs[CANNY] +
                          faux_negatifs[CANNY]);
}

void Measure::setParam(int index, int b, int param, int s) {
    this->param_b[index] = b;
    this->param_p[index] = param;
    this->param_s[index] = s;
}

std::string Measure::toCSV() const {
    /****************************************************************************
     *
     * Image; Méthode; Contours Détectés; Contours Référence; Contours "
            "correct; Faux positif; Faux négatifs; Performance; Taux de faux "
            "positif; Taux de faux négatif; Meilleur scale; Meilleur seuil; "
            "Meilleur blur
     *
     ****************************************************************************/
    std::ostringstream oss;

    // SOBEL Line
    oss << "SOBEL; ";
    oss << contours_detectes[SOBEL] << "; ";
    oss << contours_detectes[REF] << "; ";
    oss << contours_correct[SOBEL] << "; ";
    oss << faux_positifs[SOBEL] << "; ";
    oss << faux_negatifs[SOBEL] << "; ";
    oss << P[SOBEL] << "; ";
    oss << TFP[SOBEL] << "; ";
    oss << TFN[SOBEL] << "; ";
    oss << param_b[SOBEL] << "; ";
    oss << param_p[SOBEL] << "; ";
    oss << param_s[SOBEL];
    oss << "\n";

    // LAPLACE line
    oss << "; ";
    oss << "LAPLACE; ";
    oss << contours_detectes[LAPLACE] << "; ";
    oss << contours_detectes[REF] << "; ";
    oss << contours_correct[LAPLACE] << "; ";
    oss << faux_positifs[LAPLACE] << "; ";
    oss << faux_negatifs[LAPLACE] << "; ";
    oss << P[LAPLACE] << "; ";
    oss << TFP[LAPLACE] << "; ";
    oss << TFN[LAPLACE] << "; ";
    oss << param_b[LAPLACE] << "; ";
    oss << param_p[LAPLACE] << "; ";
    oss << param_s[LAPLACE];
    oss << "\n";

    // CANNY Line
    oss << "; ";
    oss << "CANNY; ";
    oss << contours_detectes[CANNY] << "; ";
    oss << contours_detectes[REF] << "; ";
    oss << contours_correct[CANNY] << "; ";
    oss << faux_positifs[CANNY] << "; ";
    oss << faux_negatifs[CANNY] << "; ";
    oss << P[CANNY] << "; ";
    oss << TFP[CANNY] << "; ";
    oss << TFN[CANNY] << "; ";
    oss << param_b[CANNY] << "; ";
    oss << param_p[CANNY] << "; ";

    if (param_s[CANNY] == -1) {
        oss << "Undefined";
    } else {
        oss << param_s[CANNY];
    }

    oss << "\n";

    return oss.str();
}

bool Measure::isBestSobel(const Measure &m) const {
    return m.P[SOBEL] < this->P[SOBEL];
}

void Measure::setSobel(const Measure &m) {
    this->param_s[SOBEL] = m.param_s[SOBEL];
    this->param_p[SOBEL] = m.param_p[SOBEL];
    this->param_b[SOBEL] = m.param_b[SOBEL];
    this->contours_detectes[SOBEL] = m.contours_detectes[SOBEL];
    this->contours_correct[SOBEL] = m.contours_correct[SOBEL];
    this->faux_positifs[SOBEL] = m.faux_positifs[SOBEL];
    this->faux_negatifs[SOBEL] = m.faux_negatifs[SOBEL];
    this->P[SOBEL] = m.P[SOBEL];
    this->TFP[SOBEL] = m.TFP[SOBEL];
    this->TFN[SOBEL] = m.TFN[SOBEL];
    this->contours_detectes[REF] = m.contours_detectes[REF];
}

bool Measure::isBestLaplace(const Measure &m) const {
    return m.P[LAPLACE] < this->P[LAPLACE];
}

void Measure::setLaplace(const Measure &m) {
    this->param_s[LAPLACE] = m.param_s[LAPLACE];
    this->param_p[LAPLACE] = m.param_p[LAPLACE];
    this->param_b[LAPLACE] = m.param_b[LAPLACE];
    this->contours_detectes[LAPLACE] = m.contours_detectes[LAPLACE];
    this->contours_correct[LAPLACE] = m.contours_correct[LAPLACE];
    this->faux_positifs[LAPLACE] = m.faux_positifs[LAPLACE];
    this->faux_negatifs[LAPLACE] = m.faux_negatifs[LAPLACE];
    this->P[LAPLACE] = m.P[LAPLACE];
    this->TFP[LAPLACE] = m.TFP[LAPLACE];
    this->TFN[LAPLACE] = m.TFN[LAPLACE];
    this->contours_detectes[REF] = m.contours_detectes[REF];
}

bool Measure::isBestCanny(const Measure &m) const {
    return m.P[CANNY] < this->P[CANNY];
}

void Measure::setCanny(const Measure &m) {
    this->param_s[CANNY] = m.param_s[CANNY];
    this->param_p[CANNY] = m.param_p[CANNY];
    this->param_b[CANNY] = m.param_b[CANNY];
    this->contours_detectes[CANNY] = m.contours_detectes[CANNY];
    this->contours_correct[CANNY] = m.contours_correct[CANNY];
    this->faux_positifs[CANNY] = m.faux_positifs[CANNY];
    this->faux_negatifs[CANNY] = m.faux_negatifs[CANNY];
    this->P[CANNY] = m.P[CANNY];
    this->TFP[CANNY] = m.TFP[CANNY];
    this->TFN[CANNY] = m.TFN[CANNY];
    this->contours_detectes[REF] = m.contours_detectes[REF];
}

void Measure::setImageSobel(cv::Mat *image_sobel) {
    this->image_sobel = image_sobel;
    this->contours_detectes[REF] = 0;
    this->contours_detectes[SOBEL] = 0;
    this->contours_correct[SOBEL] = 0;
    update();
}

void Measure::setImageLaplace(cv::Mat *image_laplace) {
    this->image_laplace = image_laplace;
    this->contours_detectes[REF] = 0;
    this->contours_detectes[LAPLACE] = 0;
    this->contours_correct[LAPLACE] = 0;
    update();
}

void Measure::setImageCanny(cv::Mat *image_canny) {
    this->image_canny = image_canny;
    this->contours_detectes[REF] = 0;
    this->contours_detectes[CANNY] = 0;
    this->contours_correct[CANNY] = 0;
    update();
}