#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh =135 , max_thresh = 255;


/// Function header
void thresh_callback(int, void* );

/**@function main*/
int main( int argc, char** argv )
{
    /// Load source image
    CommandLineParser parser( argc, argv, "{@input | ../data/HappyFish.jpg | input image}" );
    Mat src = imread( parser.get<String>( "@input" ) );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

    /// Convert image to gray 
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    

    /// Create Window
    const char* source_window = "Source";
    
    namedWindow( source_window );
    imshow( source_window, src);

    thresh_callback(0,0);


    waitKey();
    return 0;
}

/**@function thresh_callback*/
void thresh_callback(int, void* )
{
    /// Convert image binary
    Mat scr_binary;
    threshold( src_gray, scr_binary, thresh, max_thresh, THRESH_BINARY );
    const char* window = "binary image";
    namedWindow( window );
    imshow( window, scr_binary);

    /// Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( scr_binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

    /// Draw contours
    Mat drawing = Mat::zeros( scr_binary.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( 265, 265, 265 );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    /// Show in a window

    imshow( "Contours", drawing );
    imwrite("../contours/contour.jpg",drawing);
}
