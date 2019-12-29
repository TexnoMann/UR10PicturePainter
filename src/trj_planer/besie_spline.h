class BesieSpline(){
public:
  BesieSpline();
  void makeSpline(Path path);
  Point getPoint(double dist);
private:
  Eigen::MatrixXd _interpM;
  Eigen::VectorXd _controlPoints;
  void solve();

};
