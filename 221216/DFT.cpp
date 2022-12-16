#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void log_mag(Mat complex_mat, Mat& dst){

	Mat	planes[2];
	split(complex_mat, planes);
	magnitude(planes[0], planes[1], dst);
	log(dst+1, dst);
	normalize(dst, dst,0, 255, CV_MINMAX);
	dst.convertTo(dst, CV_8U);

}

void shuffling(Mat mag_img, Mat& dst)
{
	int cx = mag_img.cols/2;
	int cy = mag_img.rows/2;
	Rect q1(cx, 0, cx, cy);
	Rect q2(0, 0, cx, cy);
	Rect q3(0, cy, cx, cy);
	Rect q4(cx, cy, cx, cy);

	dst = Mat(mag_img.size(), mag_img.type());
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));

}

Mat DFT_1D(Mat one_row, int dir)
{
	int N = one_row.cols;
	Mat dst(one_row.size(), CV_32FC2);

	for(int k=0; k<N; k++){
		Vec2f complex(0,0);
		for(int n=0; n<N; n++)
		{
			float theta = dir*-2*CV_PI*k*n/N;
			Vec2f value = one_row.at<Vec2f>(n);
			complex[0] += value[0]*cos(theta)-value[1]*sin(theta);
			complex[1] += value[1]*cos(theta)+value[0]*sin(theta);

		}
		dst.at<Vec2f>(k) = complex;
	}
	if(dir == -1)	dst /= N;
	return dst;
}


void DFT_2D(Mat complex_img, Mat& dst, int dir)
{
	complex_img.convertTo(complex_img, CV_32F);
	Mat tmp(complex_img.size(), CV_32FC2, Vec2f(0,0));
	tmp.copyTo(dst);

	for(int i=0; i<complex_img.rows; i++){
		Mat one_row = complex_img.row(i);
		Mat dft_row = DFT_1D(one_row, dir);
		dft_row.copyTo(tmp.row(i));


	}

	transpose(tmp, tmp);
	for(int i=0; i<tmp.rows; i++){
		Mat one_row = tmp.row(i);
		Mat dft_row = DFT_1D(tmp.row(i), dir);
		dft_row.copyTo(dst.row(i));

	}
	transpose(dst, dst);

}



int main()
{
	Mat image = imread("../Image/lena.bmp",0);
	CV_Assert(image.data);

	Mat complex_img, dft_coef, dft_img, idft_coef, shuffling_img, idft_img[2];
	Mat	tmp[] = { image, Mat::zeros(image.size(), CV_8U)};
	merge(tmp, 2, complex_img);

	DFT_2D(complex_img, dft_coef, 1);
	log_mag(dft_coef, dft_img);
	shuffling(dft_img, shuffling_img);

	DFT_2D(dft_coef, idft_coef, -1);
	split(idft_coef, idft_img);
	idft_img[0].convertTo(idft_img[0], CV_8U);

	imshow("image", image);
	imshow("dft_img", dft_img);
	imshow("shuffling_img", shuffling_img);
	imshow("idft_img", idft_img[0]);
	waitKey();
	return 0;
}
