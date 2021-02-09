#include "layer_parser.h"


LayerParser::LayerParser(int depthLayers, int thresholdMin, int thresholdMax){
  _thresholdMin=thresholdMin;
  _thresholdMax=thresholdMax;
  _intesiveStep=(_thresholdMax-_thresholdMin)/(1.0*depthLayers);

  ImageLayers _layers(depthLayers);
}

void LayerParser::parseLayers(cv::Mat src_image, int ksize, double delta, double scale, int ddepth){
  if (ksize % 2 ==0){
    spdlog::error("[SOBEL_F] Gived invalid kernel size for filtering!");
    throw;
  }
  _layers.clear();
  cv::Mat out_image;
  medianBlur( src_image, src_image, 5);
  _ft.sobelFilt(src_image, out_image, ksize, delta, scale, ddepth);
  for(float intesive= _thresholdMin; intesive <_thresholdMax; intesive+=_intesiveStep){
    spdlog::info("[Threshold] Generate trajectory for intesivity: {0}", intesive);
    cv::Mat layer;
    threshold(out_image, out_image, intesive, _thresholdMax, 3);
    cv::Mat element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ), cv::Point( 1, 1 ) );
    dilate(out_image, out_image, element );
    erode(out_image, layer, element );
    imshow( "Test image2", layer);
    try{
//      cv::subtract(out_image, layer, out_image)
      _layers.emplace_back(layer);
    }catch(std::exception ex){
      spdlog::error("[CONTRAST_F] Gived invalid image for subtract.");
      throw;
   }
 }
}


ImageLayers LayerParser::getLayers(){
  return _layers;
}
