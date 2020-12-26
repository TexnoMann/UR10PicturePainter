#pragma once

#include <vector>
#include <Eigen/Dense>
#include "spdlog/spdlog.h"

struct PointTimeDist;

using Path = std::vector<Eigen::VectorXd>;
using PathTimeDist = std::vector<PointTimeDist>;

struct PointTimeDist{
public:
    double ts;
    double dist;
    Eigen::VectorXd point;

    PointTimeDist(){
        ts = 0;
        dist=0;
        point = Eigen::VectorXd::Zero(4);
    }

    PointTimeDist(double time, double distance, Eigen::VectorXd pointVec){
        ts = time;
        dist = distance;
        point  = pointVec;
    }
};

struct LineBesie{
public:
    Eigen::VectorXd _p0 = Eigen::VectorXd::Zero(4);
    Eigen::VectorXd _p1 = Eigen::VectorXd::Zero(4);
    LineBesie(Eigen::VectorXd p0, Eigen::VectorXd p1){
        _p0=p0;
        _p1=p1;
    }
    Eigen::VectorXd getPoint(double time){
        Eigen::VectorXd p = Eigen::VectorXd::Zero(4);
        p = (1-time)*_p0+time*_p1;
        p(3) = 1.0;
        return p;
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

    // From px to meters
    void transformPointsAndScale(const Path & path, Path & out);

    // Width: x; Height: y

    // Padding in meters
    inline void setPadding(const double padding) {_padding = padding;}

private:
    double _timeDelay;
    double _maxLinDistance;
    double _maxAccel;
    double _maxVelocity;
    double _heigh;
    Eigen::VectorXd _tool_size;
    double _padding;
    Eigen::MatrixXd _scaleFactor;
    std::vector<double> _picture_size;

    Eigen::MatrixXd _planeTransformMatrix;
};
