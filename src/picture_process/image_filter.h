#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "spdlog/spdlog.h"

class Filter{
public:
  void sobelFilt(cv::Mat & src_image, cv::Mat & out_image ,int ksize, double delta, double scale, int ddepth);
  void convertToGray(cv::Mat & image, cv::Mat & grayImage);
  void gusianBlurFilt(cv::Mat &src_image, int window);
  void contrastFilt(cv::Mat & image, cv::Mat & out_image, int step);
};
