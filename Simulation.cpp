#include "Simulation.h"
#include "ExplodingDisc.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Simulation::Simulation() {
    this->table = new Table();
}
void Simulation::getInputs() {
    string command, input;
    stringstream ss;
    double x, y, x1, y1, x2, y2, T, dT, vx, vy, radius, flag1 = 0, flag2 = 0;
    while (getline(cin, input)) {
        stringstream ss(input);
        ss >> command;
        if (command == "disc" || command == "wall" || command == "exploding_disc" || command == "shrinking_disc") {
            //Create a generic node:
            YaelLinkedListNode *element = NULL;
            //Get corresponding values:
            if (command == "disc") {
                ss >> x >> y >> vx >> vy >> radius;
                if (ss.fail()) {
                    cerr << "Error: illegal input." << endl;
                    break;
                }
                element = new YaelLinkedListNode(x, y, vx, vy, radius, 0);
            } else if (command == "exploding_disc") {
                ss >> x >> y >> vx >> vy >> radius;
                if (ss.fail()) {
                    cerr << "Error: illegal input." << endl;
                    break;
                }
                element = new YaelLinkedListNode(x, y, vx, vy, radius, 1);
            } else if (command == "shrinking_disc") {
                ss >> x >> y >> vx >> vy >> radius;
                if (ss.fail()) {
                    cerr << "Error: illegal input." << endl;
                    break;
                }
                element = new YaelLinkedListNode(x, y, vx, vy, radius, 2);
            } else if (command == "wall") {
                ss >> x1 >> y1 >> x2 >> y2;
                if (ss.fail()) {
                    cerr << "Error: illegal input." << endl;
                    break;
                }
                element = new YaelLinkedListNode(x1, y1, x2, y2);
            }
            //Make sure we have space for it:
            if (!this->table->add_table_element(element)) {
                flag2 = 1;
                if (element->disc != NULL || element->shrinkingDisc != NULL || element->explodingDisc != NULL) {
                    cerr << "Error: disc to disc collision detected in initial configuration" << endl;
                } else {
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                }
                delete element;
            }
        }
        else if (command == "simulate") {
            ss >> T >> this->dT;
            dT =  this->dT;
            if (ss.fail()) {
                cerr << "Error: illegal input." << endl;
                break;
            }
            this->simulate(T, dT);
            flag1 = 1;
            break;
        }
        else{
            flag2 = 1;
            cerr << "Error: illegal input." << endl;
            break;
        }
    }
    if (cin.eof() && flag1 == 0 && flag2 == 0){
        cerr << "Error: illegal input." << endl;
    }
}
void Simulation::simulate(double T, double dT) {
    double timer = 0;
    Vector2D oldPosition;
    while (timer <= T) {
        this->print(timer);
        this->table->reBase(); //pointing to the head of the list
        //Loop to find clashes - first iteration
        while (this->table->current) { //while current is not null
            if (this->table->current->wall == NULL) { //its a some sort of a disc
                YaelLinkedListNode *collidedWith;
                oldPosition = this->table->current->getPosition();
                //Move the element:
                this->table->move_element(dT);
                //Check for clashes:
                if ((collidedWith = this->table->search_collisions(*this->table->current, dT))){
                    this->table->current->setPosition(oldPosition.x, oldPosition.y);
                }
            }
            this->table->advance();
        }
        //Loop to handle disc types after clashes - second iteration
        this->table->reBase(); //pointing to the head of the list
        while (this->table->current) { //while current is not null
            if (this->table->current->wall == NULL) { //its a sort of disc
                //case of normal disc
                if (this->table->current->disc != NULL) {
                    this->table->current->disc->clashed = false;
                //case of shrinking disc
                } else if (this->table->current->shrinkingDisc != NULL && this->table->current->shrinkingDisc->clashed) {
                    ShrinkingDisc* cur = this->table->current->shrinkingDisc;
                    cur->clashed = false;
                    cur->radius = 0.9 * cur->radius;
                    cur->clashCounter++;
                    if (cur->clashCounter == 3) {
                        this->table->remove_current();
                    }
                //case of exploding disc
                } else if (this->table->current->explodingDisc != NULL && this->table->current->explodingDisc->clashed){
                    ExplodingDisc* cur = this->table->current->explodingDisc;
                    cur->clashed = false;
                    cur->clashCounter++;
                    if (this->table->current->explodingDisc->clashCounter < 3) {
                        Triplet children = cur->get_triplet();
                        this->table->remove_current();
                        this->table->push_at_current(children.child_one);
                        this->table->push_at_current(children.child_two);
                        this->table->push_at_current(children.child_three);
                    } else {
                        this->table->remove_current();
                    }
                }
            }
            this->table->advance();
        }
        timer += dT;
    }
}
void Simulation::print(double t) {
    if (t == 0) {
        cout << t << ": ";
        cout << setprecision(4) << fixed;
    }
    else{
        cout << setprecision(4) << fixed;
        cout << t << ": ";
    }
    this->table->print();
    cout << endl;
}
