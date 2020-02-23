#pragma once
#include "controller.h"
class ControllerO: public Controller {
	public:
		Command* handleInput() override;
};
