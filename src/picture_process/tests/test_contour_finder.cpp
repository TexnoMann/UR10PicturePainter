#include "picture_process/contour_finder.h"
#include "spdlog/spdlog.h"

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]){
  if( argc != 2){
    cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data ){
    cout <<  "Could not open or find the image" << std::endl;
    return -1;
  }

  ContoursFinder cf;
  LayerParser parser(5,50,255);

  spdlog::info("[START] Test normal image");
  imshow( "Test image", image );
  waitKey(0);

  Mat image_contours =Mat::zeros( image.size(), CV_8UC3 );

  parser.parseLayers(image, 3, 2, 1, CV_16S);
  ImageLayers il = parser.getLayers();
  cf.generateContours(il);
  cf.getImageFromContours(image_contours);
  spdlog::info("[CONTOUR FINDER] Image for contours");
  imshow( "Test image", image_contours );
  waitKey(0);
  spdlog::info("exit");
  return 0;
}
