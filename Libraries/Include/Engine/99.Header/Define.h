#pragma once

#define DECLARE_SINGLETON(ClassName)	\
private:								\
	ClassName() {}						\
										\
public:									\
	static ClassName* GetInstance()		\
	{									\
		static ClassName s_instance;	\
		return &s_instance;				\
	}									\


#define GET_SINGLE(ClassName) ClassName::GetInstance()

#define GAME			GET_SINGLE(Game)		
#define GRAPHICS		GET_SINGLE(Graphics)
#define DEVICE			GRAPHICS->GetDevice()
#define DEVICECONTEXT	GRAPHICS->GetDeviceContext()
#define INPUT			GET_SINGLE(InputManager)
#define TIME			GET_SINGLE(TimeManager)
#define DELTATIME		TIME->GetDeltaTime()
#define RESOURCES		GET_SINGLE(ResourceManager)
#define RENDER			GET_SINGLE(RenderManager)
#define INSTANCING		GET_SINGLE(InstancingManager)
#define GUI				GET_SINGLE(ImGuiManager)