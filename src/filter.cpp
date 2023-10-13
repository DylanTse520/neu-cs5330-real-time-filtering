/*  Yixiang Xie
    Fall 2023
    CS 5330
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.hpp"

/*
  function that calculates the grayscale of an image from the red channel
  src is the input image
  dst is the output image, allocated by the function
*/
int grayscale_red_channel(const cv::Mat &src, cv::Mat &dst)
{
  // allocate the dst image
  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // assign dst image with the red channel
  for (int i = 0; i < src.rows; i++)
  {
    // access the dst image with pointer
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

    // access the src image through row pointers
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i); // get the pointer to the start row i

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = rptr[j][2]; // red channel
      }
    }
  }

  return (0);
}

/*
  function that calculates the grayscale of an image from the blue channel
*/
int grayscale_blue_channel(const cv::Mat &src, cv::Mat &dst)
{
  dst = cv::Mat::zeros(src.size(), CV_8UC3);
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = rptr[j][0]; // blue channel
      }
    }
  }

  return (0);
}

/*
  function that calculates the grayscale of an image from the green channel
*/
int grayscale_green_channel(const cv::Mat &src, cv::Mat &dst)
{
  dst = cv::Mat::zeros(src.size(), CV_8UC3);
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = rptr[j][1]; // green channel
      }
    }
  }

  return (0);
}

/*
  function that calculates the grayscale of an image from the avg of three channels
*/
int grayscale_avg(const cv::Mat &src, cv::Mat &dst)
{
  dst = cv::Mat::zeros(src.size(), CV_8UC3);
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = std::round((rptr[j][0] + rptr[j][1] + rptr[j][2]) / 3); // avg of three channels
      }
    }
  }

  return (0);
}

/*
  function that calculates the grayscale of an image by converting to HSV and taking the value channel
*/
int grayscale_hsv(const cv::Mat &src, cv::Mat &dst)
{
  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // convert to HSV
  cv::Mat hsv;
  cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = hsv.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = rptr[j][2]; // value channel
      }
    }
  }
  return (0);
}

/*
  function that calculates the grayscale of an image by converting to Lab and taking the L channel
*/
int grayscale_lab(const cv::Mat &src, cv::Mat &dst)
{
  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // convert to Lab
  cv::Mat lab;
  cv::cvtColor(src, lab, cv::COLOR_BGR2Lab);

  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = lab.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = rptr[j][0]; // L channel
      }
    }
  }
  return (0);
}

/*
  function that calculates the 5x5 Gaussian blur of an image
*/
int blur5x5(const cv::Mat &src, cv::Mat &dst)
{
  // the intermediate image
  cv::Mat itm = cv::Mat::zeros(src.size(), CV_8UC3);

  // calculate itm image
  for (int i = 0; i < src.rows; i++)
  {
    // access the itm image with pointer
    cv::Vec3b *iptr = itm.ptr<cv::Vec3b>(i);

    // access the src image through row pointers
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

    // multiply [1 2 4 2 1] horizontal kernel with the image, ignoring the outer most two cols
    for (int j = 2; j < src.cols - 2; j++)
    {
      // calculate the weighted average of the 5 pixels
      for (int c = 0; c < 3; c++)
      {
        iptr[j][c] = (rptr[j - 2][c] + rptr[j - 1][c] * 2 + rptr[j][c] * 4 + rptr[j + 1][c] * 2 + rptr[j + 2][c]) / 10;
      }
    }
    // assign the outer most two cols
    for (int j = 0; j < 3; j++)
    {
      iptr[0][j] = iptr[2][j];
      iptr[1][j] = iptr[2][j];
      iptr[src.cols - 1][j] = iptr[src.cols - 3][j];
      iptr[src.cols - 2][j] = iptr[src.cols - 3][j];
    }
  }

  // allocate the dst image
  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // assign dst image, ignoring the outer most two rows
  for (int i = 2; i < src.rows - 2; i++)
  {
    // access the dst image with pointer
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

    // 5 row points (from two rows above to two rows below)
    const cv::Vec3b *rptrm2 = itm.ptr<cv::Vec3b>(i - 2);
    const cv::Vec3b *rptrm1 = itm.ptr<cv::Vec3b>(i - 1);
    const cv::Vec3b *rptr = itm.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptrp1 = itm.ptr<cv::Vec3b>(i + 1);
    const cv::Vec3b *rptrp2 = itm.ptr<cv::Vec3b>(i + 2);

    // multiply [1 2 4 2 1] vertical kernel with the image
    for (int j = 0; j < src.cols; j++)
    {

      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = (rptrm2[j][c] + rptrm1[j][c] * 2 + rptr[j][c] * 4 + rptrp1[j][c] * 2 + rptrp2[j][c]) / 10;
      }
    }
  }

  // assign the outer most two rows
  cv::Vec3b *dptrp0 = dst.ptr<cv::Vec3b>(0);
  cv::Vec3b *dptrp1 = dst.ptr<cv::Vec3b>(1);
  cv::Vec3b *dptrp2 = dst.ptr<cv::Vec3b>(2);
  cv::Vec3b *dptrm1 = dst.ptr<cv::Vec3b>(src.rows - 1);
  cv::Vec3b *dptrm2 = dst.ptr<cv::Vec3b>(src.rows - 2);
  cv::Vec3b *dptrm3 = dst.ptr<cv::Vec3b>(src.rows - 3);

  for (int i = 0; i < src.cols; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      dptrp0[i][j] = dptrp2[i][j];
      dptrp1[i][j] = dptrp2[i][j];
      dptrm1[i][j] = dptrm3[i][j];
      dptrm2[i][j] = dptrm3[i][j];
    }
  }

  return (0);
}

