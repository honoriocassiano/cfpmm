#ifndef EXACT_H_
#define EXACT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

class Exact {
public:
	Exact(Instance* instance);
	virtual ~Exact();

	Solution solve();

private:

	Instance* instance;
};
}

#endif
