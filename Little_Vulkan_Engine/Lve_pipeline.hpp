#pragma once

#include <string>
#include <vector>
namespace lve
{
    class Lvepipeline
    {
    public:
        Lvepipeline(const std::string& vertFilepath, const std::string& fragFilepath);
    
    private:
        static std::vector<char> ReadFile(const std::string& filepath);
        void CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);

    };
}