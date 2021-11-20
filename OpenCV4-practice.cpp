#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image = imread("./image.png");

    // check for failure
    if (image.empty())
    {
        cout << "could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    String windowName = "The Guitar"; //Name of the window

    namedWindow(windowName); // Create a window

    imshow(windowName, image); // Show our image inside the created window.

    waitKey(0); // Wait for any keystroke in the window

    destroyWindow(windowName); //destroy the created window

    return 0;
}
