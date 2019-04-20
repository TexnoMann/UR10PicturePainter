#include "contour_finder.h"

ContoursFinder::ContoursFinder(){}

LayersContours ContoursFinder::getContours(){
 return _contours;
}

void ContoursFinder::generateContours(ImageLayers &layers){
  std::vector<cv::Vec4i> hi;
  for(int i=0; i<layers.size();i++){
    Contours con;
    findContours( layers[i], con, hi, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    _hierarchy.emplace_back(hi);
    _contours.emplace_back(con);
  }
}

void ContoursFinder::getImageFromContours(cv::Mat & image){
for(size_t j = 0; j<  _contours.size(); j++ ){
  cv::RNG rng(12345);
  for( size_t i = 0; i< _contours[j].size(); i++ )
      {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( image, _contours[j], (int)i, color, 2, 8, _hierarchy[j], 0, cv::Point() );
      }
  }
}
