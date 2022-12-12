#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat m1(4,3,CV_32SC3);
	cout << "demansion quantity = " << m1.dims << endl;
	cout << "row number = " << m1.rows << endl;
	cout << "colomn number = " << m1.cols << endl;
	cout << "rows and coloumn size = " << m1.size() << endl << endl;

	cout << "all element num = " << m1.total() << endl;
	cout << " one element size = " << m1.elemSize() << endl;
	cout << " one element size per channel = " << m1.elemSize1() << endl << endl;

	cout << "type = " << m1.type() << endl;
	cout << "type (depth of channels num) = " << ((m1.channels() -1)<<3)+m1.depth()<< endl;
	cout << "depth = " << m1.depth() << endl;
	cout << "channel = " << m1.channels() << endl << endl;

	cout << "step = " << m1.step << endl;
	cout << "step1() = " << m1.step1() << endl;
	return 0;

}
