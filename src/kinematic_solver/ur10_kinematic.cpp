#include "ur10_kinematic.h" 


ur10_kinematic::ur10_kinematic(){
	_d << 0.1273, 0.0000, 0.0000, 0.1639, 0.1157, 0.0922;
	_a << 0.0000, 0.6120, 0.5723, 0.0000, 0.0000, 0.0000;
}

ur10_kinematic::ik_solver(VectorXd point,MatrixXd turn,VectorXd last_state){
		// VectorXd turn_point = turn * point;



	

}
