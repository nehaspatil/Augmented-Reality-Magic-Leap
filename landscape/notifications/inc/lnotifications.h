
#include <lumin/LandscapeApp.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/notifications/Notification.h>
/**
 * notifications Landscape Application
 */
class lnotifications : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
	lnotifications();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~lnotifications();

  /**
   * Disallows the copy constructor.
   */
  lnotifications(const lnotifications&) = delete;

  /**
   * Disallows the move constructor.
   */
  lnotifications(lnotifications&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  lnotifications& operator=(const lnotifications&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  lnotifications& operator=(lnotifications&&) = delete;

protected:
  /**
   * Initializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int init() override;

  /**
   * Deinitializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int deInit() override;

  /**
   * Runs this method on the Landscape Application's Event Update Thread.
   * @param fDelta - time delta since last frame.
   * @return - true to continue running, false to terminate the application.
   */
  bool updateLoop(float fDelta) override;

  /**
   * Reacts to incoming events, runs on the Landscape Application's Event Update Thread.
   * @param event - incoming Server Event.
   * @return - true if the incoming event was consumed, false otherwise.
   */
  bool eventListener(lumin::ServerEvent* event) override;

private:
  lumin::Prism* prism_ = nullptr;  // represents the bounded space where the Scene Graph renders.
 


};
