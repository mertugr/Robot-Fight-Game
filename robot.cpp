#include "robot.h"
#include <cstdlib>
#include <ctime>

Robot::Robot(int newStrength, int newHit, std::string name) : strength(newStrength), hitPoints(newHit), name(name), flag(false)
{
}

Robot::~Robot()
{
}

std::string Robot::getName()
{
    return name;
}

void Robot::setName(std::string name)
{
    this->name = name;
}


int Robot::getStrength()
{
    return strength;
}

void Robot::setStrength(int val)
{
    strength = val;
}

int Robot::getHitPoints()
{
    return hitPoints;
}

void Robot::setHitPoints(int val)
{
    this->hitPoints = val;
}

void Robot::takeDamage(int val)
{
    hitPoints -= val;
}

void Robot::setFought(bool isFought)
{
    flag = isFought;
}

bool Robot::hasFought()
{
    return flag;
}

bool Robot::isDead()
{
    return hitPoints <= 0;
}

bulldozer::bulldozer(std::string name) : Robot(50, 200, name)
{
}

std::string bulldozer::getType()
{
    return "bulldozer";
}

int bulldozer::getDamage(){
    return rand() % strength + 1;
};

roomba::roomba(std::string name) : Robot(3, 10, name)
{
}

std::string roomba::getType()
{
    return "roomba";
}

int roomba::getDamage()
{
   return (rand() % strength + 1) * 2;
}

humanic::humanic(int newStrength, int newHit, std::string name) : Robot(newStrength, newHit, name)
{
}

std::string humanic::getType() {
    return "humanic";
}

humanic::~humanic()
{
}

int humanic::getDamage()
{
    int damage = rand() % strength + 1;
    if (rand() % 100 < 10)
        damage += 50;
    return damage;
}

optimusprime::optimusprime(std::string name) : humanic(100, 100, name)
{
}

std::string optimusprime::getType()
{
    return "optimusprime";
}

int optimusprime::getDamage()
{
    return humanic::getDamage() * 2;
}

robocop::robocop(std::string name) : humanic(30, 40, name)
{
}

std::string robocop::getType()
{
    return "robocop";
}

int robocop::getDamage(){
    return humanic::getDamage();
}

kamikaze::kamikaze(std::string name) : Robot(10,10,name) {}

std::string kamikaze:: getType() {
        return "kamikaze";
    }

int kamikaze::getDamage() {
        int damage = hitPoints;
        return damage;
    }
