#pragma once
#include <Wnd/Wnd.h>
#include <Render/DXBatch.h>
class WndFrame : public Wnd
{

public:
	WndFrame(const WndDesc& desc);
	virtual ~WndFrame();

	void OnCreate() override;
	void OnReSize(uint cx, uint cy) override;

	GraphicAPI mApiType;
	std::shared_ptr<Context> mContext;
	std::shared_ptr<DXBatch> mBatcher;

	int ExecFrame(Scene* scene = nullptr);
};

