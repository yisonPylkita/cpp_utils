# cpp_utils

Useful C++ utils

## Examples

### vector

```cpp
#include <cpp_utils/stl_utils.hpp>

struct Device {};

std::vector<std::pair<std::string, Device>> devices {
    {"printer", {}},
    {"scanner", {}},
    {"keyboard", {}},
};

if (!vec::contains_key(devices, "scanner"))
    std::cout << "Scanner not foun" << std::endl;
const auto printer = vec::get(devices, "scanner");

using namespace vec::operators;
const auto new_device_list = devices + {"dummy", {}};
```
