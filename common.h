#ifndef COMMON_H
#define COMMON_H
#include "settingobject.h"
#include "hole.h"
#include "dxfview.h"
#include <qmath.h>


#ifndef GLOBALS
#define GLOBALS
   extern settingobject *setobj;
#else
   settingobject *setobj;



#endif //setobj

   /*计算脉冲的函数*/
 extern  int stepPulses(double displacement,double lead,double stepangle);
 /*计算速度转化脉冲函数*/
 extern int speedPulses(double speed,double lead,double stepangle);
class CompLessX
 {
 public:
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         return pstItem1->hx < pstItem2->hx;
     }
 };


class CompGreaterX
 {
 public:
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         return pstItem1->hx > pstItem2->hx;
     }
 };

class CompLessY
 {
 public:
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         return pstItem1->hy < pstItem2->hy;
     }
 };


class CompGreaterY
 {
 public:
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         return pstItem1->hy > pstItem2->hy;
     }
 };
class CompGreaterYX
 {
 public:
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         if (pstItem1->hy < pstItem2->hy)
         {
             return true;
         }
         else
         {
             if (pstItem1->hy== pstItem2->hy)
             {
                 return pstItem1->hx < pstItem2->hx;
             }
             else
             {
                 return false;
             }
         }


     }
 };
class CompTwoHole
 {
private:
    Hole* firstItem;
 public:
    CompTwoHole(Hole* hole):firstItem(hole){};
     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
     {
         return sqrt((pow((pstItem1->hx-firstItem->hx),2)
                      +pow((pstItem1->hy-firstItem->hy),2)))<
                 sqrt((pow((pstItem2->hx-firstItem->hx),2)
                       +pow((pstItem2->hy-firstItem->hy),2)));
     }
 };
#endif // COMMON_H
