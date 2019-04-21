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
  std::vector<double> qdata = prop::getVector<double>(canvasInfo, "quaternion");
  std::vector<double> tdata = prop::getVector<double>(canvasInfo, "translation");

  _scaleFactor = Eigen::Matrix3d::Identity();

  Eigen::Quaterniond q(qdata[0], qdata[1], qdata[2], qdata[3]);
  _planeRotMatrix = q.normalized().toRotationMatrix();

  _planeTransVector = Eigen::Vector3d(tdata[0], tdata[1], tdata[2]);
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
      pt ={{line.getPoint(t*timeNorm), globalDistPart}, globalTimePart+t};
      out.emplace_back(pt);
    }
    globalTimePart+=timePart;
  }
  return true;
}

bool TrjPlaner::freeMoving(Eigen::Vector3d p1, Eigen::Vector3d p2, double velocity,  PathTimeDist timefreeMovePath){
  Eigen::Vector3d p1h=p1;
  Eigen::Vector3d p2h=p2;
  p1h[2]=_heigh;
  p2h[2]=_heigh;
  Path freeMovePath = {p1,p1h,p2h,p2};
  return getPathWithTime(freeMovePath, velocity, timefreeMovePath);
}

void TrjPlaner::transformPointsAndScale(const Path & path, Path & out)
{
  Eigen::Matrix3d transform = _planeRotMatrix*_scaleFactor;
  out.resize(path.size());
  for (size_t i = 0; i < path.size(); ++i) {
    out[i] = transform*path[i] + _planeTransVector;
  }
}