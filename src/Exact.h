#ifndef EXACT_H_
#define EXACT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

/**
 * Implementation of exact algorithm
 */
class Exact {
public:
	Exact(const Instance* instance);
	virtual ~Exact();

	/**
	 * @param threads Number of threads used to solve
	 */
	Solution solve(std::size_t threads = 1) const;

	/**
	 * @return Instance of problem
	 */
	const Instance* getInstance() const {
		return instance;
	}

private:

	/**
	 * Instance of problem
	 */
	const Instance* instance;

	/**
	 * Function called by every thread
	 */
	static void* parallelSolve(void * param);

	/**
	 * Struct used to hold instance informations
	 */
	typedef struct _thread_arg thread_arg;
};
}

#endif
