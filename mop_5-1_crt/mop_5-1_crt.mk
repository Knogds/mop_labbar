##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mop_5-1_crt
ConfigurationName      :=Debug
WorkspacePath          :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar
ProjectPath            :=/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_5-1_crt
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kresimir
Date                   :=17/03/21
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
ObjectsFileList        :="mop_5-1_crt.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -T$(ProjectPath)/md407-ram-crt.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
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
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/sve.c$(ObjectSuffix) $(IntermediateDirectory)/startup-crt.c$(ObjectSuffix) 



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
	/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  ./Debug/mop_5-1_crt.elf ./Debug/mop_5-1_crt.s19
	/usr/share/codelite/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S ./Debug/mop_5-1_crt.elf > ./Debug/mop_5-1_crt.dass
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/sve.c$(ObjectSuffix): sve.c $(IntermediateDirectory)/sve.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_5-1_crt/sve.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sve.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sve.c$(DependSuffix): sve.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sve.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sve.c$(DependSuffix) -MM sve.c

$(IntermediateDirectory)/sve.c$(PreprocessSuffix): sve.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sve.c$(PreprocessSuffix) sve.c

$(IntermediateDirectory)/startup-crt.c$(ObjectSuffix): startup-crt.c $(IntermediateDirectory)/startup-crt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kresimir/fax/maskinorienterad_programmering/codelite/labbar/mop_5-1_crt/startup-crt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup-crt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup-crt.c$(DependSuffix): startup-crt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup-crt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup-crt.c$(DependSuffix) -MM startup-crt.c

$(IntermediateDirectory)/startup-crt.c$(PreprocessSuffix): startup-crt.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup-crt.c$(PreprocessSuffix) startup-crt.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


