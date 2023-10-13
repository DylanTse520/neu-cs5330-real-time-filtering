/*  Yixiang Xie
    Fall 2023
    CS 5330
*/

#include <opencv2/opencv.hpp>
#include "util.hpp"

std::string getFileName(char *foldername)
{
  // get the current time
  time_t rawtime;
  time(&rawtime);

  // convert the time to local time
  struct tm *timeinfo;
  timeinfo = localtime(&rawtime);

  // store current time
  char currentTime[256];
  strftime(currentTime, sizeof(currentTime), "%Y-%m-%d_%H-%M-%S", timeinfo);

  // create the filename
  std::string filename = std::string(foldername) + currentTime;
  return (filename);
}