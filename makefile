CXX       = g++
CXXFLAGS  = -c -std=c++14
LDFLAGS   = -lsfml-graphics -lsfml-window -lsfml-system
BDIR      = build
VPATH     = src
SOURCES   = Eris.cpp
OBJECTS   = $(SOURCES:%.cpp=$(BDIR)/%.o)
EXECUTABLE= $(BDIR)/Eris

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
