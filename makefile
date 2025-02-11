TARGET = ray_tracing

CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall #-g -fsanitize=address


LIBS = -lglfw -lGL -lGLEW -lm  #-fsanitize=address
INCLUDES = -I/usr/include/glm -Iexternal/imgui -Iexternal/imgui/backends

IMGUI_DIR = external/imgui
IMGUI_BACKENDS = $(IMGUI_DIR)/backends

SRCS = main.cpp ray_tracing_utils.cpp sphere.cpp ring.cpp texture.cpp init_objects.cpp background.cpp  \
       $(IMGUI_DIR)/imgui.cpp \
       $(IMGUI_DIR)/imgui_draw.cpp \
       $(IMGUI_DIR)/imgui_tables.cpp \
       $(IMGUI_DIR)/imgui_widgets.cpp \
       $(IMGUI_BACKENDS)/imgui_impl_glfw.cpp \
       $(IMGUI_BACKENDS)/imgui_impl_opengl3.cpp

SRCSCL = main.cpp ray_tracing_utils.cpp sphere.cpp ring.cpp texture.cpp init_objects.cpp background.cpp \

OBJS = $(SRCS:.cpp=.o)
OBJSCL = $(SRCSCL:.cpp=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
