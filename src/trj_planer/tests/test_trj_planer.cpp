#include "trj_planer/trj_planer.h"
#include "spdlog/spdlog.h"
#include <fstream>

using namespace std;
using namespace Eigen;

int main(int argc, char const* argv[]){

  //Making test trajectory(circle)
  int N=50;
  double timeDelay=0.008;
  double maxVelocity=0.02;
  double heigh=0.02;

  Path p;
  ofstream file;
  file.open("out.csv");

  for( int i = 0; i < N; i++){
    Vector3d point1={sin(i*timeDelay*10), cos(i*timeDelay*10), heigh};
    p.emplace_back(point1);
  }

  PathTimeDist  out;
  TrjPlaner planer(timeDelay, 0.1, 1, 0.02, heigh);

  bool ok = planer.getPathWithTime(p,0.02,out);
  if (!ok){
    spdlog::error("[TRJ PLANER] Problem with trajectory planer: overspeed, or uncorrect path");
    return -1;
  }
  file<<"x y t\n";
  for(int i = 0; i < out.size(); i++){
    std::string row = to_string(out[i].first.first[0]) + " " + to_string(out[i].first.first[1]) + " " + to_string(out[i].first.first[2]) + " " + to_string(out[i].second);
    file<<row<<"\n";
  }
  file.close();
  spdlog::info("exit");
  return 0;
}
