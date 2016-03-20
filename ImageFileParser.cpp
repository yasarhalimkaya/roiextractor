/*
 * ImageFileParser.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: qbeart
 */

#include "ImageFileParser.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <opencv2/highgui/highgui.hpp>

ImageFileParser::ImageFileParser(char* directory) :
	loaded(false),
	index(-1),
	folder(std::string(directory))
{
	boost::filesystem::path path(directory);

	try {
		// Sanity checks on given argument
		if (!boost::filesystem::exists(path)) {
			std::cout << "Given directory does not exists!" << std::endl;
			return;
		}

		if (!boost::filesystem::is_directory(path)) {
			std::cout << "Given argument is NOT a directory!" << std::endl;
			return;
		}

		// Traverse directory
		for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(path)) {
			files.push_back(entry.path().string());
		}
	} catch (const boost::filesystem::filesystem_error& err) {
		std::cout << err.what() << std::endl;
	}

	loaded = true;
}

std::string ImageFileParser::getFolderPath() {
	return folder;
}

std::string ImageFileParser::getCurrentFilePath() {
	return files[index];
}

bool ImageFileParser::isLoaded() {
	return loaded;
}

bool ImageFileParser::next(cv::Mat& image) {
	if (index > (signed)files.size()-1) {
		return false;
	}

	image = cv::imread(files[++index], CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data) {
		std::cout << "Not an image : " << files[index] << std::endl;
		return next(image);
	}

	std::cout << "Loaded : " << files[index] << std::endl;
	return true;
}

bool ImageFileParser::previous(cv::Mat& image) {
	if (index <= 0) {
		return false;
	}

	image = cv::imread(files[--index], CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data) {
		std::cout << "Not an image : " << files[index] << std::endl;
		return previous(image);
	}

	std::cout << "Loaded : " << files[index] << std::endl;
	return true;
}

ImageFileParser::~ImageFileParser() {
	// TODO Auto-generated destructor stub
}

