target("engine")

  local headers = os.files("**.h")
  local sources = os.files("**.cpp")

  
  add_files(sources)
  add_headerfiles(headers)
