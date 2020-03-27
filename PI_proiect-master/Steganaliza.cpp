#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
typedef unsigned char BYTE;
typedef unsigned long DWORD;


int main()
{
	cv::Mat img;

	img = cv::imread("Imagine_Mesaj_Rezultat.png", 1);

	DWORD x = 0;
	DWORD y = 0;

	std::string mesaj_rezultat;

	BYTE octet_rezultat = 0;
	DWORD MASK = 0x01;
	DWORD counter = 8;
	BYTE octet;

	int flag = 1;

	for (y = 0; y < img.rows && flag; ++y)
	{
		for (x = 0; x < img.cols && flag; ++x)
		{
			if (img.at<BYTE>(y, 3 * x) == 'R' && img.at<BYTE>(y, 3 * x + 1) == 'C' && img.at<BYTE>(y, 3 * x + 2) == 'T') {
				flag = 0;
				break;
			}
			if (counter != 0)
			{
				octet = img.at<BYTE>(y, 3 * x) & MASK;
				octet = octet << (counter - 1);
				octet_rezultat = octet_rezultat | octet;

				counter--;

				if (counter == 0)
				{
					counter = 8;
					mesaj_rezultat.push_back((unsigned char)octet_rezultat);
					octet_rezultat = 0;

				}
			}
		}
	}

	std::cout << mesaj_rezultat;
	
	cv::waitKey(0);
	return 0;
}