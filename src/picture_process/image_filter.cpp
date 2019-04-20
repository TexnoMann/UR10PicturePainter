#include "image_filter.h"

void Filter::convertToGray(cv::Mat & image, cv::Mat & grayImage){
  cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
}

void Filter::sobelFilt(cv::Mat &src_image, cv::Mat &out_image, int ksize, double delta, double scale, int ddepth){
  cv::Mat grad_x, grad_y;
  cv::Mat abs_grad_x, abs_grad_y;
  cv::Mat src_gray;
  convertToGray(src_image, src_gray);
  Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);
  Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);
  // converting back to CV_8U
  convertScaleAbs(grad_x, abs_grad_x);
  convertScaleAbs(grad_y, abs_grad_y);
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out_image);
}

void Filter::gusianBlurFilt(cv::Mat &src_image, int ksize){
  GaussianBlur( src_image, src_image, cv::Size(ksize,ksize), 0, 0, cv::BORDER_DEFAULT );
}

void Filter::contrastFilt(cv::Mat & image, cv::Mat & out_image, int step){
	try
	{
		std::vector<cv::Mat> rgb;
		cv::split(image, rgb);
		cv::Mat lut(1, 256, CV_8UC1);
		double contrastLevel = double(100 + step) / 100;
		uchar* p = lut.data;
		double d;
		for (int i = 0; i < 256; i++)
		{
			d = ((double(i) / 255 - 0.5)*contrastLevel + 0.5) * 255;
			if (d > 255)
				d = 255;
			if (d < 0)
				d = 0;
			p[i] = d;
		}
		cv::LUT(rgb[0], lut, rgb[0]);
		cv::LUT(rgb[1], lut, rgb[1]);
		cv::LUT(rgb[2], lut, rgb[2]);
		cv::merge(rgb, out_image);
	}
	catch (std::exception const& e)
	{
	  spdlog::error(e.what());
		throw;
	}
}
