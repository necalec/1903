#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap("video.mp4");

    if (!cap.isOpened())
    {
        cerr << "eror" << endl;
        return -1;
    }

    namedWindow("1", WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        Mat lab;
        cvtColor(frame, lab, COLOR_BGR2Lab);

        vector<Mat> lab_channels;
        split(lab, lab_channels);

        Mat binary;
        threshold(lab_channels[0], binary, 170, 255, THRESH_BINARY);

        vector<vector<Point>> contours;
        findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours)
        {
            Rect bounding_Rect = boundingRect(contour);

            if (bounding_Rect.width > 50 && bounding_Rect.height > 50)
            {
                rectangle(frame, bounding_Rect, Scalar(0, 255, 0), 2);
                break;
            }
        }

        imshow("1", frame);

        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    destroyAllWindows();

    return 0;
}
