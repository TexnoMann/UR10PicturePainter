#include "trj_planer/trj_planer.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <property_manager/property_manager.h>

using namespace std;
using namespace Eigen;

int main(int argc, char const* argv[]){

  //Making test trajectory(circle)
  int N=3000;
  double timeDelay=0.002;
  double maxVelocity=0.1;
  double heigh=0.01;

  if (argc !=2){spdlog::error("Please given arguments: ./build/test_trj_planer config/robot.json"); return 0;}
  std::string config_filename=argv[1];
  prop::init(config_filename);

  TrjPlaner planer(timeDelay, 0.05, 0.2, 0.1, 0);
  spdlog::info("[INFO] create planer");

  Path p;
  ofstream file;
  file.open("test_trj.csv");

  spdlog::info("[INFO] Open file");
  VectorXd point1 =VectorXd::Zero(4);
  for( int i = 0; i < N; i++){
    point1<<500+500 *sin(i*timeDelay*1), 500+500*cos(i*timeDelay*1), 0.0, 1.0;
    p.emplace_back(point1);
  }


  Path pt;
  planer.transformPointsAndScale(p, pt);

  spdlog::info("[INFO] generate circle");
  PathTimeDist  out;

  bool ok = planer.getPathWithTime(pt,maxVelocity,out);
  if (!ok){
    spdlog::error("[TRJ PLANER] Problem with trajectory planer: overspeed, or uncorrect path");
    return -1;
  }


  file<<"x y z t\n";
  for(int i = 0; i < out.size(); i++){
    std::string row = to_string(out[i].point(0)) + "," + to_string(out[i].point(1)) + "," + to_string(out[i].point(2)) + "," + to_string(out[i].ts);
    file<<row<<"\n";
  }
  file.close();
  spdlog::info("exit");
  return 0;
}
