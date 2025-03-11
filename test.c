#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "include/cstl.h"

void print_int_dynarray(dynarray(int) arr) {
	printf("ptr: %p, ", arr.at);
	printf("count: %ld, ", arr.count);
	printf("capacity: %ld\n", arr.capacity);	
	putc('[', stdout);
		for(size_t count = 0; count < dynarray_get_count(arr); count++) {
				printf("%d, ", arr.at[count]);
			}
		puts("]\n");
}

bool test_dynarray() {
    dynarray(int) arr = create_dynarray(int);

    if (dynarray_get_count(arr) != 0) return false;
    if (!dynarray_append(arr, 10)) return false;
    if (dynarray_get_count(arr) != 1) return false;
    if (arr.at[0] != 10) return false;
    if (!dynarray_insert(arr, 0, 20)) return false;
    if (arr.at[0] != 20 || arr.at[1] != 10) return false;
    if (!dynarray_remove(arr, 0)) return false;
    if (arr.at[0] != 10) return false;

    destroy_dynarray(arr);
    return true;
}

bool test_stack() {
    stack(int) st = create_stack(int);

    if (stack_get_count(st) != 0) return false;
    if (!stack_push(st, 5)) return false;
    if (stack_top(st) != 5) return false;
    if (!stack_push(st, 10)) return false;
    if (stack_top(st) != 10) return false;
    if (!stack_pop(st)) return false;
    if (stack_top(st) != 5) return false;

    destroy_stack(st);
    return true;
}

bool test_hashtable() {
    hashtable(int, int) ht = create_hashtable(int, int);

    hashtable_insert(ht, 1, 100);
    if (!hashtable_find(ht, 1)) return false;
    if (*hashtable_find(ht, 1) != 100) return false;
    hashtable_insert(ht, 2, 200);
    if (!hashtable_find(ht, 2) || *hashtable_find(ht, 2) != 200) return false;
    hashtable_remove(ht, 1);
    if (hashtable_find(ht, 1)) return false;

    destroy_hashtable(ht);
    return true;
}

bool test_hashset() {
    hashset(int) hs = create_hashset(int);

    hashset_insert(hs, 42, int);
    if (!hashset_contains(hs, 42)) return false;
    hashset_insert(hs, 99, int);
    if (!hashset_contains(hs, 99)) return false;
    hashset_remove(hs, 42);
    if (hashset_contains(hs, 42)) return false;

    destroy_hashset(hs);
    return true;
}

bool test_linked_list() {
    linked_list(int) *ll = create_linked_list();

    ll = linked_list_append(ll, 1);
    if (!linked_list_find(ll, 1)) return false;
    ll = linked_list_append(ll, 2);
    if (!linked_list_find(ll, 2)) return false;
    linked_list_remove(ll, 1);
    if (linked_list_find(ll, 1)) return false;

    destroy_linked_list(ll);
    return true;
}

bool test_queue() {
    queue(int) q = create_queue(int);

    if (!queue_enqueue(q, 10)) return false;
    if (!queue_enqueue(q, 20)) return false;
    if (queue_front(q) != 10) return false;
    queue_dequeue(q);
    if (queue_front(q) != 20) return false;

    destroy_queue(q);
    return true;
}

bool test_deque() {
    deque(int) dq = create_deque(int);

    deque_push_back(dq, 1, int);
    deque_push_back(dq, 2, int);
    if (deque_back(dq) != 2) return false;
    deque_push_front(dq, 0, int);
    if (deque_front(dq) != 0) return false;
    deque_pop_front(dq);
    if (deque_front(dq) != 1) return false;
    deque_pop_back(dq);
    if (deque_back(dq) != 1) return false;

    destroy_deque(dq);
    return true;
}

bool test_priority_queue() {
    priority_queue(int) pq = create_priority_queue(int);

    priority_queue_push(pq, 30, int);
    priority_queue_push(pq, 10, int);
    priority_queue_push(pq, 20, int);
    if (priority_queue_top(pq) != 10) return false;
    priority_queue_pop(pq);
    if (priority_queue_top(pq) != 20) return false;
    
    destroy_priority_queue(pq);
    return true;
}

bool test_pair() {
    pair(int, float) p = { .first = 42, .second = 3.14f };
    return (p.first == 42 && p.second == 3.14f);
}

bool test_span() {
    int arr[] = {1, 2, 3, 4, 5};
    span(int) sp = { .data = arr, .size = 5 };
    return (sp.size == 5 && sp.data[0] == 1);
}

void print_option_int(option(int) to_print) {
	if(to_print.valid) {
		printf("some(%d)", to_print.value);
	} else {
		printf("none");
	}
	puts("\n");
}

bool test_option() {
    option(int) some_value = some(42);
    option(int) none_value = none;


//	print_option_int(some_value);
//	print_option_int(none_value);
	
    return (some_value.valid && some_value.value == 42 && !none_value.valid);
}

bool test_result() {
	typedef char *char_ptr;

    result(int, char_ptr) success = { .value = 100, .error = NULL };
    result(int, char_ptr) failure = { .value = 0, .error = "Error!" };

    return (success.value == 100 && failure.error != NULL);
}

int main() {
	printf("Testing dynarray: %s\n", test_dynarray() ? "PASS" : "FAIL");
    printf("Testing stack: %s\n", test_stack() ? "PASS" : "FAIL");
    printf("Testing hashtable: %s\n", test_hashtable() ? "PASS" : "FAIL");
    printf("Testing hashset: %s\n", test_hashset() ? "PASS" : "FAIL");
    printf("Testing linked_list: %s\n", test_linked_list() ? "PASS" : "FAIL");
    printf("Testing queue: %s\n", test_queue() ? "PASS" : "FAIL");
    printf("Testing deque: %s\n", test_deque() ? "PASS" : "FAIL");
    printf("Testing priority_queue: %s\n", test_priority_queue() ? "PASS" : "FAIL");
    printf("Testing pair: %s\n", test_pair() ? "PASS" : "FAIL");
    printf("Testing span: %s\n", test_span() ? "PASS" : "FAIL");
    printf("Testing option: %s\n", test_option() ? "PASS" : "FAIL");
    printf("Testing result: %s\n", test_result() ? "PASS" : "FAIL");
}
 
