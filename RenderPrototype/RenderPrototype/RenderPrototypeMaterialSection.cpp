// RenderPrototypeMaterialSection.cpp
//

#include "stdafx.h"
#include "RenderPrototypeMaterialSection.h"
#include "RenderPrototypeMaterial.h"

#if defined (RHINO_SDK_MFC)
CRenderPrototypeMaterialSection::CRenderPrototypeMaterialSection()
	:
	CRhRdkMaterialUISection_MFC(IDD)
{
}

UUID CRenderPrototypeMaterialSection::Uuid() const
{
	// {AB6066F9-646A-4950-B534-2F6053B302D3}
	static const GUID uuid = 
	{0xab6066f9,0x646a,0x4950,{0xb5,0x34,0x2f,0x60,0x53,0xb3,0x02,0xd3}};
	return uuid;
}

void CRenderPrototypeMaterialSection::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	// TODO: Add your controls here.

//	DDX_Control(pDX, IDC_XXXX, m_xxxx);
}

BEGIN_MESSAGE_MAP(CRenderPrototypeMaterialSection, CRhRdkMaterialUISection_MFC)
END_MESSAGE_MAP()

BOOL CRenderPrototypeMaterialSection::OnInitDialog()
{
	__super::OnInitDialog();

	DisplayData();
	EnableDisableControls();

	return FALSE;
}

const wchar_t* CRenderPrototypeMaterialSection::Caption(bool bAlwaysEnglish) const
{
	UNREFERENCED_PARAMETER(bAlwaysEnglish);

	return L"RenderPrototype Material";
}

void CRenderPrototypeMaterialSection::DisplayData()
{
	CRhRdkMaterialArray a;
	GetMaterialList(a);

	if (0 == a.Count())
	{
		return;
	}

	// TODO: transfer editable material state to UI controls.
}

void CRenderPrototypeMaterialSection::EnableDisableControls()
{
	// TODO: enable and disable controls based on material state.
}
#endif
