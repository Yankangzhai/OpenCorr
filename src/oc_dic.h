/*
 * This file is part of OpenCorr, an open source C++ library for
 * study and development of 2D, 3D/stereo and volumetric
 * digital image correlation.
 *
 * Copyright (C) 2021, Zhenyu Jiang <zhenyujiang@scut.edu.cn>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one from http://mozilla.org/MPL/2.0/.
 *
 * More information about OpenCorr can be found at https://www.opencorr.org/
 */

#pragma once

#ifndef _DIC_H_
#define _DIC_H_

#include "oc_array.h"
#include "oc_image.h"
#include "oc_poi.h"
#include "oc_subset.h"

namespace opencorr
{
	class DIC
	{
	public:
		Image2D* ref_img = nullptr;
		Image2D* tar_img = nullptr;

		int subset_radius_x, subset_radius_y;
		int thread_number; //OpenMP thread number

		DIC();
		virtual ~DIC() = default;

		void setImages(Image2D& ref_img, Image2D& tar_img);
		void setSubsetRadii(int radius_x, int radius_y);

		virtual void prepare();
		virtual void compute(POI2D* poi) = 0;
		virtual void compute(std::vector<POI2D>& poi_queue) = 0;

	};

}//namespace opencorr

#endif //_DIC_H_
