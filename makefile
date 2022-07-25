#program name
prog	=SkeletalEngine.exe

#directories
srcDir	=source
binDir	=binary
bldDir	=build
incDir	=include
resDir	=inventory
libDir	=library

#flags
cc		=g++
incl	=-I$(incDir)
lib		=-lglad -lglfw3dll
flag	=-pthread -MP -MD
ldflag	=-L$(libDir)

#classes and objects
classes	=$(shell find $(srcDir) -name "*.cpp")
objects	=$(patsubst $(srcDir)/%,$(bldDir)/%,$(classes:.cpp=.o))
dependencies = $(patsubst $(bldDir)/%, $(bldDir)/%, $(objects:.o=.d))

#rules
all:	directories $(prog)

resources: directories
	@mkdir -p $(binDir)/$(resDir)
	@cp -rf $(resDir)/* $(binDir)/$(resDir)

directories:
	@mkdir -p $(binDir)
	@mkdir -p $(bldDir)
	@cp $(libDir)/glfw3.dll $(binDir)/

$(prog):	$(objects)
	@echo " ____|-----|____"
	@echo " |:: | ::: | :: | "
	@echo " |:: | ::: | :: |"
	@echo " |   |     |    |"
	@echo "     BUILDING "
	$(cc) -o $(binDir)/$@ $^ $(ldflag) $(lib)

$(bldDir)/%.o:	$(srcDir)/%.cpp
	@echo "<<<< COMPILING >>>>>"
	$(cc) -o $@ -c $< $(flag) $(incl)

clean:
	@rm -rf $(bldDir)
	@echo "cleaning complete"

purge: clean
	@rm -rf $(binDir)
	@echo "Entire village is purged !"

release: resources all

-include $(dependencies)