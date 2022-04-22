#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <string>
#include <iostream>
#include <dirent.h>
#include <thread>
#include "csv.h"
#include <experimental/filesystem>
#include "spdlog/spdlog.h"

#include <chrono>

using namespace std::chrono;
using namespace ur_rtde;
namespace fs = std::experimental::filesystem;

// Parameters


bool paint_trj(std::string csv_filename, RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos);
bool go_to_start(std::string csv_filename, RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos);
bool take_up(RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos);

double velocity = 0.4;
double acceleration = 0.05;
double dt = 1.0/500; // 2ms
double lookahead_time = 0.1;
double gain = 300;

int main(int argc, char* argv[])
{
  RTDEControlInterface rtde_control("192.168.88.5");
  RTDEReceiveInterface rtde_receive("192.168.88.5");

  std::string path_trj = argv[1];
  std::vector <std::string> files_list;

  std::vector<double> joint_q = {0.0, -3.14/2, 0.0, -3.14/2, 0.0, 0.0};
  // Move to initial joint position with a regular moveJ
  // rtde_control.moveJ(joint_q);

  std::vector<double> cart_pos = rtde_receive.getActualTCPPose();
  spdlog::info("[State] Cartesian position: {0} {1} {2}", cart_pos[0], cart_pos[1], cart_pos[2]);
  // Execute 500Hz control loop for 2 seconds, each cycle is ~2ms

  for (const auto & entry : fs::directory_iterator(path_trj))
    files_list.push_back(entry.path());

  // take_up(rtde_control, rtde_receive, cart_pos);
  // rtde_control.moveL({-0.226, -0.7068, 0.0368, cart_pos[3], cart_pos[4], cart_pos[5]}, velocity, acceleration);
  // rtde_control.moveL({-0.226, -0.6703, -0.0545, cart_pos[3], cart_pos[4], cart_pos[5]}, velocity, acceleration);
  // cart_pos = rtde_receive.getActualTCPPose();
  // take_up(rtde_control, rtde_receive, cart_pos);
  take_up(rtde_control, rtde_receive, cart_pos);

  for (int i=0; i< files_list.size(); i++){
    go_to_start(files_list[i], rtde_control, rtde_receive, cart_pos);
    spdlog::info("[Draw] Start drawing file: " + files_list[i]);
    paint_trj(files_list[i], rtde_control, rtde_receive, cart_pos);
    cart_pos = rtde_receive.getActualTCPPose();
    cart_pos = rtde_receive.getActualTCPPose();
    cart_pos = rtde_receive.getActualTCPPose();
    take_up(rtde_control, rtde_receive, cart_pos);
  }

  rtde_control.stopScript();

  return 0;
}

bool take_up(RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos){
  cart_pos[2]+= 0.09;
  spdlog::info("[Target] Take Up: {0} {1} {2}", cart_pos[0], cart_pos[1], cart_pos[2]);
  rtde_control.moveL(cart_pos, velocity, acceleration);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

bool paint_trj(std::string csv_filename, RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos){
  io::CSVReader<4> in(csv_filename);
  double x; double y; double z; double t;
  while(in.read_row(x, y, z, t)){
      auto t_start = high_resolution_clock::now();
      cart_pos[0] = x;
      cart_pos[1] = y;
      cart_pos[2] = z;
      rtde_control.servoL(cart_pos, velocity, acceleration, dt, lookahead_time, gain);
      auto t_stop = high_resolution_clock::now();
      auto t_duration = std::chrono::duration<double>(t_stop - t_start);

      if (t_duration.count() < dt)
      {
        std::this_thread::sleep_for(std::chrono::duration<double>(dt - t_duration.count()));
      }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  rtde_control.servoStop();
  return true;
}

bool go_to_start(std::string csv_filename, RTDEControlInterface & rtde_control, RTDEReceiveInterface & rtde_receive, std::vector<double> & cart_pos){
  io::CSVReader<4> in(csv_filename);
  double x; double y; double z; double t;
  in.read_row(x, y, z, t);
  cart_pos[0] = x;
  cart_pos[1] = y;
  cart_pos[2] = z;
  spdlog::info("[Target] Cartesian position: {0} {1} {2}", cart_pos[0], cart_pos[1], cart_pos[2]);
  rtde_control.moveL(cart_pos, velocity, acceleration);
  // std::this_thread::sleep_for(std::chrono::milliseconds(300));
  return true;
}
