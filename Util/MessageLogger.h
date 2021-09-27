#pragma once
#include <string>
#include <Windows.h>
#include <comdef.h>

namespace message_logger
{
	inline void __fastcall error(const std::wstring& message)
	{
		const std::wstring error_message = L"Error: " + message;
		MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
	}
	
	inline void __fastcall error(const HRESULT hr, const std::wstring& message)
	{
		error(message + L"\n" + _com_error(hr).ErrorMessage());
	}

	inline void __fastcall error(const HRESULT hr)
	{
		error(_com_error(hr).ErrorMessage());
	}
	
	inline void __fastcall question(const std::wstring& message)
	{
		const std::wstring question_message = L"Question: " + message;
		MessageBoxW(NULL, question_message.c_str(), L"Question", MB_ICONQUESTION);
	}

	inline void __fastcall question(const HRESULT hr, const std::wstring& message)
	{
		question(message + L"\n" + _com_error(hr).ErrorMessage());
	}

	inline void __fastcall question(const HRESULT hr)
	{
		question(_com_error(hr).ErrorMessage());
	}
	
	inline void __fastcall warning(const std::wstring& message)
	{
		const std::wstring warning_message = L"Warning: " + message;
		MessageBoxW(NULL, warning_message.c_str(), L"Warning", MB_ICONWARNING);
	}

	inline void __fastcall warning(const HRESULT hr, const std::wstring& message)
	{
		warning(message + L"\n" + _com_error(hr).ErrorMessage());
	}

	inline void __fastcall warning(const HRESULT hr)
	{
		warning(_com_error(hr).ErrorMessage());
	}

	inline void __fastcall succes(const std::wstring& message)
	{
		const std::wstring warning_message = L"Warning: " + message;
		MessageBoxW(NULL, warning_message.c_str(), L"Warning", MB_ICONINFORMATION);
	}

	inline void __fastcall succes(const HRESULT hr, const std::wstring& message)
	{
		succes(message + L"\n" + _com_error(hr).ErrorMessage());
	}

	inline void __fastcall succes(const HRESULT hr)
	{
		succes(_com_error(hr).ErrorMessage());
	}
}
