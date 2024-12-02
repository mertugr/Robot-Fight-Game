#include "robot.h"
#include "grid.h"
#include <iostream>
#include <ctime>

struct Direction {
    int setX,setY;
};

void printHitMessage(Robot* attacker, Robot* victim, int damage) {
    std::cout<<attacker->getName()<<" ("<<attacker->getHitPoints()<<") "<<"hits "<<victim->getName()<<" ("<<victim->getHitPoints()+damage<<") "<<"with "<<damage<<std::endl;
    std::cout<<"The new hitpoints of "<<victim->getName()<<" is "<<victim->getHitPoints()<<std::endl;
    if (victim->isDead())
        std::cout<<victim->getName()<<" died"<<std::endl;
}

void duel(Robot* attacker, Robot* victim){
    //this if for when attacker is kamikaze
    if(attacker->getType()=="kamikaze"){
            int attackerDamage = attacker->getDamage();
            victim->takeDamage(attackerDamage);
            printHitMessage(attacker, victim, attackerDamage);
            attacker->setHitPoints(0); //kamikaze kills itself
            std::cout<<attacker->getName()<<" died"<<std::endl;
            while (victim->isDead()){
                  break;
            }
    }
    while (!attacker->isDead() && !victim->isDead()) {
        int attackerDamage = attacker->getDamage();
        victim->takeDamage(attackerDamage);
        printHitMessage(attacker, victim, attackerDamage);
        if (victim->isDead())
            break;
        if(attacker->isDead()){ //just for checking if kamikaze attacked and dead
            std::cout<<attacker->getName()<<" died"<<std::endl;
            break;
        }
        int victimDamage = victim->getDamage();
        attacker->takeDamage(victimDamage);
        printHitMessage(victim, attacker, victimDamage);
    }
}

int main()
{
    std::srand(time(nullptr));
    size_t grid_height = 10;
    size_t grid_width = 10;
    size_t initial_count = 6; // 0,1,2,3,4,5 for each robot
    size_t total_count = initial_count * 5; // 5 type of robots

    Grid grid(grid_height, grid_width);

    Robot** robots = new Robot * [total_count];
    size_t counter = 0;
//creating robots
    for (size_t i = 0; i < initial_count; i++) {
        robots[counter++] = new robocop("robocop_" + std::to_string(i));
    }

    for (size_t i = 0; i < initial_count; i++) {
        robots[counter++] = new bulldozer("bulldozer_" + std::to_string(i));
    }

    for (size_t i = 0; i < initial_count; i++) {
        robots[counter++] = new roomba("roomba_" + std::to_string(i));
    }

    for (size_t i = 0; i < initial_count; i++) {
        robots[counter++] = new optimusprime("optimusprime_" + std::to_string(i));
    }

    for (size_t i = 0; i < initial_count; i++) {
        robots[counter++] = new kamikaze("kamikaze_" + std::to_string(i));
    }

    for (size_t i = 0; i < total_count; i++) {
        auto randX = rand() % grid.getWidth();
        auto randY = rand() % grid.getHeight();

        auto cell = grid.getCell(randX, randY);

        if (cell->robot) {
            i--;
            continue;
        }
//adding robots to grid
        cell->robot = robots[i];
    }
    //definig directions
    Direction directions[4];
    directions[0] = { 0, 1 };   // up
    directions[1] = { 0, -1 };  // down
    directions[2] = { -1, 0 };  // left
    directions[3] = { 1, 0 };   // right

    int aliveCount = 0;
    do {
        for (size_t y = 0; y < grid.getHeight(); y++) {
            for (size_t x = 0; x < grid.getWidth(); x++) {
                auto cell = grid.getCell(x, y);
                if (!cell->robot || cell->robot->hasFought())
                    continue;

                Robot* attacker = cell->robot;
                Cell* victimCell = nullptr;
                size_t newX = x, newY = y;
                while (true) {
                    Direction& dir = directions[rand() % 4];
                    size_t new_x = newX + dir.setX;
                    size_t new_y = newY + dir.setY;

                    victimCell = grid.getCell(new_x, new_y);

                    if (victimCell) {
                        newX = new_x;
                        newY = new_y;
                        if (victimCell->robot)
                            break;

                        cell->robot = nullptr;
                        cell = victimCell;
                        cell->robot = attacker;
                    }
                }
                duel(cell->robot, victimCell->robot);

                if (cell->robot->isDead()) {
                    cell->robot = nullptr; // deleting it if attacker is dead
                    victimCell->robot->setFought(true);
                }
                else if (victimCell->robot->isDead()) {
                    victimCell->robot = nullptr;
                    cell->robot->setFought(true);
                }
            }
        }

        aliveCount = 0;
        for (size_t i = 0; i < total_count; i++) {
            robots[i]->setFought(false);

            aliveCount += !robots[i]->isDead();
        }

    } while (aliveCount != 1); // loop until only one or zero robot left.

    for (size_t i = 0; i < total_count; i++) {
        if (!robots[i]->isDead())
            std::cout<<robots[i]->getName()<<" stands alive"<<std::endl;
    }
    for (size_t i = 0; i < total_count; i++)
        delete robots[i];

    delete[] robots;
    return 0;
}
