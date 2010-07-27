// Import a garbage collector 
// http://www.gnu.org/s/libc/manual/html_node/Hooks-for-Malloc.html
// http://www.hpl.hp.com/personal/Hans_Boehm/gc/simple_example.html
#include <malloc.h>
#include "gc/include/gc.h"

/* Prototypes for our hooks.  */
static void my_init_hook (void);

static void *my_malloc_hook (size_t, const void *);
static void *my_realloc_hook(void *, size_t, const void *);
static void my_free_hook (void *, const void *);

static void *(*old_malloc_hook) (size_t, const void *);
static void *(*old_realloc_hook) (void *, size_t, const void *);
static void (*old_free_hook) (void *, const void *);

/* Override initializing hook from the C library. */
void (*__malloc_initialize_hook) (void) = my_init_hook;

#define move_all_hooks(from,to) { \
    to ## malloc_hook = from ## malloc_hook; \
    to ## free_hook = from ## free_hook; \
    to ## realloc_hook = from ## realloc_hook; \
}

#define save_old_hooks() move_all_hooks(__, old_);
#define load_my_hooks() move_all_hooks(my_, __);
#define load_old_hooks() move_all_hooks(old_, __);

static void my_init_hook (void)
{
    save_old_hooks();
    load_my_hooks();
    GC_INIT();
}
static void *my_malloc_hook (size_t size, const void *caller)
{
    void *result;

    load_old_hooks();
    result = GC_MALLOC(size);
    load_my_hooks();

    return result;
}
static void * my_realloc_hook (void *ptr, size_t size, const void *caller)
{
    void *result;

    load_old_hooks();
    result = GC_REALLOC(ptr, size);
    load_my_hooks();

    return result;
}

static void my_free_hook (void *ptr, const void *caller)
{
    load_old_hooks();
    GC_FREE(ptr);
    load_my_hooks();
}

