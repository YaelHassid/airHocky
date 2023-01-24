#include "Table.h"

Table::Table() {}
Table::~Table() {
}
bool Table::add_table_element(YaelLinkedListNode *node) {
    if (this->is_position_available(node)) {
        this->add(node);
        return true;
    }
    return false;
}
bool Table::push_at_current(YaelLinkedListNode *node) {
    node->next = this->current->next;
    this->add(node);
    return true;
}
bool Table::is_position_available(YaelLinkedListNode *node) {
    //Save current state:
    YaelLinkedListNode* curr = this->current;
    //Reset list to head:
    this->reBase();
    while (this->current) {
        if (node->check_collision(this->current))
            return false;
        this->advance();
    }
    this->current = curr; // Restore the state!
    return true;
}
void Table::move_element(double dT) {
    return this->move_element(this->current, dT);
}
 void Table::move_element(YaelLinkedListNode *node, double dT) {
    if (node->wall == NULL) {
        node->setPosition(node->getPosition().x + node->getSpeed().x * dT, node->getPosition().y + node->getSpeed().y * dT);
    }
}
YaelLinkedListNode* Table::search_collisions(YaelLinkedListNode &node, double dT) {
    if (node.wall != NULL) return NULL;
    YaelLinkedListNode *cur = this->current;
    YaelLinkedListNode * collided = NULL;
    this->reBase();
    while (this->current) {
        if (this->current != &node) {
            if (this->current->wall == NULL) {
                if (node.check_collision(this->current)) {
                    //Update speed:
                    node.updateClashedFlag(true);
                    this->current->updateClashedFlag(true);
                    node.update_collision_speed(*this->current);
                    collided = this->current;
                }
            } else {
                if (node.check_collision(this->current)) {
                    //Update speed:
                    node.updateClashedFlag(true);
                    node.update_collision_speed(*this->current);
                    collided = this->current;
                }
            }
        }
        this->advance();
    }
    this->current = cur; // Restore the state
    return collided;
}
