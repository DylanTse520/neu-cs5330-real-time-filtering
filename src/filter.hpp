/*  Yixiang Xie
    Fall 2023
    CS 5330
*/

int grayscale_red_channel(const cv::Mat &src, cv::Mat &dst);
int grayscale_blue_channel(const cv::Mat &src, cv::Mat &dst);
int grayscale_green_channel(const cv::Mat &src, cv::Mat &dst);
int grayscale_avg(const cv::Mat &src, cv::Mat &dst);
int grayscale_hsv(const cv::Mat &src, cv::Mat &dst);
int grayscale_lab(const cv::Mat &src, cv::Mat &dst);
int blur5x5(const cv::Mat &src, cv::Mat &dst);
int sobelX3x3(const cv::Mat &src, cv::Mat &dst);
int sobelY3x3(const cv::Mat &src, cv::Mat &dst);
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels = 15 );
int cartoon( cv::Mat &src, cv::Mat&dst, int levels = 15, int magThreshold = 15 );