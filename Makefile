BUILD_DIR ?= build

.PHONY: all configure test clean install coverage

all: test

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

test: configure
	cmake --build $(BUILD_DIR) --config Debug
	ctest --test-dir $(BUILD_DIR) -C Debug --output-on-failure

coverage:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug \
		-DGRAPH_FORGE_ENABLE_COVERAGE=ON
	cmake --build $(BUILD_DIR)
	ctest --test-dir $(BUILD_DIR) --output-on-failure

install: configure
	cmake --build $(BUILD_DIR)
	cmake --install $(BUILD_DIR) --prefix $(BUILD_DIR)/install

clean:
	cmake --build $(BUILD_DIR) --target clean 2>/dev/null || true
	rm -rf $(BUILD_DIR)
