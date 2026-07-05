#ifdef _WIN32
extern "C" {
  __declspec(dllexport) char optixLaunchParams[1<<16];
  __declspec(dllexport) void *get_optixLaunchParams() {
	  return (void *)&optixLaunchParams;
  }
}
#else
extern "C" void *get_optixLaunchParams() { return 0; }
#endif
