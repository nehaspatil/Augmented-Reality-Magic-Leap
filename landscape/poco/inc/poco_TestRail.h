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
#include <Poco/Net/HTTPBasicCredentials.h>
#include <Poco/Net/HTTPSClientSession.h>
/**
 * qa_poco_example Landscape Application
 */
class poco_TestRail : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
	poco_TestRail();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~poco_TestRail();

  /**
   * Disallows the copy constructor.
   */
  poco_TestRail(const poco_TestRail&) = delete;

  /**
   * Disallows the move constructor.
   */
  poco_TestRail(poco_TestRail&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  poco_TestRail& operator=(const poco_TestRail&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  poco_TestRail& operator=(poco_TestRail&&) = delete;

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

private:
	void LoadHTTPRequestData();
	bool createHttpReq(std::string);
	void CreateHttpSession();
	bool CheckResponse();
	std::string m_data;
	Poco::Net::HTTPBasicCredentials creds;
	Poco::Net::HTTPSClientSession *ptr_session;
	lumin::Prism* m_prism;
};
