#include "subject.h"
void Subject::attachObserver(Observer* ob) {
	observers.emplace_back(ob);
}
void Subject::notifyObservers() const {
	for (auto ob: observers) {
		ob->notify(*this);
	}
}
