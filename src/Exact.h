#ifndef EXACT_H_
#define EXACT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

class Exact {
public:
	Exact(const Instance* instance);
	virtual ~Exact();

	Solution solve();

private:

	const Instance* instance;
};
}

#endif
