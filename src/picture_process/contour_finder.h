#pragma once

#include "layer_parser.h"
#include <Eigen/Dense>


using Contours =std::vector<std::vector<cv::Point>>;
using LayersContours = std::vector<Contours>;

using Paths = std::vector<std::vector<Eigen::Vector2d>>;
using LayersPaths = std::vector<Paths>;

class ContoursFinder{
  public:
    ContoursFinder();
    LayersContours getContours();
    void getImageFromContours(cv::Mat & image);
    void generateContours(ImageLayers &layers);
    void convertToPaths(LayersPaths & out_paths);

  private:
    LayersContours _layers_contours;
    std::vector<std::vector<cv::Vec4i>> _hierarchy;
};
