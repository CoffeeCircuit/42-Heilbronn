# Compile .cpp files to .o and generate .d dependency files.
# Use -MMD, -MP, and optionally -MF for robust header tracking.
# Use -include to load all .d files, so changes in headers trigger recompilation.

CXX = g++
CXXFLAGS = -Wall -Wextra -MMD -MP
SOURCES = Account.cpp tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(OBJECTS:.o=.d)
TARGET = test

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# 	$(CXX) $(CXXFLAGS) -MF $(@:.o=.d) -c $< -o $@	# Using -MF to specify dependency file name

-include $(DEPS)

# PRECOMPILED HEADERS
# 	The .gch rule ensures precompiled headers are rebuilt when headers change.
# 	The .d files ensure object files are rebuilt when any included header changes.
# %.gch: %.hpp
# 	g++ -x c++-header -c $<

clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

fclean: clean
	rm -f $(TARGET)

