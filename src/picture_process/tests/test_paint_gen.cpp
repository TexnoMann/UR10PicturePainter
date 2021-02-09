#include "picture_process/contour_finder.h"
#include "spdlog/spdlog.h"
#include <trj_planer/trj_planer.h>
#include <property_manager/property_manager.h>

#define CIM 1 // it's CV_LOAD_IMAGE_COLOR for opencv < 4.0 and IMREAD_COLOR > 4.0

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]){
  if( argc != 4){
    spdlog::error("Usage: ./build/test_paint_gen test_image config_file");
    return -1;
  }

  Mat image;
  image = imread(argv[1], CIM);   // Read the file

  if(! image.data ){
    cout <<  "Could not open or find the image" << std::endl;
    return -1;
  }

  ContoursFinder cf;
  LayerParser parser(1,10,255);

  spdlog::info("[START] Test normal image");
  imshow( "Test image", image );
  waitKey(0);

  Mat image_contours =Mat::zeros( image.size(), CV_8UC3 );

  parser.parseLayers(image, 1, 1, 2, CV_16S);
  ImageLayers il = parser.getLayers();
  spdlog::info("[LAYER PARSER] Count layers: {}", il.size());
  cf.generateContours(il);
  cf.getImageFromContours(image_contours);
  spdlog::info("[CONTOUR FINDER] Image for contours");
  LayersPaths l;
  cf.convertToPaths(l);
  spdlog::info("[CONTOUR FINDER] ConvertToPoints");
  imshow( "Test image", image_contours );
  waitKey(0);

  double timeDelay=0.002;
  double maxVelocity=1;
  double heigh=0.01;

  std::string config_filename=argv[2];
  prop::init(config_filename);
  TrjPlaner planer(timeDelay, 0.6, 0.1, 1, 0);
  spdlog::info("[INFO] create planer");
  spdlog::info("[INFO] count curves {0}", l[0].size());
  for( int i = 0; i < l[0].size(); i++){
      Path p;
      ofstream file;
      file.open(std::string(argv[3])+"/trj" + to_string(i) + ".csv");

      spdlog::info("[INFO] Open output file");



      for(int j = 0; j<l[0][i].size();j++) {
          Eigen::VectorXd point1 = Eigen::VectorXd::Zero(4);
          // std::cout << l[0][i][j](0)<<" "<< l[0][i][j](1)<<" "<<l[0][i][j](2)<<" "<<l[0][i][j](3)<<std::endl;
          point1 << l[0][i][j](0), l[0][i][j](1), l[0][i][j](2), l[0][i][j](3);
          p.emplace_back(point1);
      }


      Path pt;
      planer.transformPointsAndScale(p, pt);

      spdlog::info("[INFO] generate trj {}", i);
      PathTimeDist  out;

      bool ok = planer.getPathWithTime(pt, 0.02, out);
      if (!ok){
          spdlog::error("[TRJ PLANER] Problem with trajectory planer: overspeed, or uncorrect path");
          return -1;
      }

      std::string row = to_string(out[0].point(0)) + "," + to_string(out[0].point(1)) + "," + to_string(out[0].point(2)) + "," + to_string(out[0].ts);
      file<<row<<"\n";
      for(int j = 0; j < out.size(); j++){
          std::string row = to_string(out[j].point(0)) + "," + to_string(out[j].point(1)) + "," + to_string(out[j].point(2)) + "," + to_string(out[j].ts);
          file<<row<<"\n";
      }

      file.close();
  }


  spdlog::info("exit");
  return 0;
}
