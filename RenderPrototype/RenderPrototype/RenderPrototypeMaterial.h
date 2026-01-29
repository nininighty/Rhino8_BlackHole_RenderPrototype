// RenderPrototypeMaterial.h
//

#pragma once

// CRenderPrototypeMaterialFactory
// See RenderPrototypeMaterial.cpp for the implementation of this class.
//

class CRenderPrototypeMaterialFactory : public CRhRdkMaterialFactory
{
public:
	CRenderPrototypeMaterialFactory() = default;

protected:
	virtual CRhRdkMaterial* NewMaterial(void) const override;
};

// CRenderPrototypeMaterial
// See RenderPrototypeMaterial.cpp for the implementation of this class.
//

class CRenderPrototypeMaterial : public CRhRdkMaterial
{
public:
	CRenderPrototypeMaterial() = default;

	// CRhRdkContent overrides.
	virtual UUID TypeId(void) const override;
	virtual ON_wString TypeName(void) const override;
	virtual ON_wString TypeDescription(void) const override;
	virtual ON_wString InternalName(void) const override;
	virtual void AddUISections(IRhRdkExpandableContentUI& ui) override;
	virtual UUID RenderEngineId(void) const override;
	virtual UUID PlugInId(void) const override;
	virtual void* GetShader(const UUID& uuidRenderEngine, void* pvData) const override;
	virtual bool IsFactoryProductAcceptableAsChild(const CRhRdkContentFactory& factory, const wchar_t* wszChildSlotName) const override;
	virtual unsigned int BitFlags(void) const override;

	// CRhRdkMaterial overrides.
	virtual void SimulateMaterial(ON_Material& matOut, CRhRdkTexture::TextureGeneration tg = CRhRdkTexture::TextureGeneration::Allow,
	                              int iSimulatedTextureSize = -1, const CRhinoObject* pObject = nullptr) const override;
};
