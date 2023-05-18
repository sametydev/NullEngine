#pragma once
#include <Wnd/Wnd.h>

class WndFrame : public Wnd
{

public:
	WndFrame(const WndDesc& desc);
	virtual ~WndFrame();

	void OnCreate() override;
	void OnReSize(uint cx, uint cy) override;

	GraphicAPI mApiType;
	std::shared_ptr<Context> mContext;

	int ExecFrame(Scene* scene = nullptr);
};

