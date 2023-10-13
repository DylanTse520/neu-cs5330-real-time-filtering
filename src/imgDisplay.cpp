/*  Yixiang Xie
    Fall 2023
    CS 5330
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
  // char array to hold the filename
  char filename[256];

  // check if filename was passed in
  if (argc < 2)
  {
    printf("Error: %s needs more than one argument\n", argv[0]);
    return (-1);
  }

  // copy the filename
  strcpy(filename, argv[1]);

  // allocate an empty cv::Mat to hold the image
  cv::Mat src;

  // read the image data from filename
  src = cv::imread(filename);

  // check if the image was read
  // if the image wasn't read, src.data will be NULL
  if (src.data == NULL)
  {
    printf("Error: unable to read image %s\n", filename);
    return (-2);
  }

  // create a window
  cv::namedWindow("img", 1);
  // display the read image
  cv::imshow("img", src);

  // program enters a loop, checking for a keypress
  // if user types 'q', the program exits
  while (true)
  {
    int key = cv::waitKey(0);
    if (key == 'q')
    {
      // destroy the window
      cv::destroyWindow("img");
      break;
    }
  }

  return (0);
}