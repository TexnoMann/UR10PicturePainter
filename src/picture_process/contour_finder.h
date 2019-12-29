#pragma once

#include "layer_parser.h"
#include <Eigen/Dense>

#define MIN_AREA_SIZE 10

using Contours =std::vector<std::vector<cv::Point>>;
using LayersContours = std::vector<Contours>;

using Paths = std::vector<std::vector<Eigen::VectorXd>>;
using LayersPaths = std::vector<Paths>;
using LayersHi =std::vector<std::vector<cv::Vec4i>>;

class ContoursFinder{
  public:
    ContoursFinder();
    LayersContours getContours();
    void getImageFromContours(cv::Mat & image);
    void generateContours(ImageLayers &layers);
    void convertToPaths(LayersPaths & out_paths);
    void getLayersContours(LayersContours & l, LayersHi & hi);

  private:
    LayersContours _layers_contours;
    LayersHi _hierarchy;
};
