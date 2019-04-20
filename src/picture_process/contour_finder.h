#pragma once

#include "layer_parser.h"

using Contours =std::vector<std::vector<cv::Point>>;
using LayersContours = std::vector<Contours>;

class ContoursFinder{
  public:
    ContoursFinder();
    LayersContours getContours();
    void getImageFromContours(cv::Mat & image);
    void generateContours(ImageLayers &layers);
  private:
    LayersContours _contours;
    std::vector<std::vector<cv::Vec4i>> _hierarchy;
};
