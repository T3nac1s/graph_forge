from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.build import check_min_cppstd
import os


class GraphForgeConan(ConanFile):
    name = "graph_forge"
    version = "0.1.0"
    license = "MIT"
    url = "https://github.com/graph-forge/graph_forge"
    description = "A robust, header-only C++20 graph algorithm library forged for competitive programming"
    topics = ("graph", "algorithms", "header-only", "cpp20")
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "with_tests": [True, False],
        "warnings_as_errors": [True, False],
    }
    default_options = {
        "with_tests": False,
        "warnings_as_errors": False,
    }
    exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "tests/*"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        if self.options.with_tests:
            self.test_requires("gtest/1.15.0")

    def validate(self):
        check_min_cppstd(self, "20")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["GRAPH_FORGE_WARNINGS_AS_ERRORS"] = (
            self.options.warnings_as_errors
        )
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        if self.options.with_tests:
            cmake.build()

    def package(self):
        copy(
            self,
            "*.h",
            src=os.path.join(self.source_folder, "src"),
            dst=os.path.join(self.package_folder, "include"),
            keep_path=True,
        )
        copy(
            self,
            "*.hpp",
            src=os.path.join(self.source_folder, "src"),
            dst=os.path.join(self.package_folder, "include"),
            keep_path=True,
        )
        copy(
            self,
            "graph_forgeConfig.cmake",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "lib/cmake/graph_forge"),
            keep_path=False,
        )
        copy(
            self,
            "graph_forgeConfigVersion.cmake",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "lib/cmake/graph_forge"),
            keep_path=False,
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "graph_forge")
        self.cpp_info.set_property("cmake_target_name", "graph_forge::graph_forge")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = ["include"]
