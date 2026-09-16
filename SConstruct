#!/usr/bin/env python
import os
import sys

# You can find documentation for SCons and SConstruct files at:
# https://scons.org/documentation.html


#
# REGION: Sources
#
project_sources = []
for root, dirs, files in os.walk("src"):
    for file in files:
        print(f"Adding: {file}")
        if file.endswith(".cpp"):
            project_sources.append(os.path.join(root, file))

test_normal_sources = Glob("tests/basic/*.cpp")
test_godot_sources = Glob("tests/godot/*.cpp")

print("Project sources")
for source in project_sources:
    print("  ", source)

VariantDir(
        "build/tests",
        "src",
        duplicate=False,
        )

test_env_sources = Glob("build/tests/**/*.cpp")



#
# REGION: Create Environment
#

# This lets SCons know that we're using godot-cpp, from the godot-cpp folder.

env = SConscript("godot-cpp/SConstruct")

# Configures the 'src' directory as a source for header files.
env.Append(CPPPATH=["src/"])
test_env = env.Clone()

test_env.Append(CPPPATH=["src", "src/voxel/", "godot-cpp/include/", "godot-cpp/gen/include", "godot-cpp/gdextension"],CXXFLAGS=["-g", "-O0"])

test_env.Program(
        target="bin/tests",
        source=test_env_sources + project_sources + test_normal_sources,
        )

print("TEST CXXFLAGS:", test_env.get("CXXFLAGS"))
print("TEST CCFLAGS:", test_env.get("CCFLAGS"))

# The filename for the dynamic library for this GDExtension.
# $SHLIBPREFIX is a platform specific prefix for the dynamic library ('lib' on Unix, '' on Windows).
# $SHLIBSUFFIX is the platform specific suffix for the dynamic library (for example '.dll' on Windows).
# env["suffix"] includes the build's feature tags (e.g. '.windows.template_debug.x86_64')
# (see https://docs.godotengine.org/en/stable/tutorials/export/feature_tags.html).
# The final path should match a path in the '.gdextension' file.
lib_filename = "{}gdexample{}{}".format(env.subst('$SHLIBPREFIX'), env["suffix"], env.subst('$SHLIBSUFFIX'))

# Creates a SCons target for the path with our sources.
library = env.SharedLibrary(
    "project/bin/{}".format(lib_filename),
    source=project_sources + test_godot_sources,
)

# Selects the shared library as the default target.
Default(library)
