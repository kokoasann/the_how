#include "stdafx.h"
#include "pointPR.h"


pointPR::pointPR()
{
}
pointPR::~pointPR()
{
}

void pointPR::addPOINT()
{
	POINT++;
}

void pointPR::ChainStop()
{
	POINT = 0;
}