// cmdRenderPrototype.cpp : command file
//

#include "stdafx.h"
#include "RenderPrototypePlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN RenderPrototype command
//

#pragma region RenderPrototype command

// Do NOT put the definition of class CCommandRenderPrototype in a header
// file. There is only ONE instance of a CCommandRenderPrototype class
// and that instance is the static theRenderPrototypeCommand that appears
// immediately below the class definition.

class CCommandRenderPrototype : public CRhinoCommand
{
public:
  // The one and only instance of CCommandRenderPrototype is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandRenderPrototype::CCommandRenderPrototype()
  // is called exactly once when static theRenderPrototypeCommand is created.
  CCommandRenderPrototype() = default;

  // CCommandRenderPrototype::~CCommandRenderPrototype()
  // is called exactly once when static theRenderPrototypeCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandRenderPrototype() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {EC05C999-0795-4573-BAD2-C409A8A74063}
    static const GUID RenderPrototypeCommand_UUID = 
    {0xec05c999,0x0795,0x4573,{0xba,0xd2,0xc4,0x09,0xa8,0xa7,0x40,0x63}};
    return RenderPrototypeCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"RenderPrototype"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandRenderPrototype object
// Do NOT create any other instance of a CCommandRenderPrototype class.
static class CCommandRenderPrototype theRenderPrototypeCommand;

CRhinoCommand::result CCommandRenderPrototype::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandRenderPrototype::RunCommand() is called when the user
  // runs the "RenderPrototype".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.

  ON_wString str;
  str.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, RenderPrototypePlugIn().PlugInName(), MB_OK);
  else
    RhinoApp().Print(pszStr);

  // TODO: Return one of the following values:
  //   CRhinoCommand::success:  The command worked.
  //   CRhinoCommand::failure:  The command failed because of invalid input, inability
  //                            to compute the desired result, or some other reason
  //                            computation reason.
  //   CRhinoCommand::cancel:   The user interactively canceled the command 
  //                            (by pressing ESCAPE, clicking a CANCEL button, etc.)
  //                            in a Get operation, dialog, time consuming computation, etc.

  return CRhinoCommand::success;
}

#pragma endregion

//
// END RenderPrototype command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
