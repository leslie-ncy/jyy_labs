#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

typedef struct CONODE {
    struct co* cur;
    struct CONODE* lhs, * rhs;
} CoNode;

static CoNode* cur_node = Null;

static void co_node_insert(struct co *coroutine) {
	CoNode *victim = (CoNode*)malloc(sizeof(CoNode));
	assert(victim);

	victim->cur = coroutine;
	if(cur_node == NULL) {
		victim->lhs = victim->rhs = victim;
		cur_node = victim;
	}else {
		victim->lhs = cur_node->lhs;
		victim->rhs = cur_node;
		victim->lhs->rhs = victim->rhs->lhs = victim;
	}
}

static CoNode *co_node_remove() {
	CoNode *victim = NULL;

	if(cur_node == NULL) { return NULL; }
	else if(cur_node->rhs == cur_node) {
		victim = cur_node;
		cur_node = NULL;
	}else {
		victim = cur_node;

		cur_node = cur_node->rhs;
		cur_node->lhs = victim->lhs;
		cur_node->lhs->rhs = cur_node;
	}

	return victim;
}