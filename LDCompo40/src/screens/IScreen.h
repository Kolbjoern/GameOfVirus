#pragma once
class IScreen
{
public:
	virtual void run() = 0;
	virtual void destroy() = 0;
};