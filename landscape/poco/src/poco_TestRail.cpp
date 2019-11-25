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
#include <poco_TestRail.h>
#include <lumin/node/RootNode.h>
#include <lumin/ui/Cursor.h>
#include <lumin/ui/node/UiText.h>
#include <ml_logging.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPBasicCredentials.h>
#include <Poco/Net/KeyConsoleHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/HTTPAuthenticationParams.h>
#include <Poco/URI.h>
#include <lumin/ui/UiKitConsts.h>
#include <lumin/ui/UiKit.h>
#include <lumin/ui/node/UiButton.h>
#include <TestRailConst.h>
#include <iostream>

using namespace lumin;
using namespace lumin::ui;
using namespace Poco;
using namespace Poco::Net;

poco_TestRail::poco_TestRail() {
  ML_LOG(Debug, "poco_TestRail Constructor.");

}

poco_TestRail::~poco_TestRail() {
  ML_LOG(Debug, "poco_TestRail Destructor.");
}

int poco_TestRail::init() {
  ML_LOG(Debug, "poco_TestRail Initializing.");

  return 0;
}

void poco_TestRail::onAppStart(const InitArg&) {
	ML_LOG(Debug, "poco_TestRail creating instance");
	// Create a prism
	glm::vec3 size(2.0f, 2.0f, 2.0f);
	Prism* m_prism = requestNewPrism(size);
	if (!m_prism) {
		ML_LOG(Error, "poco_TestRail Error creating default prism.");
	}

	ui::UiText* label = ui::UiText::Create(m_prism, "Landscape  Application using Poco to connect to TestRail \n For TestNames refer to TestRailConst.h ");
	if (!m_prism->getRootNode()->addChild(label)) {
		ML_LOG(Error, "Tests Failed to add label  to the prism.");
	}

	label->setTextSize(.05f);
	label->setAlignment(ui::Alignment::CENTER_CENTER);
	label->setLocalPosition(glm::vec3(-.1f, .6f, 0));
	label->setTextColor(glm::vec4(.9f,0,0,1));

	ui::Cursor::SetScale(m_prism, 0.03f);

	LoadHTTPRequestData();
	CreateHttpSession();

	auto controlButton = lumin::ui::UiButton::CreateEclipseButton(m_prism, EclipseButtonParams(EclipseButtonType::kText, "Update TestRail Result", .02f));
	controlButton->setLocalPosition(glm::vec3(0, 0, 0));
	controlButton->setLocalScale(glm::vec3(3, 3, 3));
	m_prism->getRootNode()->addChild(controlButton);

	controlButton->onActivateSub([this](const UiEventData&) {

		for (auto it  = m_TestCaseID.begin(); it != m_TestCaseID.end(); it++)
		{
			std::string temp = *it;
			createHttpReq(temp);
			CheckResponse();

		}
	});

}
bool poco_TestRail::createHttpReq(std::string m_testID)
{

	std::string m_req;
	m_req = "/index.php?/api/v2/add_result_for_case/" + m_TestRunID + "/" + m_testID;

	HTTPRequest request1("POST", m_req, HTTPMessage::HTTP_1_1);
	request1.setContentType("application/json");
	request1.setContentLength(m_data.length());

	creds.authenticate(request1);
	std::ostream& myOStream = ptr_session->sendRequest(request1);
	myOStream << m_data << std::flush;

	return true;

}
bool poco_TestRail::CheckResponse()
{
	HTTPResponse response1;
	std::istream &is = ptr_session->receiveResponse(response1);

	std::string m_string;
	StreamCopier::copyToString64(is, m_string);

	HTTPResponse::HTTPStatus m_status = response1.getStatus();

	ui::UiText* m_Text1 = ui::UiText::Create(m_prism, "");
	m_Text1->setTextSize(.05f);
	m_Text1->setAlignment(ui::Alignment::CENTER_CENTER);
	m_prism->getRootNode()->addChild(m_Text1);
	m_Text1->setLocalPosition(glm::vec3(-.8f, 0, 0));

	if (m_status != HTTPResponse::HTTPStatus::HTTP_OK)
	{
		m_Text1->setText("Error");
		return false;
	}
	else
	{
		m_Text1->setText("Sucess");

	}
	return true;

}
void poco_TestRail::CreateHttpSession()
{
	SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new KeyConsoleHandler(false);
	SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new ConsoleCertificateHandler(false);
	Context::Ptr pContext = new Context(Context::CLIENT_USE, "", "", "res/ssl/xxxxxxx.pem", Poco::Net::Context::VERIFY_NONE);
	SSLManager::instance().initializeClient(pConsoleHandler, pInvalidCertHandler, pContext);

	creds.setUsername(m_User);
	creds.setPassword(m_Password);

	URI m_uri1("https://testrail.magicleap.com");
	ptr_session = new HTTPSClientSession(m_uri1.getHost(), m_uri1.getPort(), pContext);
}


void poco_TestRail::LoadHTTPRequestData()
{
	m_data = "{\"status_id\":";
	m_data += "1";

	m_data += ",\"version\":\"";
	m_data += m_version;
	m_data += "\"";


	m_data += ",\"custom_wear_hw_version\":\"";
	m_data += m_custom_wear_hw_version;
	m_data += "\"";

	m_data += ",\"custom_wearableversion\":\"";
	m_data += m_custom_wearableversion;
	m_data += "\"";

	m_data += "}";

}
int poco_TestRail::deInit() {
	ML_LOG(Debug, "poco_TestRail Deinitializing.");

	return 0;
}

bool poco_TestRail::updateLoop(float fDelta) {
	return true;
}

bool poco_TestRail::eventListener(ServerEvent* event) {

	return false;
}
