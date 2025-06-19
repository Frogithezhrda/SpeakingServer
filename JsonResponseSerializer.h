#pragma once
#include "IRequestHandler.h"
#include "json.hpp"
#include <sstream>
#include "Requests.h"

using json = nlohmann::json;

class JsonResponseSerializer
{
public:

	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LogoutResponse& logoutResponse);


private:

	template<typename T1, typename T2>
	static Buffer serialize(const T1& key, const T2& value, Buffer& buffer, const RequestId& id)
	{
		std::string message;
		json json;

		// Insert the key value pair into a JSON object.
		json[key] = value;

		// Convert the JSON object to a string representation.
		message = json.dump();

		// Add the request ID as the first byte in the buffer.
		buffer.push_back(static_cast<unsigned char>(id));
		// Append the actual message characters as bytes.
		for (auto& bit : message)
		{
			buffer.push_back(static_cast<unsigned char>(bit));
		}
		return buffer;
	}

};