#include "picture_process/image_filter.h"
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
  Filter cf;
  image = imread(argv[1], CIM);   // Read the file

  if(! image.data ){
    cout <<  "Could not open or find the image" << std::endl;
    return -1;
  }

  spdlog::info("[START] Test normal image");
  imshow( "Test image", image );
  waitKey(0);

  Mat new_image;
  cf.convertToGray(image, new_image);
  imshow( "Test image", new_image );
  spdlog::info("[GRAY] Test gray image");
  waitKey(0);

  // image.copyTo(new_image);
  // cf.gusianBlurFilt(new_image, 3);
  // imshow( "Test image", new_image);
  // spdlog::info("[GAUS_F] Test gausian filter");
  // waitKey(0);
  // //
  image.copyTo(new_image);
  cf.contrastFilt(image, new_image , 20);
  imshow( "Test image", new_image);
  spdlog::info("[CONTRAST_F] Test sobel filter");
  waitKey(0);

  Mat proc_image;
  new_image.copyTo(proc_image);
  image.copyTo(new_image);

  cf.sobelFilt(image, new_image ,1, 1, 2, CV_16S);
  imshow( "Test image", new_image);
  spdlog::info("[SOBEL_F] Test sobel filter");
  waitKey(0);


  cf.sobelFilt(proc_image, new_image ,1, 3, 2, CV_16S);
  imshow( "Test image", new_image);
  spdlog::info("[SOBEL_F] Test sobel filter after contrast filter");
  waitKey(0);

  spdlog::info("exit");
  return 0;
}
