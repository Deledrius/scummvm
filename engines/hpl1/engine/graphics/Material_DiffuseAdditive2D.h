/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 */

#ifndef HPL_MATERIAL_DIFFUSE_ADDITIVE2D_H
#define HPL_MATERIAL_DIFFUSE_ADDITIVE2D_H

#include "hpl1/engine/graphics/Material.h"

namespace hpl {

class cMaterial_DiffuseAdditive2D : public iMaterial {
public:
	cMaterial_DiffuseAdditive2D(const tString &asName, iLowLevelGraphics *apLowLevelGraphics,
								cImageManager *apImageManager, cTextureManager *apTextureManager,
								cRenderer2D *apRenderer, cGpuProgramManager *apProgramManager,
								eMaterialPicture aPicture, cRenderer3D *apRenderer3D);
	~cMaterial_DiffuseAdditive2D();

	void Compile();
	bool StartRendering(eMaterialRenderType mType, iCamera *apCam, iLight *pLight);
	void EndRendering(eMaterialRenderType mType);
	tVtxBatchFlag GetBatchFlags(eMaterialRenderType mType);
	bool NextPass(eMaterialRenderType mType);
	bool HasMultiplePasses(eMaterialRenderType mType);

	bool UsesType(eMaterialRenderType aType);

	eMaterialType GetType(eMaterialRenderType mType);
	void EditVertexes(eMaterialRenderType mType, iCamera *apCam, iLight *pLight,
					  tVertexVec *apVtxVec, cVector3f *apTransform, unsigned int alIndexAdd);

private:
};

class cMaterialType_DiffuseAdditive2D : public iMaterialType {
public:
	bool IsCorrect(tString asName) {
		if (cString::ToLowerCase(asName) == "diffadditive2d")
			return true;
		return false;
	}

	iMaterial *Create(const tString &asName, iLowLevelGraphics *apLowLevelGraphics,
					  cImageManager *apImageManager, cTextureManager *apTextureManager,
					  cRenderer2D *apRenderer, cGpuProgramManager *apProgramManager,
					  eMaterialPicture aPicture, cRenderer3D *apRenderer3D) {
		return hplNew(cMaterial_DiffuseAdditive2D, (asName, apLowLevelGraphics,
													apImageManager, apTextureManager, apRenderer,
													apProgramManager, aPicture, apRenderer3D));
	}
};

};     // namespace hpl
#endif // HPL_MATERIAL_DIFFUSE_ADDITIVE_H
