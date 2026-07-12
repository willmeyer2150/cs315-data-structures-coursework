# Top-level Makefile for hash-table LRU profile
# Uses CMake in ./build to compile and then runs the tools to:
#  1) generate LRU profile traces
#  2) run the hash-table harness to produce CSVs

BUILD_DIR := build

.PHONY: all configure lru_profile_trace hash_harness traces harness clean

# Default: generate traces then run harness
all: traces harness

# ----- CMake configuration -----

configure: $(BUILD_DIR)/CMakeCache.txt

$(BUILD_DIR)/CMakeCache.txt:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# ----- Build targets via CMake -----

# Build the LRU trace generator
lru_profile_trace: configure
	$(MAKE) -C $(BUILD_DIR) lru_profile_trace

# Build the hash-table harness
hash_harness: configure
	$(MAKE) -C $(BUILD_DIR) hash_harness

# ----- Run programs to generate outputs -----

# Generate all LRU traces
traces: lru_profile_trace
	@mkdir -p traces/lru_profile
	# Run from src/trace-generators/lru_profile so ../../../traces/... is correct
	cd src/trace-generators/lru_profile && ../../../$(BUILD_DIR)/lru_profile_trace

# Run harness to generate the CSV from the traces
harness: hash_harness
	@mkdir -p csvs
	# Run from src/hash_harness so ../../traces/... is correct
	cd src/hash_harness && ../../$(BUILD_DIR)/hash_harness

# ----- Cleanup -----

clean:
	$(RM) -r $(BUILD_DIR)
