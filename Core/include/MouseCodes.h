#pragma once

#include "Core.h"

namespace Core {
    using MouseCode = uint16_t;

	enum : MouseCode {
		ButtonLeft = 0,
		ButtonRight,
		ButtonMiddle,
		Button3,
		Button4,
	};
}
