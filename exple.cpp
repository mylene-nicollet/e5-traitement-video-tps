/*============================================================================*/
/* File Description                                                           */
/*============================================================================*/
/**
 * @file        load_display.cpp
 * @author      P. FOUBERT
 * @brief       OpenCV project to show how to load and display an image
 */
/*============================================================================*/

/*============================================================================*/
/* Includes                                                                   */
/*============================================================================*/
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "opencv2/opencv.hpp"

/*============================================================================*/
/* Defines                                                                    */
/*============================================================================*/

/*============================================================================*/
/* Local Constants                                                            */
/*============================================================================*/

/*============================================================================*/
/* Local Types                                                                */
/*============================================================================*/

/*============================================================================*/
/* Static Variables                                                           */
/*============================================================================*/

/*============================================================================*/
/* Static Functions Prototype                                                 */
/*============================================================================*/

/******************************************************************************/
/* Public Functions                                                           */
/******************************************************************************/
void rotateImage(const cv::Mat &i_src, double angle, cv::Mat &dest){
  cv::Point2f pt(static_cast<float>(i_src.cols) / 2,static_cast<float>(i_src.rows) / 2);
  cv::Mat rot = cv::getRotationMatrix2D(pt, angle, 1.0);

  cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), i_src.size(), angle).boundingRect2f();
  // adjust transformation matrix
  rot.at<double>(0,2) += bbox.width/2.0 - i_src.cols/2.0;
  rot.at<double>(1,2) += bbox.height/2.0 - i_src.rows/2.0;

  cv::warpAffine(i_src, dest, rot, bbox.size());

}

/*============================================================================*/
/* Function Description                                                       */
/*============================================================================*/
/**
 * @brief         Main
 * @param[in]     argc        : Number of arguments
 * @param[in]     argv        : Arguments list
 * @return        <0 if error, 0 if success, >0 if warning
 */
/*============================================================================*/
int main(int argc, char** argv)
{
  int res(0);
  char* filename = argv[1];
  //const char filename[] = "smarties.jpg";

  cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR/*IMREAD_GRAYSCALE*/);
  if(img.empty())
  {
    std::cout << "Cannot load image!" << std::endl;
    res = -1;
  }
  else
  {
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::Mat dest;
    char key;
    double angle = 0;
    double light = 0;
    double contrast = 1;
    while((key = cv::waitKey(0)) != 'q'){  //quit
      if('l' == key){  //left
        angle += 15;
      }
      if('r' == key){  //right
        angle -= 15;
      }
      if('s' == key){  //save
        cv::imwrite("saved_image.png", dest);
      }
      if('w' == key){  //white pour light
        light += 50;
      }
      if('b' == key){  //black pour dark
        light -= 50;
      }
      if('c' == key){  //color pour + de contrast
        contrast += 0.5;
      }
      if('f' == key){  //fade pour - de contrast
        contrast -= 0.5;
      }
      img.convertTo(dest, -1, contrast, light);
      rotateImage(dest, angle, dest);
      cv::imshow("image", dest);
    }
  }
  return res;
}