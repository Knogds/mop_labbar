##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mop_3-1
ConfigurationName      :=Debug
WorkspacePath          :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar
ProjectPath            :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kresimir
Date                   :=17/02/21
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).elf
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="mop_3-1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostartfiles
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc $(LibrarySwitch)c_nano 
ArLibs                 :=  "gcc" "c_nano" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-ar rcu
CXX      := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-g++
CC       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O3 -w -mthumb -march=armv6-m -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=$(IntermediateDirectory)/graphicdisplay.c$(ObjectSuffix) $(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IntermediateDirectory)/font_6x8.c$(ObjectSuffix) $(IntermediateDirectory)/font.c$(ObjectSuffix) $(IntermediateDirectory)/draw.c$(ObjectSuffix) $(IntermediateDirectory)/xprintf.c$(ObjectSuffix) $(IntermediateDirectory)/startup.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  ./Debug/mop_3-1.elf ./Debug/mop_3-1.s19
	/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S ./Debug/mop_3-1.elf > ./Debug/mop_3-1.dass
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/graphicdisplay.c$(ObjectSuffix): graphicdisplay.c $(IntermediateDirectory)/graphicdisplay.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/graphicdisplay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/graphicdisplay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/graphicdisplay.c$(DependSuffix): graphicdisplay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/graphicdisplay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/graphicdisplay.c$(DependSuffix) -MM graphicdisplay.c

$(IntermediateDirectory)/graphicdisplay.c$(PreprocessSuffix): graphicdisplay.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/graphicdisplay.c$(PreprocessSuffix) graphicdisplay.c

$(IntermediateDirectory)/delay.c$(ObjectSuffix): delay.c $(IntermediateDirectory)/delay.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/delay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/delay.c$(DependSuffix): delay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/delay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/delay.c$(DependSuffix) -MM delay.c

$(IntermediateDirectory)/delay.c$(PreprocessSuffix): delay.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/delay.c$(PreprocessSuffix) delay.c

$(IntermediateDirectory)/font_6x8.c$(ObjectSuffix): font_6x8.c $(IntermediateDirectory)/font_6x8.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/font_6x8.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/font_6x8.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/font_6x8.c$(DependSuffix): font_6x8.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/font_6x8.c$(ObjectSuffix) -MF$(IntermediateDirectory)/font_6x8.c$(DependSuffix) -MM font_6x8.c

$(IntermediateDirectory)/font_6x8.c$(PreprocessSuffix): font_6x8.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/font_6x8.c$(PreprocessSuffix) font_6x8.c

$(IntermediateDirectory)/font.c$(ObjectSuffix): font.c $(IntermediateDirectory)/font.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/font.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/font.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/font.c$(DependSuffix): font.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/font.c$(ObjectSuffix) -MF$(IntermediateDirectory)/font.c$(DependSuffix) -MM font.c

$(IntermediateDirectory)/font.c$(PreprocessSuffix): font.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/font.c$(PreprocessSuffix) font.c

$(IntermediateDirectory)/draw.c$(ObjectSuffix): draw.c $(IntermediateDirectory)/draw.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/draw.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/draw.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/draw.c$(DependSuffix): draw.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/draw.c$(ObjectSuffix) -MF$(IntermediateDirectory)/draw.c$(DependSuffix) -MM draw.c

$(IntermediateDirectory)/draw.c$(PreprocessSuffix): draw.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/draw.c$(PreprocessSuffix) draw.c

$(IntermediateDirectory)/xprintf.c$(ObjectSuffix): xprintf.c $(IntermediateDirectory)/xprintf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/xprintf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/xprintf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xprintf.c$(DependSuffix): xprintf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/xprintf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/xprintf.c$(DependSuffix) -MM xprintf.c

$(IntermediateDirectory)/xprintf.c$(PreprocessSuffix): xprintf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/xprintf.c$(PreprocessSuffix) xprintf.c

$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c $(IntermediateDirectory)/startup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_3-1/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(DependSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c

$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


