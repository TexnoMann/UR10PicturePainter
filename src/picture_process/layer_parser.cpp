#include "layer_parser.h"


LayerParser::LayerParser(int depthLayers, int thresholdMin, int thresholdMax){
  _thresholdMin=thresholdMin;
  _thresholdMax=thresholdMax;
  _intesiveStep=(_thresholdMax-_thresholdMin)/(depthLayers);

  ImageLayers _layers(depthLayers);
}

void LayerParser::parseLayers(cv::Mat src_image, int ksize, double delta, double scale, int ddepth){
  if (ksize % 2 ==0){
    spdlog::error("[SOBEL_F] Gived invalid kernel size for filtering!");
    throw;
  }
  _layers.clear();
  cv::Mat out_image;
  _ft.contrastFilt(src_image, src_image , 50);
  _ft.sobelFilt(src_image, out_image, ksize, delta, scale, ddepth);
  for(int intesive=_thresholdMax; intesive >= _thresholdMin; intesive-=_intesiveStep){
    cv::Mat layer;
    threshold(out_image, layer, intesive, 255, 3);
    _ft.gusianBlurFilt(out_image,3);
    try{
//      cv::subtract(out_image, layer, out_image);
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
