#ifndef DEPTHPROCESSOR_H
#define DEPTHPROCESSOR_H

#include <opencv2/opencv.hpp>
#include "depthai/depthai.hpp"
#include <vector>

class DepthProcessor {
public:
    cv::Mat processDepthFrame(const std::shared_ptr<dai::ImgFrame>& inDepth);
    void analyzeSpatialData(const std::vector<dai::SpatialLocationCalculatorData::SpatialLocation>& spatialData,
                            std::vector<std::vector<int>>& grid, cv::Mat& depthFrameColor);
};

#endif // DEPTHPROCESSOR_H
