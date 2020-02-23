#pragma once
#include <vector>
#include "observer.h"
class Subject {
	std::vector<Observer*> observers;
	public:
	void attachObserver(Observer*);
	void notifyObservers() const;
};

