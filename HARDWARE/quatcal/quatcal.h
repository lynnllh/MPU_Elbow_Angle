#ifndef __QUATCAL_H
#define __QUATCAL_H

void Quat_Product(const float *q,const float *p,float *res);
void Quat_Inv(const float *q,float *res);
void Quat_Cal_Angle(const float *q,float *ang);


#endif 

