// included by gtkcallback.inc

{
 *****************************************************************************
  This file is part of the Lazarus Component Library (LCL)

  See the file COPYING.modifiedLGPL.txt, included in this distribution,
  for details about the license.
 *****************************************************************************
}
//DRAG CALLBACK FUNCTIONS

function edit_drag_data_received(widget : pgtkWidget;
  Context : pGdkDragContext;
  X, Y : Integer;
  SelData : pGtkSelectionData;
  info : Integer;
  time : Integer;
  data : pointer) : GBoolean; cdecl;
Var
  Texts : String;
Begin
  Result:=false;
  if (Widget=nil) or (X=0) or (Y=0) or (Info=0) then exit;
  //DebugLn('Trace:***********Drag Data Received*******************');
  if Seldata^.Length > 0 then
  Begin
    Texts := StrPas(PChar(SelData^.data));
    //DebugLn('Trace:' + Texts);
    //DebugLn('Trace:0');
    TCustomEdit(Data).Caption := Texts;
    //DebugLn('Trace:1');
  end;
  gtk_drag_finish(Context,false,false,time);
end;

function edit_source_drag_data_get(widget : pgtkWidget;
  Context : pGdkDragContext;
  Selection_data : pGtkSelectionData;
  info : Integer;
  time : Integer;
  data : pointer) : GBoolean; cdecl;
var
  strTemp : PChar;
  Texts : String;
Begin
  Result:=false;
  if (Time=0) or (Context=nil) or (Widget=nil) then ;
  if (info = TARGET_ROOTWIN) then begin
    //DebugLn('Trace:I WAS DROPPED ON THE ROOTWIN')
  end
  else Begin
    //DebugLn('Trace:*********Setting Data************');
    Texts := TCustomEdit(data).Text;
    //DebugLn('Trace:0');
    strTemp := StrAlloc(length(Texts) + 1);
    try
      StrPCopy(strTemp, Texts);
      //DebugLn('Trace:1');
      gtk_selection_data_set(selection_data,selection_data^.target,
                    8,
                    {$IFDEF Gtk2}PGUChar(StrTemp){$ELSE}StrTemp{$ENDIF},
                    length(Texts)+1);
      //DebugLn('Trace:2');
    finally
      strDispose(strTemp);
    end;
    //DebugLn('Trace:3');
  end;
end;


function Edit_source_drag_data_delete (Widget: pGtkWidget;
  Context: pGdkDragContext; Data: gpointer): gBoolean ; cdecl;
begin
  if (Widget=nil) or (Context=nil) or (Data=nil) then ;
  //DebugLn('Trace:***************');
  //DebugLn('Trace:DELETE THE DATA');
  Result:=false;
end;

// included by gtkcallback.inc
