#include "picture_process/contour_finder.h"
#include "spdlog/spdlog.h"

#define CIM 1 // it's CV_LOAD_IMAGE_COLOR for opencv < 4.0 and IMREAD_COLOR > 4.0

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]){
  if( argc != 2){
    cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], CIM);   // Read the file

  if(! image.data ){
    cout <<  "Could not open or find the image" << std::endl;
    return -1;
  }

  ContoursFinder cf;
  LayerParser parser(1,80,255);

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
  spdlog::info("exit");
  return 0;
}
