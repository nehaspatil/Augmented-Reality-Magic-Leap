// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%
#include <lumin/LandscapeApp.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/notifications/Notification.h>
/**
 * qa_notifications Landscape Application
 */
class qa_notifications : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
  qa_notifications();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~qa_notifications();

  /**
   * Disallows the copy constructor.
   */
  qa_notifications(const qa_notifications&) = delete;

  /**
   * Disallows the move constructor.
   */
  qa_notifications(qa_notifications&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  qa_notifications& operator=(const qa_notifications&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  qa_notifications& operator=(qa_notifications&&) = delete;

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
