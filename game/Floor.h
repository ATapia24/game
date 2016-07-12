#pragma once
#include "Entity.h"
#include "WindowMgr.h"
#include <iostream>

class Floor : public Entity
{
	protected:

	public:
		Floor(WindowMgr* _window);
		Floor();
		~Floor();
};

