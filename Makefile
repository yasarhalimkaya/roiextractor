#
#
#

CC=g++
APP_NAME=roi_extractor

SHARED_LIBRARIES= \
	-lopencv_core \
	-lopencv_highgui \
	-lopencv_imgproc \
	-lopencv_imgcodecs \
	-lboost_system \
	-lboost_filesystem

# Assign the following variables if not using standart paths, e.g /usr/local
OPENCV_INCLUDE_PATH=""
OPENCV_LIBRARY_PATH=""
BOOST_INCLUDE_PATH=""
BOOST_LIBRARY_PATH=""

app:
	$(CC) -o $(APP_NAME) Main.cpp ImageFileParser.cpp -std=c++0x $(SHARED_LIBRARIES) \
#	-L$(OPENCV_LIBRARY_PATH) -L$(BOOST_LIBRARY_PATH) -I$(OPENCV_INCLUDE_PATH) -I$(BOOST_INCLUDE_PATH)
	
all:
	make app
	
clean:
	rm -fv $(APP_NAME)