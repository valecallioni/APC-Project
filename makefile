CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o Job.o Application.o Stage.o helper.o create_application.o Process.o FineGrain.o FineGrainWeights.o FineGrainDerivative.o CoarseGrain.o


.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

Job.o: Job.hh Stage.hpp
Stage.o: Stage.hpp
helper.o: helper.hpp
create_application.o: create_application.hpp Application.hpp helper.hpp Job.hh Stage.hpp
Application.o: Job.hh Stage.hpp
Process.o: Process.hpp Application.hpp create_application.hpp
FineGrain.o : FineGrain.hpp
FineGrainWeights.o : FineGrain.hpp FineGrainWeights.hpp
FineGrainDerivative.o : FineGrain.hpp FineGrainDerivative.hpp
CoarseGrain.o : CoarseGrain.hpp
main.o:  Job.hh Stage.hpp helper.hpp Application.hpp create_application.hpp Process.hpp FineGrain.hpp FineGrainWeights.hpp FineGrainDerivative.hpp CoarseGrain.hpp

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
