#pragma once

extern Gabr::Application* Gabr::Create();

int main(int argc, char** argv)
{
	auto app = Gabr::Create();
	app->Run();
	delete app;
}