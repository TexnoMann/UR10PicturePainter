#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <cmath>

using namespace ur_rtde;
using namespace std::chrono;

int main(int argc, char* argv[])
{
  RTDEControlInterface rtde_control("192.168.88.5");
  RTDEReceiveInterface rtde_receive("192.168.88.5");
  // Parameters
  double velocity = 0.5;
  double acceleration = 0.5;
  double dt = 1.0/500; // 2ms
  double lookahead_time = 0.1;
  double gain = 300;
  std::vector<double> joint_q = rtde_receive.getActualQ();
  double jq = joint_q[5];
  unsigned int i = 0;
  std::cout << "Start!!!" << std::endl;
  while(true)
  {
    auto t_start = high_resolution_clock::now();
    rtde_control.servoJ(joint_q, velocity, acceleration, dt, lookahead_time, gain);
    joint_q[5] = jq + sin(i++*0.001);
    // joint_q[1] += 0.001;
    auto t_stop = high_resolution_clock::now();
    auto t_duration = std::chrono::duration<double>(t_stop - t_start);
    if (t_duration.count() < dt)
    {
      std::this_thread::sleep_for(std::chrono::duration<double>(dt - t_duration.count()));
    }
  }

  rtde_control.servoStop();
  rtde_control.stopScript();

  return 0;
}
