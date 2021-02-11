#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream> 

int main()
{
    constexpr int device_id = 0; 
    cv::VideoCapture input_stream(device_id); 

    if (!input_stream.isOpened())
    {
        std::cerr << "Could not open camera\n"; 
        return EXIT_FAILURE; 
    }

    const std::string window_title = "Lab 0: Introduction to C++ and OpenCV"; 
    cv::namedWindow(window_title, cv::WINDOW_GUI_NORMAL); 

    cv::Mat frame, prev_frame, blurred, canny, difference; 

    while (true)
    {
        if (!frame.empty())
        {
            prev_frame = frame; 
        }

        input_stream >> frame; 

        if (frame.empty())
        {
            std::cerr << "The camera returned an empty frame. Is the camera ok?\n"; 
            break; 
        }

        cv::blur(frame, blurred, cv::Size(5, 5)); 
        cv::Canny(frame, canny, 50, 150);
        
        difference = frame - prev_frame; 

        cv::imshow(window_title, canny); 

        constexpr int delay_ms = 15; 
        if (cv::waitKey(delay_ms) >= 0)
            break; 
    }

    return EXIT_SUCCESS; 
}
