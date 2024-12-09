#include "PipelineManager.h"

static constexpr int GRID_SIZE = 5;

PipelineManager::PipelineManager() {
    setupPipeline();
}

void PipelineManager::setupPipeline() {
    auto monoLeft = pipeline.create<dai::node::MonoCamera>();
    auto monoRight = pipeline.create<dai::node::MonoCamera>();
    auto stereo = pipeline.create<dai::node::StereoDepth>();
    auto spatialLocationCalculator = pipeline.create<dai::node::SpatialLocationCalculator>();

    auto xoutDepth = pipeline.create<dai::node::XLinkOut>();
    auto xoutSpatialData = pipeline.create<dai::node::XLinkOut>();
    auto xinSpatialCalcConfig = pipeline.create<dai::node::XLinkIn>();

    xoutDepth->setStreamName("depth");
    xoutSpatialData->setStreamName("spatialData");
    xinSpatialCalcConfig->setStreamName("spatialCalcConfig");

    monoLeft->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);
    monoLeft->setCamera("left");
    monoRight->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);
    monoRight->setCamera("right");

    stereo->setDefaultProfilePreset(dai::node::StereoDepth::PresetMode::HIGH_DENSITY);
    stereo->setLeftRightCheck(true);
    stereo->setSubpixel(true);

    spatialLocationCalculator->inputConfig.setWaitForMessage(false);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            dai::SpatialLocationCalculatorConfigData config;
            config.depthThresholds.lowerThreshold = 200;
            config.depthThresholds.upperThreshold = 30000;
            config.calculationAlgorithm = dai::SpatialLocationCalculatorAlgorithm::MEDIAN;
            config.roi = dai::Rect(
                dai::Point2f(i * 0.2f, j * 0.2f),
                dai::Point2f((i + 1) * 0.2f, (j + 1) * 0.2f)
                );
            spatialLocationCalculator->initialConfig.addROI(config);
        }
    }

    monoLeft->out.link(stereo->left);
    monoRight->out.link(stereo->right);

    spatialLocationCalculator->passthroughDepth.link(xoutDepth->input);
    stereo->depth.link(spatialLocationCalculator->inputDepth);
    spatialLocationCalculator->out.link(xoutSpatialData->input);
    xinSpatialCalcConfig->out.link(spatialLocationCalculator->inputConfig);

    device = std::make_shared<dai::Device>(pipeline);
    device->setIrLaserDotProjectorBrightness(1000);
}

std::shared_ptr<dai::DataOutputQueue> PipelineManager::getQueue(const std::string& name, int maxSize, bool blocking) {
    return device->getOutputQueue(name, maxSize, blocking);
}
