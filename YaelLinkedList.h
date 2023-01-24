#ifndef AIRHOCKEY_YAELLINKEDLIST_H
#define AIRHOCKEY_YAELLINKEDLIST_H
#include "YaelLinkedListNode.h"

class YaelLinkedList {

public:

    YaelLinkedListNode* head;
    YaelLinkedListNode* current;
    YaelLinkedList();
    virtual ~YaelLinkedList();
    YaelLinkedListNode* add(YaelLinkedListNode* node);
    void remove_current();
    YaelLinkedList* reBase();
    YaelLinkedListNode* advance(int steps = 1);
    void print();

};
#endif //AIRHOCKEY_YAELLINKEDLIST_H
