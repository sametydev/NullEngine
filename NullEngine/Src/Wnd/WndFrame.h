#pragma once
#include <Wnd/Wnd.h>

class WndFrame : public Wnd
{

public:
	WndFrame(Wnd* parent,uint height,uint width);
	virtual ~WndFrame();

	void OnCreate() override;
	void OnReSize(uint cx, uint cy) override;

	//TODO : Graphics Context
	//Input Event
	//Event Drive Execute
	std::shared_ptr<Context> mContext;

	int ExecFrame(Scene* scene = nullptr);
};

