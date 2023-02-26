#include "co.h"

#include <stdlib.h>
#include <setjmp.h>
#include <stdint.h>

#include "co_list.h"

#define STACK_SIZE (64 * 1024)

enum co_status {
  CO_NEW = 1,
  CO_RUNNING,
  CO_WAITING,
  CO_OVER
};

struct co {
  const char* name;
  void (*func)(void*);
  void* arg;
  jmp_buf env;
  enum co_status status;
  struct co* waiter;
  unsigned char stack[STACK_SIZE];
};


static inline void stack_switch_call(void *sp, void *entry, void* arg) {
	asm volatile (
#if __x86_64__
			"movq %%rcx, 0(%0); movq %0, %%rsp; movq %2, %%rdi; call *%1"
			: : "b"((uintptr_t)sp - 16), "d"((uintptr_t)entry), "a"((uintptr_t)arg)
#else
			"movl %%ecx, 4(%0); movl %0, %%esp; movl %2, 0(%0); call *%1"
			: : "b"((uintptr_t)sp - 8), "d"((uintptr_t)entry), "a"((uintptr_t)arg) 
#endif
			);
}

static inline void restore_return() {
	asm volatile (
#if __x86_64__
			"movq 0(%%rsp), %%rcx" : : 
#else
			"movl 4(%%esp), %%ecx" : :  
#endif
			);
}

struct co* current = NULL;
//--------------------------------
struct co *co_start(const char *name, void (*func)(void *), void *arg) {
  struct co* p_co = (struct co*) malloc(sizeof(struct co));
  assert(p_co);

  p_co->name = name;
  p_co->func = func;
  p_co->arg = arg;
  p_co->status = CO_NEW;
  p_co->waiter = NULL;
  
  co_node_insert(p_co);
  return p_co;
};

void co_wait(struct co *pco) {
  assert(pco);
  if (pco->status != CO_OVER) {
    pco->waiter = current;
    pco->status = CO_WAITING;
    co_yield();
  }

  while (cur_node->cur != pco) {
    cur_node = cur_node->rhs;
  }

  free(pco);
  free(co_node_remove());
}

void co_yield() {
  int ret = setjmp(current->env);
  if (ret == 0) { // 停止，跳其他函数
    // find another co
    cur_node = cur_node->lhs;
    while (cur_node->cur->status != CO_NEW && 
          cur_node->cur->status != CO_RUNNING) {
      cur_node = cur_node->rhs;
    }
    current = cur_node->cur;
    assert(current);
    // switch co
    if (current->status == CO_NEW) {
      ((volatile struct co*)current)->status = CO_RUNNING; // set status
      // 将参数压入栈
      stack_switch_call(current->stack + STACK_SIZE, current->func, current->arg);
      // 恢复相关寄存器
      restore_return();

      current->status = CO_OVER;

      if (current->waiter) {
        current->waiter->status = CO_RUNNING;
        co_yield();
      }
    } else { // CO_RUNNING
      longjmp(cur_node->cur->env, 1);
    }
  }
  assert(ret && current->status == CO_RUNNING);
}


static __attribute__((constructor)) void co_constructor(void) {
  current = co_start("main", NULL, NULL);
  current->status = CO_RUNNING;
}

static __attribute__((destructor)) void co_destructor(void) {
  while (cur_node) {
    free(cur_node->cur);
    free(co_node_remove());
  }
}