#include "robot.hpp"
#include "lib/auto_move.hpp"

Motor left_f_mtr(7, MOTOR_GEARSET_18, reverse);
Motor left_b_mtr(6, MOTOR_GEARSET_18);
Motor right_f_mtr(4, MOTOR_GEARSET_18);
Motor right_b_mtr(5, MOTOR_GEARSET_18,reverse);

Motor collector(13, MOTOR_GEARSET_36);
Motor shoot1(12, MOTOR_GEARSET_6);
Motor shoot2(11, MOTOR_GEARSET_6, reverse);
Motor arm(14, MOTOR_GEARSET_18);

Chassis chassis({left_f_mtr, left_b_mtr}, {right_f_mtr, right_b_mtr});

Controller master(CONTROLLER_MASTER);

//configuration
bool IsCollectorOn;
bool IsCollectorReverse;

bool IsAutoShootEnabled = true;

bool IsReady;

#define SIG_STANDBY false
#define SIG_SHOOT true
bool ShootSignal = SIG_STANDBY;

ADIDigitalIn shoot_switch_a('C');
ADIDigitalIn shoot_switch_b('B');

ADIDigitalIn arm_switch('A');

bool IsAccelCompensationEnabled = false;

void reset_config()
{
    if (pros::competition::is_disabled())
    {
        IsCollectorOn = false;
        IsCollectorReverse = false;
        IsAutoShootEnabled = false;
        IsReady = false;
        IsAccelCompensationEnabled = true;

        movecnt = 0;
        memset((void *)&move_state, 0, sizeof(move_state[MAX_STEPS]));
        memset((void *)&move_start_time, 0, sizeof(move_start_time[MAX_STEPS]));
    }
    else if (pros::competition::is_autonomous())
    {

      motor_pid_s_t pid_strip = pros::c::motor_convert_pid(1.0 ,4, 2, 2); //left
      pros::c::motor_set_vel_pid(7, pid_strip);
      pros::c::motor_set_vel_pid(6, pid_strip);
      pid_strip = pros::c::motor_convert_pid(1.0 ,4, 2, 2); //right
      pros::c::motor_set_vel_pid(5, pid_strip);
      pros::c::motor_set_vel_pid(4, pid_strip);

        IsCollectorOn = false;
        IsCollectorReverse = false;
        IsAutoShootEnabled = true;
        IsReady = false;
        IsAccelCompensationEnabled = false;
    }
    else
    {
        chassis.TurningCoefficient = 0.7;
        chassis.ForwardCoefficient = 1.0;
        IsCollectorOn = false;
        IsCollectorReverse = false;
        IsAutoShootEnabled = true;
        IsReady = false;
        IsAccelCompensationEnabled = true;
    }
}
