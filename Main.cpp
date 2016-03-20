/*
 * Main.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: qbeart
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageFileParser.h"

#define NEXT_KEY 32  // Space
#define PREV_KEY 112 // P
#define EXIT_KEY 27  // Escape
#define WINDOW_NAME "ROI Extractor"

void help();
void onMouse(int event, int x, int y, int flags, void* userdata);

cv::Rect2i rect;
bool validRect = false;
cv::Mat displayedImage;
bool drawing = false;

int main(int argc, char* argv[])
{
	// Check the arguments
	if (argc != 2) {
		help();
		return -1;
	}

	ImageFileParser imageFileParser(argv[1]);

	if (!imageFileParser.isLoaded()) {
		std::cout << "Problem with loading images!" << std::endl;
		return -1;
	}

	// Create a window to show the images
	cv::namedWindow(WINDOW_NAME);

	// Set a mouse event callback to the window
	cv::setMouseCallback(WINDOW_NAME, onMouse, NULL);

	cv::Mat image;

	std::string folder = imageFileParser.getFolderPath();
	folder.append("/rois.txt");
	std::ofstream os(folder);

	// Load the first image
	if (!imageFileParser.next(image)) {
		std::cout << "Could not load an image" << std::endl;
	} else {
		while (true) {
			if (image.data) {
				displayedImage = image;
			}

			// Show the image
			cv::imshow(WINDOW_NAME, displayedImage);

			int key = cv::waitKey(0);

			if (key == NEXT_KEY) {
				if (validRect) {
					os << imageFileParser.getCurrentFilePath() << "," << rect.x << "," << rect.y << "," << rect.width << "," << rect.height << std::endl;
					validRect = false;
				}

				if (!imageFileParser.next(image)) {
					continue;
				}
			} else if (key == PREV_KEY) {
				if (!imageFileParser.previous(image)) {
					continue;
				}
			} else if (key == EXIT_KEY) {
				std::cout << "Exiting..." << std::endl;
				break;
			} else {
				std::cout << "Space -> Next image" << std::endl
						  << "P     -> Previous image" << std::endl
						  << "Esc   -> Exit" << std::endl;
			}
		}
	}

	cv::destroyAllWindows();
	os.close();

	return 0;
}

void help () {
	std::cout << "Usage: " << std::endl
			  << "./ROIExtractor image_path" << std::endl
			  << "image_path: directory containing the images" << std::endl;
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
		case cv::EVENT_LBUTTONDOWN:
			rect.x = x;
			rect.y = y;

			drawing = true;
			break;
		case cv::EVENT_LBUTTONUP:
			validRect = true;
			drawing = false;
			break;
		case cv::EVENT_MOUSEMOVE:
			if (drawing) {
				rect.width = x - rect.x;
				rect.height = y - rect.y;

				cv::Mat cloneImage = displayedImage.clone();
				cv::rectangle(cloneImage, rect, cv::Scalar(255, 0, 0));

				cv::imshow(WINDOW_NAME, cloneImage);
			}
			break;
		default:
			break;
	}
}
