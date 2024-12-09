#include <QCoreApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "PipelineManager.h"
#include "DepthProcessor.h"
#include "ActionDecider.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    PipelineManager pipelineManager;
    DepthProcessor depthProcessor;
    ActionDecider actionDecider;

    auto depthQueue = pipelineManager.getQueue("depth");
    auto spatialCalcQueue = pipelineManager.getQueue("spatialData");

    while (true) {
        auto inDepth = depthQueue->get<dai::ImgFrame>();
        auto depthFrameColor = depthProcessor.processDepthFrame(inDepth);

        auto spatialData = spatialCalcQueue->get<dai::SpatialLocationCalculatorData>()->getSpatialLocations();
        std::vector<std::vector<int>> grid(5, std::vector<int>(5, 0));

        depthProcessor.analyzeSpatialData(spatialData, grid, depthFrameColor);
        QString action = actionDecider.decideAction(grid);

        std::cout << "Action: " << action.toStdString() << std::endl;
        cv::imshow("depth", depthFrameColor);

        if (cv::waitKey(1) == 'q') break;
    }

    return app.exec();
}
