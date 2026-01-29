// RenderPrototypeRdkPlugIn.h
//

#pragma once

// CRenderPrototypeRdkRenderPlugIn
// See RenderPrototypeRdkPlugIn.cpp for the implementation of this class.
//

class CRenderPrototypeRdkPlugIn : public CRhRdkRenderPlugIn
{
public:
	CRenderPrototypeRdkPlugIn() = default;

	virtual bool Initialize() override;
	virtual void Uninitialize() override;

	virtual UUID PlugInId() const override;

	virtual void AbortRender() override;

	CRhinoPlugIn& RhinoPlugIn() const override;

protected:
	virtual void RegisterExtensions() const override;

	// Preview renderers
	virtual bool CreatePreview(const ON_2iSize& sizeImage, RhRdkPreviewQuality quality, const IRhRdkPreviewSceneServer* pSceneServer, IRhRdkPreviewCallbacks* pNotify, CRhinoDib& dibOut) override;
	virtual bool CreatePreview(const ON_2iSize& sizeImage, const CRhRdkTexture& texture, CRhinoDib& dibOut) override;

	virtual bool SupportsFeature(const UUID& uuidFeature) const override;
};
