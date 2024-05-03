
#include <cstddef>
#include <string>
#include <vector>

class ZBMLoader
{
public:
    ZBMLoader(const std::string filename);
    uint getWidth();
    uint getHeight();
    std::vector<std::byte> getData();

private:
    std::byte data;
};
