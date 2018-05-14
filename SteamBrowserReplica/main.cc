#include "application.h"
#include "view.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace Awesomium;

class SteamBrowser : public Application::Listener {
	Application* app_;
	View* view_;
	public:
		SteamBrowser()
	: app_(Application::Create()),
		view_(0) {
	app_->set_listener(this);
	}

	virtual ~SteamBrowser() {
	if (view_)
		app_->DestroyView(view_);
	if (app_)
		delete app_;
	}

	void Run() {
	app_->Run();
	}

	// Inherited from Application::Listener
	virtual void OnLoaded() {
	view_ = View::Create(1000, 600);
	// < Set up your View here. >

	WebURL url(WSLit("data:text/html, <input id='url' name='url' type='url' placeholder='http://www.example.com'><input type='button' onclick='redirect()' value='Submit'></input><br><p>Steam Browser Replica (replicates the version used in GMod) by Charles_(https://github.com/charlesbarone).</p><script>function redirect(){var e=document.getElementById('url');window.location=e.value}</script>"));

	//WebURL url(WSLit("file:///C:/steambrowserreplica/index.html"));
	view_->web_view()->LoadURL(url);
	}

	// Inherited from Application::Listener
	virtual void OnUpdate() {
	}

	// Inherited from Application::Listener
	virtual void OnShutdown() {
	}
};

#ifdef _WIN32
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, wchar_t*, 
	int nCmdShow) {
#else
int main() {
#endif

	SteamBrowser app;
	app.Run();

	return 0;
}