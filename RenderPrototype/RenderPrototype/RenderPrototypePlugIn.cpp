// RenderPrototypePlugIn.cpp : defines the initialization routines for the plug-in.
//插件的逻辑实现

#include "stdafx.h"
#include "rhinoSdkPlugInDeclare.h"
#include "RenderPrototypePlugIn.h"
#include "Resource.h"
#include "RenderPrototypeRdkPlugIn.h"
#include "RenderPrototypeSdkRender.h"

// The plug-in object must be constructed before any plug-in classes derived
// from CRhinoCommand. The #pragma init_seg(lib) ensures that this happens.
#pragma warning(push)
#pragma warning(disable : 4073)
#pragma init_seg(lib)
#pragma warning(pop)

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
// Provide a short, friendly name for this plug-in.
RHINO_PLUG_IN_NAME(L"RenderPrototype");

// Rhino plug-in id
// Provide a unique uuid for this plug-in.
RHINO_PLUG_IN_ID(L"CD107BF1-94E8-4FC0-B5CE-735DF1942A6D");

// Rhino plug-in version
// Provide a version number string for this plug-in.
RHINO_PLUG_IN_VERSION(__DATE__ "  " __TIME__)

// Rhino plug-in description
// Provide a description of this plug-in.
RHINO_PLUG_IN_DESCRIPTION(L"RenderPrototype plug-in for Rhinoceros®");

// Rhino plug-in icon resource id
// Provide an icon resource this plug-in.
// Icon resource should contain 16, 24, 32, 48, and 256-pixel image sizes.
RHINO_PLUG_IN_ICON_RESOURCE_ID(IDI_ICON);

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations with
// your company information. Note, all of these declarations
// must be present or your plug-in will not load.
//
// When completed, delete the following #error directive.
//#error Developer declarations block is incomplete!
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION(L"Nighty");
RHINO_PLUG_IN_DEVELOPER_ADDRESS(L"Andromeda");
RHINO_PLUG_IN_DEVELOPER_COUNTRY(L"Andromeda");
RHINO_PLUG_IN_DEVELOPER_PHONE(L"no");
RHINO_PLUG_IN_DEVELOPER_FAX(L"no");
RHINO_PLUG_IN_DEVELOPER_EMAIL(L"no");
RHINO_PLUG_IN_DEVELOPER_WEBSITE(L"http://nininighty.xin/");
RHINO_PLUG_IN_UPDATE_URL(L"no");

// The one and only CRenderPrototypePlugIn object
static class CRenderPrototypePlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CRenderPrototypePlugIn definition

CRenderPrototypePlugIn& RenderPrototypePlugIn()
{
	// Return a reference to the one and only CRenderPrototypePlugIn object
	return thePlugIn;
}

