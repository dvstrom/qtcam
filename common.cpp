#include "common.h"
#include <math.h>


settingobject *setobj=new settingobject();
/*
 *displacement :需要移动距离
 *lead:导程
 **stepangle:步距角
 **返回：移动该距离需要的脉冲数
 **/
int stepPulses(double displacement,double lead,double stepangle)
{
    int steppulses;
    steppulses=displacement*360/(lead*stepangle);
    return steppulses;
 }
/*
 *speed:给定速度，单位m/s。函数内转化为mm/s
 *lead:导程
 *stepangle：步距角
 *返回：速度转化为脉冲数
 **/
int speedPulses(double speed,double lead,double stepangle)
{
    int speedpulses;
    speedpulses=(speed*1000*360/lead*60*stepangle);
    return speedpulses;
}
