#pragma once
#include "controller.h"
class ControllerX: public Controller {
	public:
		Command* handleInput() override ;
};
