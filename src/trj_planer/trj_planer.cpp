#include "trj_planer.h"
#include <iostream>
#include <property_manager/property_manager.h>


TrjPlaner::TrjPlaner(double timeDelay, double maxLinDistance, double maxAccel, double maxVelocity, double heigh){
    _maxAccel = maxAccel;
    _maxVelocity = maxVelocity;
    _timeDelay = timeDelay;
    _heigh = heigh;
    _padding = 0;

    // Quaternion read from file
    ptree canvasInfo = prop::tree().get_child("canvas_info");
    std::vector<double> transform_data = prop::getVector<double>(canvasInfo, "transform_matrix");
    std::vector<double> plane_size = prop::getVector<double>(canvasInfo, "plane_size");
    _picture_size = prop::getVector<double>(canvasInfo, "picture_size");
    std::vector<double> tool_size = prop::getVector<double>(canvasInfo, "tool_size");

    _scaleFactor = Eigen::MatrixXd::Zero(4,4);
    float maxScale = std::fmin(plane_size[0]/_picture_size[0],plane_size[1]/_picture_size[1]);
    spdlog::info("[TRJ PLANER]: scaling picture with scale factor {}", maxScale);
    _scaleFactor(0,0) = maxScale;
    _scaleFactor(1,1) = maxScale;
    _scaleFactor(2,2) = 1;
    _scaleFactor(3,3) = 1;
    _planeTransformMatrix =  Eigen::MatrixXd::Zero(4,4);
    _planeTransformMatrix << transform_data[0], transform_data[1], transform_data[2], transform_data[3],
                            transform_data[4], transform_data[5], transform_data[6], transform_data[7],
                            transform_data[8], transform_data[9], transform_data[10], transform_data[11],
                            transform_data[12], transform_data[13], transform_data[14], transform_data[15];
    spdlog::info("[TRJ PLANER] given transform matrix:");
    std::cout<<_planeTransformMatrix<<std::endl;
    _tool_size = Eigen::VectorXd::Zero(4);
    _tool_size << tool_size[0],tool_size[1], tool_size[2],1;


    spdlog::info("TrjPlaner::TrjPlaner");
}

bool TrjPlaner::getPathWithTime(Path & path, double velocity, PathTimeDist & out){
    if(velocity>_maxVelocity) return false;
    double globalTimePart;
    double globalDistPart;
    PointTimeDist pt;
    double currentDist;
    double timePart;
    double timeNorm;
    for( int i=0; i < path.size()-1; i++){
        LineBesie line(path[i], path[i+1]);
        currentDist=line.getDistance();
        timePart = currentDist/velocity;
        timeNorm = 1.0 / timePart;
        globalDistPart += currentDist;
        for(double t = 0; t <= timePart; t+= _timeDelay){
            globalTimePart+=_timeDelay;
            PointTimeDist pt(globalTimePart, globalDistPart, line.getPoint(t*timeNorm));
            out.emplace_back(pt);
        }
    }
    return true;
}

//bool TrjPlaner::freeMoving(Eigen::VectorXd p1, Eigen::VectorXd p2, double velocity,  PathTimeDist timefreeMovePath){
//  Eigen::VectorXd p1h=p1;
//  Eigen::VectorXd p2h=p2;
//  p1h[2]=_heigh;
//  p2h[2]=_heigh;
//  Path freeMovePath = {p1,p1h,p2h,p2};
//  return getPathWithTime(freeMovePath, velocity, timefreeMovePath);
//}

void TrjPlaner::transformPointsAndScale(const Path & path, Path & out)
{
    out.resize(path.size());
    Path pc=path;
    for (int64_t i = 0; i < path.size(); ++i) {
        pc[i] = Eigen::VectorXd::Zero(4);
        pc[i](0) = path[i](0) - _picture_size[0]/2;
        pc[i](1) = _picture_size[1]/2 - path[i](1);
        pc[i](2) = path[i](2);
        pc[i](3) = path[i](3);
//        out[i] = pc[i];
        out[i] = _planeTransformMatrix * _scaleFactor * pc[i];
    }
}