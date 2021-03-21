##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=lab5
ConfigurationName      :=Debug
WorkspacePath          :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar
ProjectPath            :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/lab5
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kresimir
Date                   :=21/03/21
CodeLitePath           :=/home/kresimir/.codelite
LinkerName             :=/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-g++
SharedObjectLinkerName :=/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)d.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="lab5.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-ar rcu
CXX      := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-g++
CC       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) $(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IntermediateDirectory)/general.c$(ObjectSuffix) $(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/.build-debug"
	@echo rebuilt > "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/.build-debug/lab5"

PostBuild:
	@echo Executing Post Build commands ...
	
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix): asciidisplay_driver.c $(IntermediateDirectory)/asciidisplay_driver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/lab5/asciidisplay_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/asciidisplay_driver.c$(DependSuffix): asciidisplay_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/asciidisplay_driver.c$(DependSuffix) -MM asciidisplay_driver.c

$(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix): asciidisplay_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix) asciidisplay_driver.c

$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix): usart_driver.c $(IntermediateDirectory)/usart_driver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/lab5/usart_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usart_driver.c$(DependSuffix): usart_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/usart_driver.c$(DependSuffix) -MM usart_driver.c

$(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix): usart_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix) usart_driver.c

$(IntermediateDirectory)/general.c$(ObjectSuffix): general.c $(IntermediateDirectory)/general.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/lab5/general.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/general.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/general.c$(DependSuffix): general.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/general.c$(ObjectSuffix) -MF$(IntermediateDirectory)/general.c$(DependSuffix) -MM general.c

$(IntermediateDirectory)/general.c$(PreprocessSuffix): general.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/general.c$(PreprocessSuffix) general.c

$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix): keypad_driver.c $(IntermediateDirectory)/keypad_driver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/lab5/keypad_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keypad_driver.c$(DependSuffix): keypad_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keypad_driver.c$(DependSuffix) -MM keypad_driver.c

$(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix): keypad_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix) keypad_driver.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


