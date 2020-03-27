#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
typedef unsigned char BYTE;
typedef unsigned long DWORD;


int main(int argc,char* argv[])
{
	cv::Mat img;

	img = cv::imread(argv[2], 1);
	if (argc > 1)
	{
		std::string mesaj{ argv[1] };

		BYTE MASK = 0x80;
		DWORD y = 0;
		DWORD x = 0;
		for (auto elem : mesaj)
		{
			DWORD counter = 8;
			while (counter)
			{
				BYTE bit_of_interest = elem & MASK;
				bit_of_interest = bit_of_interest >> (counter - 1);
				MASK = MASK >> 1;
				counter--;

				if (x + 3 <= 3 * img.cols)
				{
					BYTE& oct1 = img.at<BYTE>(y, x);
					BYTE& oct2 = img.at<BYTE>(y, x + 1);
					BYTE& oct3 = img.at<BYTE>(y, x + 2);

					oct1 = ((oct1 >> 1) << 1) | (bit_of_interest);
					oct2 = ((oct2 >> 1) << 1) | (bit_of_interest);
					oct3 = ((oct3 >> 1) << 1) | (bit_of_interest);

					x += 3;
				}
				else
				{
					x = 0;
					y++;

					BYTE& oct1 = img.at<BYTE>(y, x);
					BYTE& oct2 = img.at<BYTE>(y, x + 1);
					BYTE& oct3 = img.at<BYTE>(y, x + 2);

					oct1 = ((oct1 >> 1) << 1) | (bit_of_interest);
					oct2 = ((oct2 >> 1) << 1) | (bit_of_interest);
					oct3 = ((oct3 >> 1) << 1) | (bit_of_interest);

					x += 3;
				}

			}
			MASK = 0x80;
		}

		if (x < 3 * img.cols)
		{
			BYTE& oct1 = img.at<BYTE>(y, x);
			BYTE& oct2 = img.at<BYTE>(y, x + 1);
			BYTE& oct3 = img.at<BYTE>(y, x + 2);

			oct1 = 'R';
			oct2 = 'C';
			oct3 = 'T';
		}

	}
	cv::imwrite("Imagine_Mesaj_Rezultat.png", img);
	std::cout << "\n";
	return 0;
}