#include "spdlog/spdlog.h"
#include "picture_process/layer_parser.h"

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]){
  if( argc != 2){
    cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
    return -1;
  }

  Mat image;
  LayerParser parser(5,50,255);
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data ){
    cout <<  "Could not open or find the image" << std::endl;
    return -1;
  }

  parser.parseLayers(image, 3, 2, 1, CV_16S);
  ImageLayers il = parser.getLayers();

  Mat sum;
  for (unsigned int i =0; i<il.size();i++){
    imshow( "Test image", il[i]);
    std::string message = "[LAYER_PARSER] Show layer: " + std::to_string(i);;
    spdlog::info(message);
    waitKey(0);
  }
}
