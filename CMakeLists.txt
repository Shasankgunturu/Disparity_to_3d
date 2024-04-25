cmake_minimum_required(VERSION 3.0.2)
project(flo_tests)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(PCL REQUIRED COMPONENTS common io visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(VTK REQUIRED COMPONENTS
  vtkCommonCore
  vtkRenderingCore
  vtkRenderingOpenGL2
  vtkInteractionStyle
  vtkRenderingFreeType  
)

include(${VTK_USE_FILE})

add_executable(convert src/disparityToCloud.cpp)
target_link_libraries(convert ${OpenCV_LIBS} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES} ${VTK_LIBRARIES})
