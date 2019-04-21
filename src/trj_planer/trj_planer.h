#pragma once

#include <vector>
#include <Eigen/Dense>
#include "spdlog/spdlog.h"

using Path = std::vector<Eigen::Vector3d>;
using PointTimeDist = std::pair< std::pair< Eigen::Vector3d , double > , double >;
using PathTimeDist = std::vector<PointTimeDist>;

struct LineBesie{
  public:
    Eigen::Vector3d _p0;
    Eigen::Vector3d _p1;
    LineBesie(Eigen::Vector3d p0, Eigen::Vector3d p1){
      _p0=p0;
      _p1=p1;
    }
    Eigen::Vector3d getPoint(double time){
      return (1-time)*_p0+time*_p1;
    }

    double getDistance(){
      return sqrtf(powf((_p1[0]-_p0[0]),2)+powf((_p1[1]-_p0[1]),2)+powf((_p1[2]-_p0[2]),2));
    }
};


class TrjPlaner{
public:
  TrjPlaner(double timeDelay, double maxLinDistance, double maxAccel, double maxVelocity, double heigh);
  bool getPathWithTime(Path & path, double velocity, PathTimeDist & out);
  bool freeMoving(Eigen::Vector3d p1, Eigen::Vector3d p2, double velocity,  PathTimeDist timefreeMovePath);
private:
  double _timeDelay;
  double _maxLinDistance;
  double _maxAccel;
  double _maxVelocity;
  double _heigh;
};
