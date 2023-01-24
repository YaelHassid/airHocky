#include <iostream>
#include "YaelLinkedList.h"

YaelLinkedList::YaelLinkedList() {
    this->head = NULL;
    this->current = NULL;
}

YaelLinkedListNode* YaelLinkedList::add(YaelLinkedListNode* node) {
    if (this->head == NULL) {
        this->head = node;
    }
    if(this->current != NULL){
        this->current->next = node;
    }
    this->current = node;
    return node;
}
void YaelLinkedList::remove_current() {
    YaelLinkedListNode *cache = this->current;
    YaelLinkedListNode *prev = NULL;
    this->reBase();
    while (this->current != NULL) {
        if (this->current == cache) {
            if (prev == NULL) {
                this->head = this->current->next;
                this->current = this->head;
            } else {
                prev->next = this->current->next;
                this->current = prev;
            }
            delete cache;
            return;
        }
        prev = this->current;
        this->advance();
    }
    this->current = cache;
}
YaelLinkedList* YaelLinkedList::reBase() {
    this->current = this->head;
    return this;
}

YaelLinkedListNode* YaelLinkedList::advance(int steps) {
    for (int i = 0; i < steps; i++) {
        if (this->current != NULL && this->current->next != NULL)
            this->current = this->current->next;
        else {
            this->current = NULL;
            break;
        }
    }
    return this->current;
}

void YaelLinkedList::print() {
    YaelLinkedListNode* curr = this->current;
    this->reBase();
    while(this->current != NULL) {
        if(this->current->wall == NULL){
            this->current->print();
        }
        this->advance();
    }
    this->current = curr;
}
YaelLinkedList::~YaelLinkedList() {
    YaelLinkedListNode* curr = this->head;
    while(curr != NULL){
        delete curr;
        curr = curr->next;
    }
}