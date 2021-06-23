/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


// Description : Utility classes used by Editor.


#pragma once

#include <Cry_Color.h>

class QColor;

QColor ColorLinearToGamma(ColorF col);
ColorF ColorGammaToLinear(const QColor& col);
QColor ColorToQColor(uint32 color);

