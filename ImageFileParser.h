/*
 * ImageFileParser.h
 *
 *  Created on: Mar 18, 2016
 *      Author: qbeart
 */

#ifndef IMAGEFILEPARSER_H_
#define IMAGEFILEPARSER_H_

#include <vector>
#include <opencv2/core/core.hpp>

class ImageFileParser {
public:
	ImageFileParser(char* );
	bool isLoaded();
	bool next(cv::Mat&);
	bool previous(cv::Mat&);
	std::string getFolderPath();
	std::string getCurrentFilePath();

	virtual ~ImageFileParser();

private:
	bool loaded;
	int index;
	std::string folder;
	std::vector<std::string> files;
};

#endif /* IMAGEFILEPARSER_H_ */
