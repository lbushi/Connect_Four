#pragma once
class Subject;
class Observer {
	public:
		virtual void notify(const Subject&) = 0;
};
