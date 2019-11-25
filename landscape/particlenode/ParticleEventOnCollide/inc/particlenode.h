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
#include <lumin/InitArg.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <ParticleOnCollide.h>

class particlenode : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
  particlenode();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~particlenode();

  /**
   * Disallows the copy constructor.
   */
  particlenode(const particlenode&) = delete;

  /**
   * Disallows the move constructor.
   */
  particlenode(particlenode&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  particlenode& operator=(const particlenode&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  particlenode& operator=(particlenode&&) = delete;

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
   * This is called each time the application is launched from the icon grid.
   * Most apps choose to create a new prism.
   * @param initArg - the initial application argument
   */
  void onAppStart(const lumin::InitArg&) override;

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
};
