extern "C" __declspec(dllexport) void Init(const char* path)
{
	Configuration::Read();

	Main::Install();
}