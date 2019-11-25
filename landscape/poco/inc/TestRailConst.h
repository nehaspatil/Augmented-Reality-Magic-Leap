#pragma once
#include "string.h"
#include <set>
#include <iostream>

const std::string m_TestRunID = "IDxxx";
const std::string m_version = "Versionyyyy";
const std::string m_custom_wear_hw_version = "zzzzzz";
const std::string m_custom_wearableversion = "wwwwwwwwww";

const std::string m_User = "npatil@magicleap.com";
const std::string m_Password = "xxxxxxxxxxx"; // actual password for testrail . 

std::set <std::string> m_TestCaseID = {

		"20633008", // TryOpenApplication 
		"20503056", // Uikit - scrollbar
		"20503057", //UIkit - progressbar
		"20601453", //Uikit - LoadingSpinner
};
