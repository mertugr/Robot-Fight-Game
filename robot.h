#ifndef ROBOT_H
#define ROBOT_H
#include <string>

class Robot {
protected:
    std::string name;
    bool flag;
    int strength;
    int hitPoints;
public:
    Robot(int newStrength, int newHit, std::string name);
    virtual ~Robot();
    std::string getName();
    void setName(std::string);
    virtual std::string getType()=0;
    void setType(int newType);
    int getStrength();
    void setStrength(int);
    int getHitPoints();
    void setHitPoints(int);
    virtual int getDamage()=0;
    void takeDamage(int);
    void setFought(bool);
    bool hasFought();
    bool isDead();
};

class bulldozer : public Robot {
public:
    bulldozer(std::string name);
    std::string getType() override;
    int getDamage() override;
};

class roomba : public Robot {
public:
    roomba(std::string name);
    std::string getType() override;
    int getDamage() override;
};

class humanic : public Robot {
public:
    humanic(int newStrength, int newHit, std::string name);
    std::string getType() override;
    virtual ~humanic();
    int getDamage() override;
};

class optimusprime : public humanic {
public:
    optimusprime(std::string name);
    std::string getType() override;
    int getDamage() override;
};

class robocop : public humanic {
public:
    robocop(std::string name);
    std::string getType() override;
    int getDamage() override;
};

class kamikaze : public Robot {
public:
    kamikaze(std::string name);
    std::string getType() override;
    int getDamage() override;
};

#endif
