#pragma once

#include "Core.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace Core {
    using InputEvent = std::variant<MouseEvent, KeyEvent>;
}
