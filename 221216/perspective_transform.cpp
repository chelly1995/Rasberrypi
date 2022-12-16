#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../Image/lena.bmp",IMREAD_COLOR);
	CV_Assert(image.data);

	Point2f pts1[4] = {

		Point2f(90, 170), Point2f(300,120),
		Point2f(90, 285), Point2f(300,320)

	};

	Point2f pts2[4]




}
