#pragma once

#include "Core.h"
#include "InputEvent.h"
#include "WindowEvent.h"

namespace Core {
    using Event = std::variant<InputEvent, WindowEvent>;
}
