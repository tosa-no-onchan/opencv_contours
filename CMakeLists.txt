cmake_minimum_required(VERSION 3.1)
project( opencv_contours )
find_package( OpenCV REQUIRED )

include_directories(/home/nishi/usr/local/src/cpp-nishi/nishi-many-test/opencv_contours)

link_directories(/home/nishi/usr/local/src/cpp-nishi/nishi-many-test/opencv_contours/build)


#add_executable( main main.cpp )
#add_executable( main2 main2.cpp )
add_executable( main3 main3.cpp )
#add_executable( sample sample.cpp )


#target_link_libraries( main ${OpenCV_LIBS} )
#target_link_libraries( main2 ${OpenCV_LIBS} )
target_link_libraries( main3 ${OpenCV_LIBS} )
#target_link_libraries( sample ${OpenCV_LIBS} )

