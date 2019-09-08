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
malloc_list_item(void *data)
{
    test_list_t *_list;
    _list = (test_list_t *)malloc(sizeof(test_list_t));
    INIT_LIST_HEAD(&_list->_head);
    _list->data = data;

    return _list;
}

int
free_list_item(test_list_t **item)
{
    assert_true(item);
    assert_true(*item);

    test_list_t *tmp_entry = NULL;
    struct list_head *pos = NULL;
    test_list_t *head = *item;
    while (list_empty(&head->_head)) {
        tmp_entry = list_entry(pos, test_list_t, _head);
        free(tmp_entry->data);
        list_del(&head->_head);
        free(tmp_entry);
    }

    free(head->data);
    free(head);
    *item = NULL;

    return 0;
}

void
test_list_setup(void **state)
{
    char *c = (char *)malloc(4);
    c[0] = '1';
    c[1] = 0;
    test_list_t *g_list;
    g_list = malloc_list_item(c);
    *state = (void*)g_list;
}

void
test_list_add(void **state)
{
    struct list_head *pos = NULL;
    int               cnt = 0;
    test_list_t *tmp_entry = NULL;

    char *c = (char *)malloc(4);
    c[0] = '2';
    c[1] = 0;

    test_list_t *head = (test_list_t*)(*state);
    list_add(&malloc_list_item(c)->_head, &head->_head);

    c = (char *)malloc(4);
    c[0] = '3';
    c[1] = 0;
    list_add(&malloc_list_item(c)->_head, &head->_head);

    //printf("offset: %d\n", &((test_list_t*)0)->data);
    list_for_each(pos, &head->_head) {
       cnt++;
       tmp_entry = list_entry(pos, test_list_t, _head);
       //tmp_entry = (int)pos - (int) &(((test_list_t*)0)->_head);
       printf("pos data:%s\n", tmp_entry->data);
       //printf("pos data:%d %d", tmp_entry, pos);
    }

    printf("pos data:%s\n", head->data);
    assert_int_equal(cnt, 2);

    *state = head;

    return;
}

void
test_list_teardown(void **state)
{
   test_list_t *head= *state;
   free_list_item(&head);
}

int main(int argc, char *argv[])
{
    UnitTest tests[] = {
        unit_test_setup_teardown(test_list_add, test_list_setup, test_list_teardown),
    };
    run_tests(tests);
    return 0;
}
