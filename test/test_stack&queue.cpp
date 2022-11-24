#include "stack.h"
#include "queue.h"

#include <gtest.h>

TEST(Tstack, stack1)
{
	Tstack<int> stack1, stack2;
	stack1.push(3);
	stack1.push(1);
	stack1.push(2);
	stack2 = stack1;
	stack2.pop();
	stack2.pop();
	EXPECT_EQ(3, stack2.get());
}

TEST(Tqueue, queue1)
{
	Tqueue<int> queue2;
	if (true) {
		Tqueue<int> queue1;
		queue1.push(3);
		queue1.push(1);
		queue1.push(2);
		queue2 = queue1;
	}
	queue2.pop();
	EXPECT_EQ(1, queue2.front());
}