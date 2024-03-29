#include "application.h"
#include "view.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <string>

using namespace Awesomium;

class ApplicationWin : public Application {
  bool is_running_;
 public:
  ApplicationWin() {
    is_running_ = true;
    listener_ = NULL;
    web_core_ = NULL;
  }

  virtual ~ApplicationWin() {
    if (listener())
      listener()->OnShutdown();

    if (web_core_)
      web_core_->Shutdown();
  }

  virtual void Run() {
    Load();

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) && is_running_) {
      web_core_->Update();
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      if (listener())
        listener()->OnUpdate();
    }
  }
  
  virtual void Quit() {
    is_running_ = false;
  }

  virtual void Load() {
	WebConfig config;
	config.user_agent = WSLit("Mozilla/5.0 (Windows; Valve Source Client) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1003.1 Safari/535.19 Awesomium/1.7.5.1 GMod/13");

	web_core_ = WebCore::Initialize(config);

    if (listener())
      listener()->OnLoaded();
  }

  virtual View* CreateView(int width, int height) {
    return View::Create(width, height);
  }

  virtual void DestroyView(View* view) {
    delete view;
  }

  virtual void ShowMessage(const char* message) {
    std::string message_str(message, message + strlen(message));
    MessageBox(0, message_str.c_str(), message_str.c_str(), NULL);
  }
};

Application* Application::Create() {
  return new ApplicationWin();
}