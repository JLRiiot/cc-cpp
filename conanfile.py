from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.errors import ConanInvalidConfiguration

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("gtest/1.14.0")
        self.requires("cryptopp/8.9.0")
        self.requires("boost/1.84.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")

    def layout(self):
        cmake_layout(self)

    # def validate(self):
    #     if self.settings.os == "Macos" and self.settings.arch == "armv8":
    #         raise ConanInvalidConfiguration("ARM v8 not supported in Macos")