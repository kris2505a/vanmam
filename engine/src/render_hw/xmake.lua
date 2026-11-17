target("engine")

  local headers = os.files("**.h")
  local sources = os.files("**.cpp")

  
  add_files(sources)
  add_headerfiles(headers)
  add_defines("VULKAN_HPP_NO_STRUCT_CONSTRUCTORS")
  add_defines("VULKAN_HPP_NO_EXCEPTIONS")
  add_defines("VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1")
  