#include <opencv2/opencv.hpp>

using namespace cv;

using namespace std;

int main()
{

    Mat image;

    namedWindow("Display window");

    VideoCapture cap(0);

    if (!cap.isOpened())
    {

        cout << "cannot open camera";
    }
    while (true)
    {
        Mat frame, frame_HSV, frame_threshold, output;

        cap >> frame;
        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
        inRange(frame_HSV, Scalar(16, 118, 191), Scalar(70, 214, 255), frame_threshold);
        bitwise_and(frame, frame, output, frame_threshold);

        Mat channels[3];
        split(output,channels);
        vector<vector<Point>> contours; // Vector for storing contours
        int largest_area = 0;
        Rect bounding_rect;
        
        Mat gray =channels[2];
        findContours(gray, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) 
        {
            double area = contourArea(contours[i]); 

            if (area > largest_area)
            {
                largest_area = area;             
                bounding_rect = boundingRect(contours[i]); 
            }
        }
        Point pt1, pt2;
        pt1.x = bounding_rect.x;
        pt1.y = bounding_rect.y;
        pt2.x = bounding_rect.x + bounding_rect.width;
        pt2.y = bounding_rect.y + bounding_rect.height; 
        Point center;
        center.x= bounding_rect.x+bounding_rect.width/2;
        center.y=bounding_rect.y+bounding_rect.height/2;
        //DRAW CROSSHAIR AT CENTER POINT       
        rectangle(output, pt1, pt2, CV_RGB(0,255,0), 1);

        drawMarker(output, center,  CV_RGB(0, 255, 0), MARKER_CROSS, 10, 1);

        imshow("Display window", output);
        waitKey(0);
    }

    return 0;
}