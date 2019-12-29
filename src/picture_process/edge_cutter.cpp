
#include "edge_cutter.h"

EdgeCutter::EdgeCutter(int minSize, int cuttingCount) {
    _minCutSize = minSize;
    _cuttingCount = cuttingCount;
}

void EdgeCutter::cutImage(cv::Mat &image, LayersContours &lcontoursOut, ContoursFinder & cf) {
    LayersContours  contours;
    LayersHi  hierarchy;
    cf.getLayersContours(contours, hierarchy);
    for (int i=0;i<contours.size();i++){
        cv::Scalar color = ( 255,255,255);
        drawContours( image, contours[j], (int)i, color, _minCutSize, 8, hierarchy[j], 0, cv::Point() );
    }
}