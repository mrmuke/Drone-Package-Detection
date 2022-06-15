
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;
Mat img;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if(event == EVENT_LBUTTONDOWN ){
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        Vec3b rgb=img.at<Vec3b>(y,x);
        string res = "H: "+to_string(rgb.val[0])+", S:"+to_string(rgb.val[1])+", V:"+to_string(rgb.val[2]);
        cout << res <<endl;
    }
}

int main()
{
    img = imread("img.jpg");
     //Create a window
     namedWindow("hsv");

     //set the callback function for any mouse event
     setMouseCallback("hsv", CallBackFunc, NULL);

     //show the image
     imshow("hsv", img);
    waitKey(0);
    return 0;

}