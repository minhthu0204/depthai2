#include "DepthProcessor.h"

static constexpr int GRID_SIZE = 5;

cv::Mat DepthProcessor::processDepthFrame(const std::shared_ptr<dai::ImgFrame>& inDepth) {
    cv::Mat depthFrame = inDepth->getFrame();
    cv::Mat depthFrameColor;
    cv::normalize(depthFrame, depthFrameColor, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::applyColorMap(depthFrameColor, depthFrameColor, cv::COLORMAP_HOT);
    return depthFrameColor;
}

void DepthProcessor::analyzeSpatialData(const std::vector<dai::SpatialLocationCalculatorData::SpatialLocation>& spatialData,
                                        std::vector<std::vector<int>>& grid, cv::Mat& depthFrameColor) {
    for (const auto& depthData : spatialData) {
        auto roi = depthData.config.roi.denormalize(depthFrameColor.cols, depthFrameColor.rows);
        auto coords = depthData.spatialCoordinates;
        float distance = std::sqrt(coords.x * coords.x + coords.y * coords.y + coords.z * coords.z);

        int col = static_cast<int>(depthData.config.roi.topLeft().x * GRID_SIZE);
        int row = static_cast<int>(depthData.config.roi.topLeft().y * GRID_SIZE);

        if (distance / 1000.0f < 1.0f) {
            grid[row][col]++;
        }

        int xmin = static_cast<int>(roi.topLeft().x);
        int ymin = static_cast<int>(roi.topLeft().y);
        int xmax = static_cast<int>(roi.bottomRight().x);
        int ymax = static_cast<int>(roi.bottomRight().y);

        cv::Scalar color = (distance / 1000.0f < 1.0f) ? cv::Scalar(0, 0, 255) : cv::Scalar(0, 255, 0);
        cv::rectangle(depthFrameColor, cv::Rect(cv::Point(xmin, ymin), cv::Point(xmax, ymax)), color, 2);
    }
}
