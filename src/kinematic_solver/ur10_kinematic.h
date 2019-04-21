#include <Eigen/Dense>
#include <cmath>

class ur10_kinematic{
	private:
		VectorXd _d(6);
		VectorXd _a(6);
	public:
		ur10_kinematic();
 		ik_solver(VectorXd point,MatrixXd turn,VectorXd last_state);
 }	