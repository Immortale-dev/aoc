#include <queue>
#include <stdexcept>

struct Oper {
	char oper;
	pair<bool, ll> item;
};

class Monkey {
	public:
		Monkey(std::queue<ll> items, Oper operation, ll test_divisible, int test_true, int test_false);
		pair<ll, int> throw_item(ll divis = 3);
		bool empty();
		void catch_item(ll item);
		
	private:
		ll do_oper(ll item);
		bool test(ll item);
		
		std::queue<ll> items;
		Oper operation;
		ll test_divisible;
		int test_true, test_false;
};

Monkey::Monkey(std::queue<ll> items, Oper operation, ll test_divisible, int test_true, int test_false):
	items(items), operation(operation), test_divisible(test_divisible), test_true(test_true), test_false(test_false) {}

pair<ll, int> Monkey::throw_item(ll divis) {
	ll item = items.front();
	items.pop();
	
	item = do_oper(item);
	if (divis != 1) item /= divis;
	
	return {item, test(item) ? test_true : test_false};
}

bool Monkey::empty() {
	return items.empty();
}

void Monkey::catch_item(ll item) {
	items.push(item);
}

///// PRIVATE

ll Monkey::do_oper(ll item) {
	ll op_item = operation.item.first ? item : operation.item.second;
	switch(operation.oper) {
		case '+':
			return item + op_item;
		case '*':
			return item * op_item;
	}
	throw logic_error("impossible operation");
}

bool Monkey::test(ll item) {
	return !(item % test_divisible);
}