/*
  function that calculates the horizontal Sobel gradient of an image
*/
int sobelX3x3(const cv::Mat &src, cv::Mat &dst)
{
  // the intermediate image
  cv::Mat itm = cv::Mat::zeros(src.size(), CV_16SC3);

  // calculate itm image
  for (int i = 1; i < src.rows - 1; i++)
  {
    cv::Vec3s *iptr = itm.ptr<cv::Vec3s>(i);

    // 3 row points (above, middle, below)
    const cv::Vec3b *rptrm1 = src.ptr<cv::Vec3b>(i - 1);
    const cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptrp1 = src.ptr<cv::Vec3b>(i + 1);

    // multiply [1 2 1] vertical kernel with the image
    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        iptr[j][c] = (rptrm1[j][c] + rptr[j][c] * 2 + rptrp1[j][c]) / 4;
      }
    }
  }

  dst = cv::Mat::zeros(src.size(), CV_16SC3);
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);

    const cv::Vec3s *rptr = itm.ptr<cv::Vec3s>(i);

    // multiply [-1 0 1] horizontal kernel with the image
    for (int j = 1; j < src.cols - 1; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = (-1 * rptr[j - 1][c] + rptr[j + 1][c]) / 2;
      }
    }
  }
  return (0);
}

/*
  function that calculates the vertical Sobel gradient of an image
*/
int sobelY3x3(const cv::Mat &src, cv::Mat &dst)
{
  // the intermediate image
  cv::Mat itm = cv::Mat::zeros(src.size(), CV_16UC3);

  // calculate itm image
  for (int i = 1; i < src.rows - 1; i++)
  {
    cv::Vec3s *iptr = itm.ptr<cv::Vec3s>(i);

    // 2 row pointers (above and below)
    const cv::Vec3b *rptrm1 = src.ptr<cv::Vec3b>(i - 1);
    const cv::Vec3b *rptrp1 = src.ptr<cv::Vec3b>(i + 1);

    // multiply [1 0 -1] vertical kernel with the image
    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        iptr[j][c] = (rptrm1[j][c] - rptrp1[j][c]) / 2;
      }
    }
  }

  dst = cv::Mat::zeros(src.size(), CV_16SC3);
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);

    const cv::Vec3s *rptr = itm.ptr<cv::Vec3s>(i);

    // multiply [1 2 1] horizontal kernel with the image
    for (int j = 1; j < src.cols - 1; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = (rptr[j - 1][c] + 2 * rptr[j][c] + rptr[j + 1][c]) / 4;
      }
    }
  }
  return (0);
}

/*
  function that calculates the gradient magnitude of an image
  sx is the input Sobel X image
  sy is the input Sobel Y image
  dst is the output image, allocated by the function
*/
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst)
{
  dst = cv::Mat::zeros(sx.size(), CV_8UC3);
  for (int i = 0; i < sx.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

    const cv::Vec3s *sxptr = sx.ptr<cv::Vec3s>(i);
    const cv::Vec3s *syptr = sy.ptr<cv::Vec3s>(i);

    for (int j = 0; j < sx.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = sqrt(sxptr[j][c] * sxptr[j][c] + syptr[j][c] * syptr[j][c]);
      }
    }
  }
  return (0);
}

/*
  function that blurs and quantizes a color image
*/
int blurQuantize(cv::Mat &src, cv::Mat &dst, int levels)
{
  // generate the blurred image
  cv::Mat blur;
  blur5x5(src, blur);

  // generate the quantization table
  int step = 255 / levels;
  int *qtable = new int[256];
  for (int i = 0; i < 256; i++)
  {
    qtable[i] = (i / step) * step;
  }

  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // quantize the image
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    const cv::Vec3b *rptr = blur.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        dptr[j][c] = qtable[rptr[j][c]];
      }
    }
  }

  return (0);
}

/*
  function that cartoonizes a color image
*/
int cartoon(cv::Mat &src, cv::Mat &dst, int levels, int magThreshold)
{
  // generate the gradient magnitude
  cv::Mat sobelx;
  sobelX3x3(src, sobelx);
  cv::Mat sobely;
  sobelY3x3(src, sobely);
  cv::Mat mag;
  magnitude(sobelx, sobely, mag);

  // generate the blurred and quantized image
  cv::Mat quantize;
  blurQuantize(src, quantize, levels);

  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // apply the threshold
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    cv::Vec3b *mptr = mag.ptr<cv::Vec3b>(i);
    cv::Vec3b *qptr = quantize.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        // only copy the quantized image if the magnitude is lower than the threshold
        if (mptr[j][c] <= magThreshold)
        {
          dptr[j][c] = qptr[j][c];
        }
      }
    }
  }

  return (0);
}
