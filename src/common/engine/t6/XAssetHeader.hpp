#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/Font_s.hpp"
#include "engine/t6/FontIcon.hpp"
#include "engine/t6/GfxImage.hpp"
#include "engine/t6/RawFile.hpp"
#include "engine/t6/XModelPieces.hpp"

namespace t6 {
	union XAssetHeader {
		XModelPieces* xmodel_pieces_;
		/*PhysPreset* physPreset;
		PhysConstraints* physConstraints;
		DestructibleDef* destructibleDef;
		XAnimParts* parts;*/
		XModel* model_;
		Material* material_;
		/*MaterialPixelShader* pixelShader;
		MaterialVertexShader* vertexShader;
		MaterialTechniqueSet* techniqueSet;*/
		GfxImage* image_;
		/*SndBank* sound;
		SndPatch* soundPatch;
		clipMap_t* clipMap;
		ComWorld* comWorld;
		GameWorldSp* gameWorldSp;
		GameWorldMp* gameWorldMp;
		MapEnts* mapEnts;
		GfxWorld* gfxWorld;
		GfxLightDef* lightDef;*/
		Font_s* font_;
		FontIcon* font_icon_;
		/*MenuList* menuList;
		menuDef_t* menu;
		LocalizeEntry* localize;
		WeaponVariantDef* weapon;
		WeaponAttachment* attachment;
		WeaponAttachmentUnique* attachmentUnique;
		WeaponCamo* weaponCamo;
		SndDriverGlobals* sndDriverGlobals;
		const FxEffectDef* fx;
		FxImpactTable* impactFx;*/
		RawFile* raw_file_;
		/*StringTable* stringTable;
		LeaderboardDef* leaderboardDef;
		XGlobals* xGlobals;
		ddlRoot_t* ddlRoot;
		Glasses* glasses;
		TextureList* textureList;
		EmblemSet* emblemSet;
		ScriptParseTree* scriptParseTree;
		KeyValuePairs* keyValuePairs;
		VehicleDef* vehicleDef;
		MemoryBlock* memoryBlock;
		AddonMapEnts* addonMapEnts;
		TracerDef* tracerDef;
		SkinnedVertsDef* skinnedVertsDef;
		Qdb* qdb;
		Slug* slug;
		FootstepTableDef* footstepTableDef;
		FootstepFXTableDef* footstepFXTableDef;
		ZBarrierDef* zbarrierDef;*/
		void* data_;
	};
}
