pros::lcd::print(1, "Auto: new_back_blue");

<<<<<<< HEAD


//后退翻盘
_set_movement_warm(127,-1200,-1200,2000);
=======
// go back to the wall and face the plate
_set_movement_warm(127,-1800,-1800,2000);
>>>>>>> 77d7acdabfcf389f2858c23679c03c365f427427
_set_movement(100,-680,600,600);
_set_onetime_task(0,_arm_down);
_set_onetime_task(600,chassis.Drive(-60,0));
_set_onetime_task(0, chassis.Drive(0,0));
_set_movement_warm(80, 2450, 2450, 3000);
_set_onetime_task(0,_arm_up);
_set_movement(127,200,200,300);
//_set_onetime_task(0,collector.move(110))
_set_movement_warm(100, -1300, -1300, 2000);
//_set_onetime_task(200, );
//_set_onetime_task(0,collector.move(0))

<<<<<<< HEAD
//推盘吸球
_set_movement(100,270,-270,400);
=======
//turn and face the another plate
_set_movement(100,250,-250,400);
>>>>>>> 77d7acdabfcf389f2858c23679c03c365f427427
_set_onetime_task(0,_arm_down);
_set_onetime_task(0,collector.move(110));

//slowly straight and fetch the ball
_set_movement_warm(60,2500,2500,2500);
_set_delayed_task(400,collector.move(0));
_set_movement_warm(60,-800,-800,900);
_set_onetime_task(0,_arm_back);

<<<<<<< HEAD
//撞台打旗
_set_movement(100,400,-400,500);
_set_onetime_task(800,chassis.Drive(80,0))
_set_onetime_task(0,chassis.Drive(0,0));
_set_movement(60,-640,0,900);//第一列旗角度
_set_onetime_task(0,collector.move(-80));
_set_onetime_task(300,ShootSignal = SIG_SHOOT);//高旗
=======
//turn and correct the angle
_set_movement(100,400,-400,500);
_set_onetime_task(800,chassis.Drive(80,0))
_set_onetime_task(0,chassis.Drive(0,0));

//turn an shoot the high flag
_set_movement(60,-650,0,900);
//_set_onetime_task(200,collector.move(-110));
_set_onetime_task(300,ShootSignal = SIG_SHOOT);
>>>>>>> 77d7acdabfcf389f2858c23679c03c365f427427
_set_onetime_task(0,collector.move(110));

//go back and shoot the middle flag
_set_movement_warm(100,-1230,-1230,1500);
//_set_onetime_task(100, );
_set_onetime_task(250,collector.move(0));
<<<<<<< HEAD
_set_onetime_task(100,ShootSignal = SIG_SHOOT);//低旗
=======
_set_onetime_task(100,ShootSignal = SIG_SHOOT);

//correct the angle at the middle spuare
>>>>>>> 77d7acdabfcf389f2858c23679c03c365f427427
_set_movement_warm(100,1100,1100,1500);
_set_movement(100,650,0,900);

//go on
_set_onetime_task(1200,chassis.Drive(127,0));
_set_movement(10,-10,-10,50);
