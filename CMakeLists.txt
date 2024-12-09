cmake_minimum_required(VERSION 3.16)

project(depthai2 LANGUAGES CXX)

# Bật tự động xử lý UIC, MOC, và RCC của Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Sử dụng tiêu chuẩn C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tìm kiếm thư viện Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Tìm kiếm thư viện OpenCV
find_package(OpenCV REQUIRED)

# Tìm kiếm thư viện DepthAI (Cập nhật đường dẫn cài đặt nếu cần thiết)
find_package(depthai CONFIG REQUIRED PATHS /home/phulinh/depthai-core/build/install/lib/cmake/depthai)

# Định nghĩa danh sách tệp nguồn
set(SOURCES
  main.cpp
  PipelineManager.h PipelineManager.cpp
  DepthProcessor.h DepthProcessor.cpp
  ActionDecider.h ActionDecider.cpp
)

# Tạo tệp thực thi
add_executable(${PROJECT_NAME} ${SOURCES})

# Liên kết các thư viện cần thiết
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  PRIVATE ${OpenCV_LIBS}
  PRIVATE depthai::opencv
)

# Cấu hình cài đặt
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
