#include "trj_planer.h"
#include <iostream>


TrjPlaner::TrjPlaner(double timeDelay, double maxLinDistance, double maxAccel, double maxVelocity, double heigh){
  _maxAccel = maxAccel;
  _maxVelocity = maxVelocity;
  _timeDelay = timeDelay;
  _heigh = heigh;
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
