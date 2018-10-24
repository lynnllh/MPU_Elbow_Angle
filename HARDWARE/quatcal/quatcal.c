#include "quatcal.h"
#include "math.h"


void Quat_Product(const float *q,const float *p,float *res)
{
	res[0] = q[0]*p[0] - q[1]*p[1] - q[2]*p[2] - q[3]*p[3];
	res[1] = q[0]*p[1] + q[1]*p[0] + q[2]*p[3] - q[3]*p[2];
	res[2] = q[0]*p[2] - q[1]*p[3] + q[2]*p[0] + q[3]*p[1];
	res[3] = q[0]*p[3] + q[1]*p[2] - q[2]*p[1] + q[3]*p[0];
}

void Quat_Inv(const float *q,float *res)
{
	float sosq;
	sosq = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
	res[0] =  q[0]/sosq;
	res[1] = -q[1]/sosq;
	res[2] = -q[2]/sosq;
	res[3] = -q[3]/sosq;
	
}

void Quat_Cal_Angle(const float *q,float *ang)
{
	//printf("%f   ",q[0]);
	*ang=2.0f*acos(q[0]);
	*ang=*ang*57.29578049f;
}
