#include "contour_finder.h"

ContoursFinder::ContoursFinder(){}

LayersContours ContoursFinder::getContours(){
 return _layers_contours;
}

void ContoursFinder::generateContours(ImageLayers &layers){
  std::vector<cv::Vec4i> hi;
  for(unsigned int i=0; i<layers.size();i++){
    Contours con;
    findContours( layers[i], con, hi, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));
    _hierarchy.emplace_back(hi);
    _layers_contours.emplace_back(con);
  }
}

void ContoursFinder::getImageFromContours(cv::Mat & image){
for(size_t j = 0; j < _layers_contours.size(); j++ ){
  cv::RNG rng(12345);
  for( size_t i = 0; i < _layers_contours[j].size(); i++ )
      {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( image, _layers_contours[j], (int)i, color, 2, 8, _hierarchy[j], 0, cv::Point() );
      }
  }
}

void ContoursFinder::convertToPaths(LayersPaths &out_layers_paths){
  for(auto const & contours : _layers_contours){
    Paths p;
    for(unsigned int i=0; i<contours.size(); i++){
      std::vector<Eigen::VectorXd> one_part;
      for(unsigned int j=0; j<contours[i].size(); j++){
        Eigen::VectorXd point = Eigen::VectorXd::Zero(4);
        point<< contours[i][j].x, contours[i][j].y, 0, 1;
        one_part.emplace_back(point);
      }
      p.emplace_back(one_part);
    }
    out_layers_paths.emplace_back(p);
  }
}

void ContoursFinder::getLayersContours(LayersContours &l, LayersHi & hi) {
    l = _layers_contours;
    hi = _hierarchy;
}
