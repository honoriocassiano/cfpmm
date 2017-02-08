#ifndef EXACT_H_
#define EXACT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

class Exact {
public:
	Exact(const Instance* instance);
	virtual ~Exact();

	Solution solve(std::size_t threads = 1) const;

	const Instance* getInstance() const {
		return instance;
	}

private:
	const Instance* instance;

	static void* parallelSolve(void * param);

	typedef struct _thread_arg thread_arg;
};
}

#endif
