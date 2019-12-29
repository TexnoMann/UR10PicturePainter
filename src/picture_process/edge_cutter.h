#pragma once
#include "contour_finder.h"

class EdgeCutter {
public:
    EdgeCutter(int minSize, int cuttungCount);
    void cutImage(cv::Mat & image, const LayersContours & lcontours, LayersContours & lcontoursOut);
private:
    int _cuttingCount;
    int _minCutSize;
};
