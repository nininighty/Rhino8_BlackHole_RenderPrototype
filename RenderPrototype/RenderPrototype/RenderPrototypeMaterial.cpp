// RenderPrototypeMaterial.cpp
//

#include "stdafx.h"
#include "RenderPrototypeMaterial.h"
#include "RenderPrototypeMaterialSection.h"
#include "RenderPrototypePlugIn.h"

CRhRdkMaterial* CRenderPrototypeMaterialFactory::NewMaterial() const
{
	return new CRenderPrototypeMaterial();
}

UUID CRenderPrototypeMaterial::RenderEngineId() const
{
	return ::RenderPrototypePlugIn().PlugInID();
}

UUID CRenderPrototypeMaterial::PlugInId() const
{
	return ::RenderPrototypePlugIn().PlugInID();
}

UUID CRenderPrototypeMaterial::TypeId() const
{
	// {8EA205B1-2881-4060-B10C-4086CDEDA80F}
	static const GUID RenderPrototypeMaterial_UUID = 
	{0xf31c1e52,0x8156,0x44db,{0xb9,0x12,0xf,0x86,0xb8,0x76,0x6e,0x78}};
	return RenderPrototypeMaterial_UUID;
}

ON_wString CRenderPrototypeMaterial::TypeName() const
{
	// TODO: Return the user-friendly type name of the material.
	return L"RenderPrototype Material";
}

ON_wString CRenderPrototypeMaterial::TypeDescription() const
{
	// TODO: Return a description of the material.
	return "Demo material for RenderPrototype";
}

ON_wString CRenderPrototypeMaterial::InternalName() const
{
	// TODO: Return the material's internal name (not usually seen by the user).
	return L"your-unique-material-name-goes-here";
}

void CRenderPrototypeMaterial::SimulateMaterial(ON_Material& matOut, CRhRdkTexture::TextureGeneration tg, int iSimulatedTextureSize, const CRhinoObject* pObject) const
{
	// TODO: Set up the ON_Material based on your material state so that it looks as much
	//       as possible like your material will look when it is rendered.
	UNREFERENCED_PARAMETER(matOut);
	UNREFERENCED_PARAMETER(tg);
	UNREFERENCED_PARAMETER(iSimulatedTextureSize);
	UNREFERENCED_PARAMETER(pObject);
}

void CRenderPrototypeMaterial::AddUISections(IRhRdkExpandableContentUI& ui)
{
#if defined (RHINO_SDK_MFC)
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ui.AddSection(new CPlugIn1MaterialSection);
#endif

	AddAutomaticUISection(ui, L"Parameters", L"Parameters");

	// TODO: Add any further UI sections.

	__super::AddUISections(ui);
}

void* CRenderPrototypeMaterial::GetShader(const UUID& uuidRenderEngine, void* pvData) const
{
	UNREFERENCED_PARAMETER(pvData);

	if (!IsCompatible(uuidRenderEngine))
		return nullptr;

	void* pShader = nullptr;

	// TODO: Get a pointer to the shader used to render this material.

	return pShader;
}

bool CRenderPrototypeMaterial::IsFactoryProductAcceptableAsChild(const CRhRdkContentFactory& factory, const wchar_t* wszChildSlotName) const
{
	// TODO: Determine if pFactory produces content suitable as a child for a particular child slot.
	//       If so, return true, otherwise return false.
	UNREFERENCED_PARAMETER(factory);
	UNREFERENCED_PARAMETER(wszChildSlotName);

	return false;
}

unsigned int CRenderPrototypeMaterial::BitFlags() const
{
	auto flags = __super::BitFlags();

	flags &= ~bfTextureSummary; // No texture summary required.

	// TODO: Modify flags to customize how RDK uses your material.

	return flags;
}
