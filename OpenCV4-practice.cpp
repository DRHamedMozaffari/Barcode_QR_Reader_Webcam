#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <zbar.h>


int main(int argc, char** argv)
{
	zbar::ImageScanner scanner;

	// scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
	// scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

	cv::VideoCapture capture;
	capture.open(0);  //Turn on the camera

	std::vector<cv::Point2f> obj_location;
	bool flag = true;
	
	if (!capture.isOpened())
	{
		std::cout << "cannot open cam!" << std::endl;
	}
	else
	{
		while (flag)
		{
			cv::Mat image;
			cv::Mat imageGray;
			capture >> image;
			cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

			int width = imageGray.cols;
			int height = imageGray.rows;
			int delay = 30;

			uchar* raw = (uchar*)imageGray.data;

			zbar::Image imageZbar(width, height, "Y800", raw, width * height);

			scanner.scan(imageZbar);  //Scan Barcode
			zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
			if (imageZbar.symbol_begin() != imageZbar.symbol_end())  //If Scan to QR Code
			{
				delay = 0;
				//Resolve 2D Code
				for (int i = 0; i < symbol->get_location_size(); i++)
				{
					obj_location.push_back(cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
				}
				for (int i = 0; i < obj_location.size(); i++)
				{
					cv::line(image, obj_location[i], obj_location[(i + 1) % obj_location.size()], cv::Scalar(255, 0, 0), 3);//Locate Barcode
				}
				for (; symbol != imageZbar.symbol_end(); ++symbol)
				{
					std::cout << "Code Type: " << std::endl << symbol->get_type_name() << std::endl; //Get Barcode Type
					std::cout << "Decode Result: " << std::endl << symbol->get_data() << std::endl;  //Decode
				}
				imageZbar.set_data(NULL, 0);
			}
			cv::imshow("Result", image);

			int key = cv::waitKey(delay);
			if (key == 27) {
				flag = false;
				break;
			}
			if (key == 127) {
				delay = 30;
				image.release();
				cv::destroyAllWindows();
			}
		}
		cv::destroyAllWindows();
	}
	return 0;
}

