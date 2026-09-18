#include "register_types.h"

#include "../tests/godot/test_runner.h"

#include "ui/button_call_function.h"

#include "voxel/voxel_generator.h"
#include "voxel/voxel_interactor.h"
#include "voxel/voxel_manager.h"
#include "voxel/voxel_object.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  GDREGISTER_CLASS(Button_Call_Function);

  GDREGISTER_CLASS(Voxel_Manager);
  GDREGISTER_CLASS(Voxel_Interactor);
  GDREGISTER_CLASS(Voxel_Generator);
  GDREGISTER_CLASS(Voxel_Object);

#ifndef UNIT_TEST_BUILD
  GDREGISTER_CLASS(Test_Runner);
#endif
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C" {
GDExtensionBool GDE_EXPORT
example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                     const GDExtensionClassLibraryPtr p_library,
                     GDExtensionInitialization *r_initializtion) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initializtion);

  init_obj.register_initializer(initialize_example_module);
  init_obj.register_terminator(uninitialize_example_module);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}
