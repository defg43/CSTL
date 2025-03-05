#ifndef _CSTD_H_
#define _CSTD_H_

#define CSTL_alloc malloc
#define CSTL_realloc realloc
#define CSTL_dealloc free

// containers
#define dynarray(T) struct dynarray_##T {					\
	T *at;													\
	size_t count;											\
	size_t capacity;										\
}

// this just creates an empty array
#define create_dynarray(T) ({								\
	dynarray(T) ret = {										\
		.at = NULL,											\
		.count = 0,											\
		.capacity = 0, 										\
	};														\
	return ret;												\
})

#define dynarray_append(array, element) ({					\
	size_t element_byte_size = sizeof(array.at[0]);			\
	if(array.count >= array.capacity) {						\
		void *realloc_result = NULL;						\
		if(realloc_result = 								\
			CSTL_realloc(array.at, 							\
			2 * array.capacity * element_byte_size )) {		\
			array.at = realloc_result;						\
			array.capacity *= 2;							\
			array.at[array.count] = element;				\
			array.count++;									\
			return true;									\
		}													\
		return false;										\
	} else if(array.count < array.capacity) {				\
		array.at[array.count] =  element;					\
		array.count++;										\
	}														\
})

#define stack(T) struct stack_##T {							\
	T *at;													\
	size_t count;											\
	sizt_t capacity;										\
}

#define hashtable(T1, T2) struct hashtable_##T1##_##T2 { 	\
	T1 *key;												\
	T2 *value;												\
	size_t count;											\
	size_t capacity;										\
}

#define hashset(T) struct hashset_##T {   					\
    T *data;                          						\
    size_t count;                     						\
    size_t capacity;                  						\
}

#define linked_list(T) struct linked_list_##T {  			\
    T value;                                    			\
    struct linked_list_##T *next;               			\
}

#define queue(T) struct queue_##T {         				\
    T *data;                               					\
    size_t head;                           					\
    size_t tail;                           					\
    size_t capacity;                       					\
}

#define deque(T) struct deque_##T {         				\
    T *data;                               					\
    size_t front;                          					\
    size_t back;                           					\
    size_t capacity;                       					\
}

#define priority_queue(T) struct priority_queue_##T {  		\
    T *data;                                       			\
    size_t count;                                  			\
    size_t capacity;                               			\
}

#define pair(T1, T2) struct pair_##T1##_##T2 {  			\
    T1 first;                               				\
    T2 second;                              				\
}

#define span(T) struct span_##T { 							\
    T *data;                     							\
    size_t size;                 							\
}

#define option(T) struct option_##T { 						\
	T value;												\
	bool valid;												\
}

#define result(T1, T2) struct result_##T1##_##T2 {			\
	T1 value;												\
	T2 error;												\
}

#endif // _CSTD_H_
