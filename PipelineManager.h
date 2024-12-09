#ifndef PIPELINEMANAGER_H
#define PIPELINEMANAGER_H

#include "depthai/depthai.hpp"
#include <memory>

class PipelineManager {
public:
    PipelineManager();
    std::shared_ptr<dai::DataOutputQueue> getQueue(const std::string& name, int maxSize = 4, bool blocking = false);

private:
    void setupPipeline();

    dai::Pipeline pipeline;
    std::shared_ptr<dai::Device> device;
};

#endif // PIPELINEMANAGER_H
