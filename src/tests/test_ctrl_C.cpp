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
  std::cout << "Start it!" << std::endl;
  for (int i = 0; i < 5; i++ )
  {
      std::vector<double> cart_pos = rtde_receive.getActualTCPPose();
      std::cout << cart_pos[0] << "  " << cart_pos[1] << "  " << cart_pos[2] << std::endl;
      std::cout << cart_pos[3] << "  " << cart_pos[4] << "  " << cart_pos[5] << std::endl;
      cart_pos[0] +=0.1;
      rtde_control.moveL(cart_pos,0.05,0.05,false);
      cart_pos[1] +=0.1;
      rtde_control.moveL(cart_pos,0.05,0.05,false);
      cart_pos[0] -=0.1;
      rtde_control.moveL(cart_pos,0.05,0.05,false);
      cart_pos[1] -=0.1;
      rtde_control.moveL(cart_pos,0.05,0.05,false);
  }

  // cart_pos[0]=0;
  // cart_pos[1]=-1.5708;
  // cart_pos[2]+=0.1;
  // cart_pos[3]=-1.5708;
  // cart_pos[4]=0;
  // cart_pos[5]=0;

  // std::vector<double> target = rtde_receive.getTargetTCPPose();
  // std::cout << target[0] << "  " << target[1] << "  " << target[2] << std::endl;
  // std::cout << target[3] << "  " << target[4] << "  " << target[5] << std::endl;
  // std::this_thread::sleep_for(std::chrono::milliseconds(200));
  // cart_pos[1] += 0.1;
  // rtde_control.moveL(cart_pos,0.05,0.05,false);
  // std::this_thread::sleep_for(std::chrono::milliseconds(200));
  // cart_pos[0] += 0.1;
  // rtde_control.moveL(cart_pos,0.05,0.05,false);
  // std::this_thread::sleep_for(std::chrono::milliseconds(200));
  // rtde_control.stopL(0.5);


  rtde_control.servoStop();
  rtde_control.stopScript();

  return 0;
}
