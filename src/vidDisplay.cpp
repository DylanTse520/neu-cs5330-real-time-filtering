/*  Yixiang Xie
    Fall 2023
    CS 5330
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "util.hpp"
#include "filter.hpp"

int main(int argc, char *argv[])
{
  // char array to hold the image saving folder
  char foldername[256];

  // check if foldername was passed in
  if (argc < 2)
  {
    printf("Error: %s needs more than one argument\n", argv[0]);
    return (-1);
  }

  // copy the foldername
  strcpy(foldername, argv[1]);

  // allocate a video capture object
  cv::VideoCapture *capdev;

  // open the video device
  capdev = new cv::VideoCapture(0);

  // check if the video device was opened
  if (!capdev->isOpened())
  {
    printf("Error: unable to open video device\n");
    return (-1);
  }

  // get the width and height of frames in the video stream
  cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
  printf("Expected size: %d %d\n", refS.width, refS.height);

  // create a window
  cv::namedWindow("vid", 1);

  // allocate the frame buffer objects
  cv::Mat original;

  // store the adjustments and filter name
  int brightnessAdjustment = 0;
  double contrastAdjustment = 1.0;
  std::string filter = "original";

  // program enters a loop to display video and check for keypress
  while (true)
  {
    // read a frame from the video stream
    *capdev >> original;

    // check if the video stream was read
    if (original.empty())
    {
      printf("Error: frame is empty\n");
      break;
    }

    // adjust the brightness and contrast
    original.convertTo(original, -1, contrastAdjustment, brightnessAdjustment);
    original += cv::Scalar(brightnessAdjustment, brightnessAdjustment, brightnessAdjustment);
    original *= contrastAdjustment;
    cv::normalize(original, original, 0, 255, cv::NORM_MINMAX);
    original.convertTo(original, CV_8UC3);

    cv::Mat processed;

    if (filter == "original")
    {
      processed = cv::Mat::zeros(original.size(), original.type());
      original.copyTo(processed);
    }
    else if (filter == "grayscale_cvt_color")
    {
      cv::cvtColor(original, processed, cv::COLOR_BGR2GRAY);
    }
    else if (filter == "grayscale_red_channel")
    {
      grayscale_red_channel(original, processed);
    }
    else if (filter == "grayscale_blue_channel")
    {
      grayscale_blue_channel(original, processed);
    }
    else if (filter == "grayscale_green_channel")
    {
      grayscale_green_channel(original, processed);
    }
    else if (filter == "grayscale_avg")
    {
      grayscale_avg(original, processed);
    }
    else if (filter == "grayscale_hsv")
    {
      grayscale_hsv(original, processed);
    }
    else if (filter == "grayscale_lab")
    {
      grayscale_lab(original, processed);
    }
    else if (filter == "blur")
    {
      blur5x5(original, processed);
    }
    else if (filter == "sobelx")
    {
      cv::Mat sobelx;
      sobelX3x3(original, sobelx);
      cv::convertScaleAbs(sobelx, processed);
    }
    else if (filter == "sobely")
    {
      cv::Mat sobely;
      sobelY3x3(original, sobely);
      cv::convertScaleAbs(sobely, processed);
    }
    else if (filter == "magnitude")
    {
      cv::Mat sobelx;
      sobelX3x3(original, sobelx);
      cv::Mat sobely;
      sobelY3x3(original, sobely);
      magnitude(sobelx, sobely, processed);
    }
    else if (filter == "quantize")
    {
      blurQuantize(original, processed, 6);
    }
    else if (filter == "cartoon")
    {
      cartoon(original, processed, 6, 15);
    }

    // display the frame
    cv::imshow("vid", processed);

    // wait for a keypress
    int key = cv::waitKey(1);
    // if key is 'q', exit the loop and quit the program
    if (key == 'q')
    {
      // destroy the window
      cv::destroyWindow("vid");
      break;
    }
    // if key is 's', save the frame to a file
    else if (key == 's')
    {
      // get filename and save the image
      std::string filename = getFileName(foldername);
      cv::imwrite(filename + "_original.jpg", original);
      if (filter != "original")
      {
        cv::imwrite(filename + "_" + filter + ".jpg", processed);
      }
    }
    // if key is 'o', show the original image
    else if (key == 'o')
    {
      filter = "original";
    }
    // if key is 'g', show the grayscale image
    else if (key == 'g')
    {
      filter = "grayscale_cvt_color";
    }
    // if key is 'h', show the alternative grayscale image, which is the average of three channels
    else if (key == 'h')
    {
      filter = "grayscale_avg";
    }
    // if key is '1', show the red channel grayscale image
    else if (key == '1')
    {
      filter = "grayscale_red_channel";
    }
    // if key is '2', show the blue channel grayscale image
    else if (key == '2')
    {
      filter = "grayscale_blue_channel";
    }
    // if key is '3', show the green channel grayscale image
    else if (key == '3')
    {
      filter = "grayscale_green_channel";
    }
    // if key is '4', show the grayscale image with three channels averaged
    else if (key == '4')
    {
      filter = "grayscale_avg";
    }
    // if key is '5', show the value channel grayscale image
    else if (key == '5')
    {
      filter = "grayscale_hsv";
    }
    // if key is '6', show the L channel grayscale image
    else if (key == '6')
    {
      filter = "grayscale_lab";
    }
    // if key is 'b', show the 5x5 Gaussian blurred image
    else if (key == 'b')
    {
      filter = "blur";
    }
    // if key is 'x', show the 3x3 Sobel X filtered image
    else if (key == 'x')
    {
      filter = "sobelx";
    }
    // if key is 'y', show the 3x3 Sobel Y filtered image
    else if (key == 'y')
    {
      filter = "sobely";
    }
    // if key is 'm', show the gradient magnitude image from X and Y Sobel image
    else if (key == 'm')
    {
      filter = "magnitude";
    }
    // if key is 'l', show the blurred and quantized image of a color image
    else if (key == 'l')
    {
      filter = "quantize";
    }
    // if key is 'c', show the cartoonized image
    else if (key == 'c')
    {
      filter = "cartoon";
    }
    // if key is 'up', increase the brightness on the video stream
    else if (key == 0)
    {
      // increase the brightness by 10
      brightnessAdjustment += 10;
    }
    // if key is 'down', decrease the brightness on the video stream
    else if (key == 1)
    {
      // decrease the brightness by 10
      brightnessAdjustment -= 10;
    }
    // if key is 'right', increase the contrast on the video stream
    else if (key == 3)
    {
      // increase the contrast by 0.1
      contrastAdjustment += 0.1;
    }
    // if key is 'left', decrease the contrast on the video stream
    else if (key == 2)
    {
      // decrease the contrast by 0.1
      contrastAdjustment -= 0.1;
      if (contrastAdjustment < 0.1)
      {
        contrastAdjustment = 0.1;
      }
    }
  }

  // free the video capture object
  delete capdev;
  return (0);
}