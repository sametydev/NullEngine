#pragma once
#include <Wnd/Wnd.h>
#include <Render/DXBatch.h>
#include <Render/DXFontBatch.h>
#include <Render/DXSpriteBatch.h>

class WndFrame : public Wnd
{

public:
	WndFrame(const WndDesc& desc);
	virtual ~WndFrame();

	void OnCreate() override;
	void OnReSize(uint cx, uint cy) override;

	GraphicAPI mApiType;
	std::shared_ptr<Context> mContext;
	std::shared_ptr<DXFontBatch> mFontBatcher;
	std::shared_ptr<DXSpriteBatch> mSpriteBatcher;

	int ExecFrame(Scene* scene = nullptr);
};

