#ifndef _CSTD_H_
#define _CSTD_H_

#define CSTL_alloc malloc
#define CSTL_realloc realloc
#define CSTL_dealloc free

#define dynarray(T) struct dynarray_##T {					\
	T *at;													\
	size_t count;											\
	size_t capacity;										\
}

// this just creates an empty array
#define create_dynarray(T) ({								\
	(dynarray(T)) {											\
		.at = NULL,											\
		.count = 0,											\
		.capacity = 0, 										\
	};														\
})

#define dynarray_get_count(array) (array.count)

#define dynarray_append(array, element) ({					\
	bool return_value = false;								\
	size_t element_byte_size = sizeof(array.at[0]);			\
	if(array.capacity == 0) {								\
		void *alloc_result = 								\
			CSTL_alloc(4 * element_byte_size);				\
		if(alloc_result) {									\
			array.at = alloc_result;						\
			array.capacity = 4;								\
			return_value = true;							\
		} else {											\
			fprintf(stderr, 								\
			"failed to allocated memory for dynamic array");\
			exit(EXIT_FAILURE);								\
		}													\
	}														\
															\
	if(array.count >= array.capacity) {						\
		void *realloc_result =								\
			CSTL_realloc(array.at, 							\
			2 * array.capacity * element_byte_size);		\
		if (realloc_result) {								\
			array.at = realloc_result;						\
			array.capacity *= 2;							\
			array.at[array.count] = element;				\
			array.count++;									\
			return_value = true;							\
		} else {											\
			return_value = false;							\
		}													\
	} else if(array.count < array.capacity) {				\
		array.at[array.count] = element;					\
		array.count++;										\
		return_value = true;								\
	}														\
	return_value;											\
})

#define dynarray_insert(array, position, element)	({		\
	bool return_value = false;								\
	if (array.count < position) {							\
		return_value = false;								\
	} else if (array.count == position) {					\
		return_value = dynarray_append(array, element);		\
	} else if (dynarray_append(array, 						\
		array.at[array.count - 1])) { 						\
		memmove(array.at + position + 1, 					\
			array.at + position, 							\
			(array.count - position) 					\
			* sizeof(*array.at)); 							\
		array.at[position] = element;						\
		return_value = true;								\
	}														\
	return_value;											\
})

#define dynarray_remove(array, position)	({				\
	bool return_value = false;								\
	if(position >= array.count) {							\
		return_value = false;								\
	} else {												\
		memmove(array.at + position,						\
			array.at + position + 1,						\
			(array.count - position - 1) 					\
			* sizeof(*array.at));							\
															\
		array.count--;										\
		if(array.count * 2 < array.capacity) {				\
			void *resize_result = CSTL_realloc(array.at, 	\
				(sizeof(array.at[0]) * array.capacity) / 2);\
			if(resize_result == NULL) {						\
				return_value = false;						\
			} else {										\
				return_value = true;						\
				array.at = resize_result;					\
				array.capacity /= 2;						\
			}												\
		}													\
	}														\
	return_value;											\
})

#define destroy_dynarray(array) ({							\
	if (array.at) { 										\
    	CSTL_dealloc(array.at); 							\
	}														\
	CSTL_dealloc(array.at);									\
	array.at = NULL;										\
	array.count = 0;										\
	array.capacity = 0;										\
})

#define stack(T) struct stack_##T {							\
	T *at;													\
	size_t count;											\
	size_t capacity;										\
}

#define create_stack(T) ({               					\
    (stack(T)) {                         					\
        .at = NULL,                      					\
        .count = 0,                       					\
        .capacity = 0,                     					\
    };                                   					\
})

#define stack_get_count(stack) ((stack).count)

#define stack_push(stack, element) ({                             \
    bool return_value = false;                                    \
    size_t element_byte_size = sizeof(stack.at[0]);               \
    if (stack.capacity == 0) {                                    \
        void *alloc_result = CSTL_alloc(4 * element_byte_size);   \
        if (alloc_result) {                                       \
            stack.at = alloc_result;                              \
            stack.capacity = 4;                                   \
            return_value = true;                                  \
        } else {                                                  \
            fprintf(stderr, "Memory allocation failed\n");        \
            exit(EXIT_FAILURE);                                   \
        }                                                         \
    }                                                             \
    if (stack.count >= stack.capacity) {                          \
        void *realloc_result = 									  \
        	CSTL_realloc(stack.at, 							      \
        		2 * stack.capacity * element_byte_size); 		  \
        if (realloc_result) {                                     \
            stack.at = realloc_result;                            \
            stack.capacity *= 2;                                  \
        } else {                                                  \
            return_value = false;                                 \
        }                                                         \
    }                                                             \
    if (stack.count < stack.capacity) {                           \
        stack.at[stack.count] = element;                          \
        stack.count++;                                            \
        return_value = true;                                      \
    }                                                             \
    return_value;                                                 \
})

#define stack_pop(stack) ({                                       \
    bool return_value = false;                                    \
    if (stack.count == 0) {                                       \
        fprintf(stderr, "Error: Stack underflow\n");              \
        return_value = false;                                     \
    } else {                                                      \
        stack.count--;                                            \
        if (stack.count * 4 < stack.capacity) {                   \
            void *resize_result = CSTL_realloc(stack.at,          \
                (sizeof(stack.at[0]) * stack.capacity) / 2);      \
            if (resize_result) {                                  \
                stack.at = resize_result;                         \
                stack.capacity /= 2;                              \
            }                                                     \
        }                                                         \
        return_value = true;                                      \
    }                                                             \
    return_value;                                                 \
})

#define stack_top(stack) ({                                      \
    typeof(stack.at[0]) return_value;                            \
    if (stack.count == 0) {                                      \
        fprintf(stderr, "Error: Stack is empty\n");              \
        exit(EXIT_FAILURE);                                      \
    }                                                            \
    return_value = stack.at[stack.count - 1];                    \
    return_value;                                                \
})

#define destroy_stack(stack) ({                                  \
    if (stack.at) { CSTL_dealloc(stack.at); }                    \
    stack.at = NULL;                                             \
    stack.count = 0;                                             \
    stack.capacity = 0;                                          \
})

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
