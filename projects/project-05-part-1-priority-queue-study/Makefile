# Top-level Makefile for priority-queue-study
# Uses CMake in ./build to compile and then runs the tools to:
#  1) generate batch-then-drain traces
#  2) generate the CSV via the harness

BUILD_DIR := build

.PHONY: all configure build batch_then_drain_trace harness traces csv clean

# Default: generate traces then CSV
all: traces csv

# ----- CMake configuration -----

configure: $(BUILD_DIR)/CMakeCache.txt

$(BUILD_DIR)/CMakeCache.txt:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# ----- Build targets via CMake -----

batch_then_drain_trace: configure
	$(MAKE) -C $(BUILD_DIR) batch_then_drain_trace

harness: configure
	$(MAKE) -C $(BUILD_DIR) harness

# ----- Run programs to generate outputs -----

# Generate all batch-then-drain traces
traces: batch_then_drain_trace
	@mkdir -p traces/batch_then_drain
	# Run from src/trace-generators/batch_then_drain so ../../../traces/... is correct
	cd src/trace-generators/batch_then_drain && ../../../$(BUILD_DIR)/batch_then_drain_trace

# Run harness to generate the CSV from the traces
csv: harness
	@mkdir -p csvs
	# Run from src/harness so ../../traces/... is correct
	cd src/harness && ../../$(BUILD_DIR)/harness

# ----- Cleanup -----

clean:
	$(RM) -r $(BUILD_DIR)
