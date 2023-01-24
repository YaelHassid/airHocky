#ifndef AIRHOCKEY_TABLE_H
#define AIRHOCKEY_TABLE_H
#include "YaelLinkedList.h"

class Table: public YaelLinkedList {
public:
    //Constructor:
    Table();
    //Destructor:
    ~Table();
    //Put an element (node) on the table if available:
    bool add_table_element(YaelLinkedListNode *node);
    //Put an element (node) on the table assumes without availability check:
    bool push_at_current(YaelLinkedListNode *node);
    // Table related methods:
    bool is_position_available(YaelLinkedListNode *node);
    // Move an element on the table:
    void move_element(double dT);
    void move_element(YaelLinkedListNode *node, double dT);
    //Search for collisions:
    YaelLinkedListNode* search_collisions(YaelLinkedListNode &node, double dT);
};


#endif //AIRHOCKEY_TABLE_H
