#pragma once

#include "image_filter.h"
#include "spdlog/spdlog.h"

using ImageLayers = std::vector<cv::Mat>;

class LayerParser{
public:
  LayerParser(int depthLayers, int thresholdMin, int thresholdMax);
  void parseLayers(cv::Mat src_image, int ksize, double delta, double scale, int ddepth);
  void parseLayersEros(cv::Mat src_image, int ksize, double delta, double scale, int ddepth);
  ImageLayers getLayers();
  void parseCountours();
private:
 int _intesiveStep;
 int _thresholdMin;
 int _thresholdMax;
 ImageLayers _layers;
 Filter _ft;
};
