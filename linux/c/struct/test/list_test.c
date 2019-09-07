#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "cmockery.h"

#include "list.h"

#ifdef DEBUG
#define LOGD printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__)
#else
#define LOGD
#endif

typedef struct {
    struct list_head _head;
    void            *data;
}test_list_t;

test_list_t *
new_list_item(void *data)
{
    test_list_t *_list;
    _list = (test_list_t *)malloc(sizeof(test_list_t));
    INIT_LIST_HEAD(&_list->_head);
    _list->data = data;

    return _list;
}

int
del_list_item(test_list_t **item)
{
    assert_false(item == NULL);
    assert_false(*item == NULL);

    free((*item)->data);
    *item = NULL;

    return 0;
}

void
test_list_setup(void **state)
{
    test_list_t *g_list;
    g_list = (test_list_t *)malloc(sizeof(test_list_t));
    INIT_LIST_HEAD(&g_list->_head);
    g_list->data = "hello";

    *state = (void*)g_list;
}

void
test_list_add(void **state)
{
    struct list_head *head = (struct list_head *)(*state);
    struct list_head *item =
        (struct list_head *)malloc(sizeof(struct list_head));
    list_add(item, head);

    return;
}

void
test_list_teardown(void **state)
{
   test_list_t *_list = *state;
}

int main(int argc, char *argv[])
{
    UnitTest tests[] = {
        unit_test_setup_teardown(test_list_add, test_list_setup, test_list_teardown),
    };
    run_tests(tests);
    return 0;
}