CRenderPrototypePlugIn::CRenderPrototypePlugIn()
{
	// Description:
	//   CRenderPrototypePlugIn constructor. The constructor is called when the
	//   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
	//   is loaded, CRenderPrototypePlugIn::OnLoadPlugIn() is called. The
	//   constructor should be simple and solid. Do anything that might fail in
	//   CRenderPrototypePlugIn::OnLoadPlugIn().

	// TODO: Add construction code here
	m_plugin_version = RhinoPlugInVersion();
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CRenderPrototypePlugIn::PlugInName() const
{
	// Description:
	//   Plug-in name display string.  This name is displayed by Rhino when
	//   loading the plug-in, in the plug-in help menu, and in the Rhino
	//   interface for managing plug-ins.

	// TODO: Return a short, friendly name for the plug-in.
	return RhinoPlugInName();
}

const wchar_t* CRenderPrototypePlugIn::PlugInVersion() const
{
	// Description:
	//   Plug-in version display string. This name is displayed by Rhino
	//   when loading the plug-in and in the Rhino interface for managing
	//   plug-ins.

	// TODO: Return the version number of the plug-in.
	return m_plugin_version;
}

GUID CRenderPrototypePlugIn::PlugInID() const
{
	// Description:
	//   Plug-in unique identifier. The identifier is used by Rhino to
	//   manage the plug-ins.

	// TODO: Return a unique identifier for the plug-in.
	// {CD107BF1-94E8-4FC0-B5CE-735DF1942A6D}
	return ON_UuidFromString(RhinoPlugInId());
}

/////////////////////////////////////////////////////////////////////////////
// Additional overrides

BOOL CRenderPrototypePlugIn::OnLoadPlugIn()
{
	// Description:
	//   Called after the plug-in is loaded and the constructor has been
	//   run. This is a good place to perform any significant initialization,
	//   license checking, and so on.  This function must return TRUE for
	//   the plug-in to continue to load.

	// Remarks:
	//    Plug-ins are not loaded until after Rhino is started and a default document
	//    is created.  Because the default document already exists
	//    CRhinoEventWatcher::On????Document() functions are not called for the default
	//    document.  If you need to do any document initialization/synchronization then
	//    override this function and do it here.  It is not necessary to call
	//    CPlugIn::OnLoadPlugIn() from your derived class.

	// If this assert fires, it's likely that the RDK has not yet been loaded by Rhino.
	// This can happen if you load your plug-in first, before the debug RDK and for some
	// reason it actually manages to find rdk.rhp on the search path. If this happens,
	// load protect your plug-in, restart Rhino and and load rdk.rhp using drag and drop
	// or the plug-in manager. Then un-load protect your plug-in.
	ASSERT(RhRdkIsAvailable());

	// TODO: Add render plug-in initialization code here.

	m_pRdkPlugIn = new CRenderPrototypeRdkPlugIn;
	ON_wString str;
	if (!m_pRdkPlugIn->Initialize())
	{
		delete m_pRdkPlugIn;
		m_pRdkPlugIn = nullptr;
		str.Format(L"Failed to load %s, version %s. RDK initialization failed\n", PlugInName(), PlugInVersion());
		RhinoApp().Print(str);
		return FALSE;
	}

	str.Format(L"Loading %s, version %s\n", PlugInName(), PlugInVersion());
	RhinoApp().Print(str);

	return TRUE;
}


void CRenderPrototypePlugIn::OnUnloadPlugIn()
{
	// Description:
	//    Called one time when plug-in is about to be unloaded. By this time,
	//    Rhino's mainframe window has been destroyed, and some of the SDK
	//    managers have been deleted. There is also no active document or active
	//    view at this time. Thus, you should only be manipulating your own objects.
	//    or tools here.

	// TODO: Add render plug-in clean-up code here.
	m_event_watcher.Enable(FALSE);
	m_event_watcher.UnRegister();
}

/////////////////////////////////////////////////////////////////////////////
// Render overrides

CRhinoCommand::result CRenderPrototypePlugIn::Render(const CRhinoCommandContext& context, bool bPreview)
{
	// Description:
	//   Called by the Render and RenderPreview commands if this application is both
	//   a Render plug-in and is set as the default render engine.
	// Parameters:
	//   context [in] Command parameters passed to the render command.
	//   bPreview [in] If true, a faster, lower quality rendering is expected.

	const auto pDoc = context.Document();
	if (nullptr == pDoc)
		return CRhinoCommand::failure; 

	CRenderPrototypeSdkRender render(context, *this, L"[RenderPrototype", IDI_RENDER, bPreview);
	const auto size = render.RenderSize(*pDoc, true);
	if (CRhinoSdkRender::render_ok != render.Render(size))
		return CRhinoCommand::failure;

	return CRhinoCommand::success;
}

CRhinoCommand::result CRenderPrototypePlugIn::RenderWindow(
	const CRhinoCommandContext& context,
	bool render_preview,
	CRhinoView* view,
	const LPRECT rect,
	bool bInWindow,
	bool bBlowUp
)
{
	UNREFERENCED_PARAMETER(bBlowUp);

	// Description:
	//   Called by Render command if this application is both
	//   a Render plug-in and is set as the default render engine.
	// Parameters:
	//   context [in] Command parameters passed to the render command.
	//   bPreview [in] If true, a faster, lower quality rendering is expected.
	//   view [in] View to render.
	//   rect [in] Rectangle to render in viewport window coordinates.

	CRenderPrototypeSdkRender render(context, *this, L"RenderPrototype", IDI_RENDER, render_preview);
	if (CRhinoSdkRender::render_ok == render.RenderWindow(view, rect, bInWindow))
		return CRhinoCommand::success;

	return CRhinoCommand::failure;
}

CRhinoCommand::result CRenderPrototypePlugIn::RenderQuiet(const CRhinoCommandContext& context, bool bPreview)
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(bPreview);

	return CRhinoCommand::failure;
}

BOOL CRenderPrototypePlugIn::SaveRenderedImage(ON_wString filename)
{
	// Description:
	//   Message sent from a script to save the rendering to a file.
	// Parameters:
	//   filename [in] The name of file to save.

	// TODO: Add file saving code here.
	return FALSE;
}

BOOL CRenderPrototypePlugIn::CloseRenderWindow()
{
	// Description:
	//   Close render window notification. Called when rendering is done and render window
	//   is no longer modal. (When RenderCommand returns if you leave the window up)

	return FALSE;
}

// Render methods

UINT CRenderPrototypePlugIn::MainFrameResourceID() const
{
	return IDR_RENDER;
}

BOOL CRenderPrototypePlugIn::SceneChanged() const
{
	return m_event_watcher.RenderSceneModified();
}

void CRenderPrototypePlugIn::SetSceneChanged(BOOL bChanged)
{
	m_event_watcher.SetRenderMeshFlags(bChanged);
	m_event_watcher.SetMaterialFlags(bChanged);
}

BOOL CRenderPrototypePlugIn::LightingChanged() const
{
	return m_event_watcher.RenderLightingModified();
}

void CRenderPrototypePlugIn::SetLightingChanged(BOOL bChanged)
{
	m_event_watcher.SetLightFlags(bChanged);
}



