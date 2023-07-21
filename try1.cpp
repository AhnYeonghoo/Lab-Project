#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat img, templ, mask, result, result_mini, templ_mini, templ_mini2, result_mini2, templ_mini3, result_mini3, templ_mini4, result_mini4;
int match_method;
bool use_mask;

void matchingMethod(int, void*);

int main()
{
	img = imread("./data/all4.jpg", IMREAD_GRAYSCALE);
	templ = imread("./data/template_big.jpg", IMREAD_GRAYSCALE);
	templ_mini = imread("./data/template_mini.jpg", IMREAD_GRAYSCALE);
	templ_mini2 = imread("./data/template_mini2.jpg", IMREAD_GRAYSCALE);
	templ_mini3 = imread("./data/template_mini3.jpg", IMREAD_GRAYSCALE);
	templ_mini4 = imread("./data/template_mini4.jpg", IMREAD_GRAYSCALE);

	/*resize(templ, templ, Size(669, 565));*/
	if (img.empty() || templ.empty())
	{
		cerr << "Image load failed" << endl;
		return -1;
	}

	namedWindow("Source Image", WINDOW_AUTOSIZE);


	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, "Source Image", &match_method, 5, matchingMethod);

	matchingMethod(0, 0);

	return 0;

}

void matchingMethod(int, void*)
{
	Mat img_display, img_display_mini, img_display_mini2, img_display_mini3, img_display_mini4;
	img.copyTo(img_display);
	img.copyTo(img_display_mini);
	img.copyTo(img_display_mini2);
	img.copyTo(img_display_mini3);
	img.copyTo(img_display_mini4);

	cvtColor(img_display, img_display, COLOR_GRAY2BGR);
	cvtColor(img_display_mini, img_display_mini, COLOR_GRAY2BGR);
	cvtColor(img_display_mini2, img_display_mini2, COLOR_GRAY2BGR);
	cvtColor(img_display_mini3, img_display_mini3, COLOR_GRAY2BGR);
	cvtColor(img_display_mini4, img_display_mini4, COLOR_GRAY2BGR);

	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	int result_cols_mini = img.cols - templ_mini.cols + 1;
	int result_rows_mini = img.rows - templ_mini.rows + 1;
	int result_cols_mini2 = img.cols - templ_mini2.cols + 1;
	int result_rows_mini2 = img.rows - templ_mini2.rows + 1;
	int result_cols_mini3 = img.cols - templ_mini3.cols + 1;
	int result_rows_mini3 = img.rows - templ_mini3.rows + 1;
	int result_cols_mini4 = img.cols - templ_mini4.cols + 1;
	int result_rows_mini4 = img.rows - templ_mini4.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);
	result_mini.create(result_rows_mini, result_cols_mini, CV_32FC1);
	result_mini2.create(result_rows_mini2, result_cols_mini2, CV_32FC1);
	result_mini3.create(result_rows_mini3, result_cols_mini3, CV_32FC1);
	result_mini4.create(result_rows_mini4, result_cols_mini4, CV_32FC1);

	matchTemplate(img, templ, result, match_method);
	matchTemplate(img, templ_mini, result_mini, match_method);
	matchTemplate(img, templ_mini2, result_mini2, match_method);
	matchTemplate(img, templ_mini3, result_mini3, match_method);
	matchTemplate(img, templ_mini4, result_mini4, match_method);

	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(result_mini, result_mini, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(result_mini2, result_mini2, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(result_mini3, result_mini3, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(result_mini4, result_mini4, 0, 1, NORM_MINMAX, -1, Mat());




	double min_val, max_val;
	Point min_loc, max_loc;
	Point match_loc;
	double threshold = 0.158;

	minMaxLoc(result, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			if (result.at<float>(i, j) < threshold)
			{
				rectangle(img_display, Point(j, i), Point(j + templ.cols, i + templ.rows),
					Scalar(0, 0, 255), 1);
			}
		}
	}

	minMaxLoc(result_mini, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result_mini.rows; i++)
	{
		for (int j = 0; j < result_mini.cols; j++)
		{
			if (result_mini.at<float>(i, j) < threshold)
			{
				rectangle(img_display_mini, Point(j, i), Point(j + templ_mini.cols, i + templ_mini.rows),
					Scalar(0, 255, 0), 1);
		
			}
		}
	}

	minMaxLoc(result_mini2, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result_mini2.rows; i++)
	{
		for (int j = 0; j < result_mini2.cols; j++)
		{
			if (result_mini2.at<float>(i, j) < threshold)
			{
				rectangle(img_display_mini2, Point(j, i), Point(j + templ_mini2.cols, i + templ_mini2.rows),
					Scalar(0, 255, 0), 1);

			}
		}
	}

	minMaxLoc(result_mini3, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result_mini3.rows; i++)
	{
		for (int j = 0; j < result_mini3.cols; j++)
		{
			if (result_mini3.at<float>(i, j) < threshold)
			{
				rectangle(img_display_mini2, Point(j, i), Point(j + templ_mini3.cols, i + templ_mini3.rows),
					Scalar(0, 255, 0), 1);

			}
		}
	}

	minMaxLoc(result_mini4, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result_mini4.rows; i++)
	{
		for (int j = 0; j < result_mini4.cols; j++)
		{
			if (result_mini4.at<float>(i, j) < threshold)
			{
				rectangle(img_display_mini4, Point(j, i), Point(j + templ_mini4.cols, i + templ_mini4.rows),
					Scalar(0, 255, 0), 1);

			}
		}
	}



	resize(img_display, img_display, Size(555, 555), 0.3, 0.3, INTER_AREA);
	resize(img_display_mini, img_display_mini, Size(555, 555), 0.3, 0.3, INTER_AREA);
	resize(img_display_mini2, img_display_mini2, Size(555, 555), 0.3, 0.3, INTER_AREA);
	resize(img_display_mini3, img_display_mini3, Size(555, 555), 0.3, 0.3, INTER_AREA);
	resize(img_display_mini4, img_display_mini4, Size(555, 555), 0.3, 0.3, INTER_AREA);
	
	Mat main = img_display + img_display_mini + img_display_mini2 + img_display_mini3 + img_display_mini4;
	imshow("Source Image", main);
	/*imshow("Source Image1", img_display_mini);
	imshow("Source Image2", img_display_mini2);
	imshow("Source Image3", img_display_mini3);
	imshow("Source Image4", img_display_mini4);*/
	
	waitKey(0);
	
	
}