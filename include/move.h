#include <arduino.h>
class motorController
{
private:
/* data */
#define spdL 5 // speed of left motor
#define spdR 6 // speed of right motor
#define dirL 8 // direction of right motor
#define dirR 7 // direction of left motor
#define stby 3 // standby pin enables motors

public:
    void forward();
    void left();
    void right();
    void stop();
    void backward();
    void setupPins();
#define speedMax 255
    motorController(/* args */);
    ~motorController();
};

motorController::motorController(/* args */)
{
}

motorController::~motorController()
{
}
