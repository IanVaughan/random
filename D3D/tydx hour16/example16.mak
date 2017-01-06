# Microsoft Developer Studio Generated NMAKE File, Based on example16.dsp
!IF "$(CFG)" == ""
CFG=example16 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to example16 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "example16 - Win32 Release" && "$(CFG)" != "example16 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "example16.mak" CFG="example16 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "example16 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "example16 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "example16 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\example16.exe"


CLEAN :
	-@erase "$(INTDIR)\Car.obj"
	-@erase "$(INTDIR)\Cube.obj"
	-@erase "$(INTDIR)\d3dmath.obj"
	-@erase "$(INTDIR)\d3dtextr.obj"
	-@erase "$(INTDIR)\d3dutil.obj"
	-@erase "$(INTDIR)\example16.obj"
	-@erase "$(INTDIR)\example16.pch"
	-@erase "$(INTDIR)\Helicopter.obj"
	-@erase "$(INTDIR)\Obj.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\example16.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\example16.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\example16.pdb" /machine:I386 /out:"$(OUTDIR)\example16.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Car.obj" \
	"$(INTDIR)\Cube.obj" \
	"$(INTDIR)\d3dmath.obj" \
	"$(INTDIR)\d3dtextr.obj" \
	"$(INTDIR)\d3dutil.obj" \
	"$(INTDIR)\example16.obj" \
	"$(INTDIR)\Helicopter.obj" \
	"$(INTDIR)\Obj.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\example16.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "example16 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\example16.exe"


CLEAN :
	-@erase "$(INTDIR)\Car.obj"
	-@erase "$(INTDIR)\Cube.obj"
	-@erase "$(INTDIR)\d3dmath.obj"
	-@erase "$(INTDIR)\d3dtextr.obj"
	-@erase "$(INTDIR)\d3dutil.obj"
	-@erase "$(INTDIR)\example16.obj"
	-@erase "$(INTDIR)\example16.pch"
	-@erase "$(INTDIR)\Helicopter.obj"
	-@erase "$(INTDIR)\Obj.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\example16.exe"
	-@erase "$(OUTDIR)\example16.ilk"
	-@erase "$(OUTDIR)\example16.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\example16.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib d3dim.lib winmm.lib d3dframe.lib d3dxof.lib dxguid.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\example16.pdb" /debug /machine:I386 /out:"$(OUTDIR)\example16.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Car.obj" \
	"$(INTDIR)\Cube.obj" \
	"$(INTDIR)\d3dmath.obj" \
	"$(INTDIR)\d3dtextr.obj" \
	"$(INTDIR)\d3dutil.obj" \
	"$(INTDIR)\example16.obj" \
	"$(INTDIR)\Helicopter.obj" \
	"$(INTDIR)\Obj.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\example16.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("example16.dep")
!INCLUDE "example16.dep"
!ELSE 
!MESSAGE Warning: cannot find "example16.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "example16 - Win32 Release" || "$(CFG)" == "example16 - Win32 Debug"
SOURCE=.\Car.cpp

"$(INTDIR)\Car.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\Cube.cpp

"$(INTDIR)\Cube.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\d3dmath.cpp

!IF  "$(CFG)" == "example16 - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\d3dmath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "example16 - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\d3dmath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\d3dtextr.cpp

!IF  "$(CFG)" == "example16 - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\d3dtextr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "example16 - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\d3dtextr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\d3dutil.cpp

!IF  "$(CFG)" == "example16 - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\d3dutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "example16 - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\d3dutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\example16.cpp

"$(INTDIR)\example16.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\Helicopter.cpp

"$(INTDIR)\Helicopter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\Obj.cpp

"$(INTDIR)\Obj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\Scene.cpp

"$(INTDIR)\Scene.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\example16.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "example16 - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\example16.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "example16 - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\example16.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\example16.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

