#pragma once
#include <Wnd/Wnd.h>
#include <Render/DXBatch.h>
#include <Render/DXFontBatch.h>
#include <Render/BasicBatch.h>
#include <Render/BasicBatch.h>

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

private:
	DXFontBatch* mFontBatcher  = nullptr;
	BasicBatch* mSpriteBatcher = nullptr;
};

