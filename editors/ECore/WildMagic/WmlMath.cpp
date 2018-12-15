// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2004.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.
#include "stdafx.h"
#pragma hdrstop

#include "WmlMath.h"
//using namespace Wml;

template<> const float Wml::Math<float>::EPSILON = FLT_EPSILON;
template<> const float Wml::Math<float>::ZERO_TOLERANCE = 1e-06f;
template<> const float Wml::Math<float>::MAX_REAL = flt_max;//.FLT_MAX;
template<> const float Wml::Math<float>::_PI = (float)(4.0*atan(1.0));
template<> const float Wml::Math<float>::TWO_PI = 2.0f*Wml::Math<float>::_PI;
template<> const float Wml::Math<float>::HALF_PI = 0.5f*Wml::Math<float>::_PI;
template<> const float Wml::Math<float>::INV_PI = 1.0f/Wml::Math<float>::_PI;
template<> const float Wml::Math<float>::INV_TWO_PI = 1.0f/Wml::Math<float>::TWO_PI;
template<> const float Wml::Math<float>::DEG_TO_RAD = Wml::Math<float>::_PI/180.0f;
template<> const float Wml::Math<float>::RAD_TO_DEG = 180.0f/Wml::Math<float>::_PI;

template<> const double Wml::Math<double>::EPSILON = DBL_EPSILON;
template<> const double Wml::Math<double>::ZERO_TOLERANCE = 1e-08;
template<> const double Wml::Math<double>::MAX_REAL = DBL_MAX;
template<> const double Wml::Math<double>::_PI = 4.0*atan(1.0);
template<> const double Wml::Math<double>::TWO_PI = 2.0*Wml::Math<double>::_PI;
template<> const double Wml::Math<double>::HALF_PI = 0.5*Wml::Math<double>::_PI;
template<> const double Wml::Math<double>::INV_PI = 1.0/Wml::Math<double>::_PI;
template<> const double Wml::Math<double>::INV_TWO_PI = 1.0/Wml::Math<double>::TWO_PI;
template<> const double Wml::Math<double>::DEG_TO_RAD = Wml::Math<double>::_PI/180.0;
template<> const double Wml::Math<double>::RAD_TO_DEG = 180.0/Wml::Math<double>::_PI;

namespace Wml
{
template WML_ITEM class Math<float>;
template WML_ITEM class Math<double>;
};

