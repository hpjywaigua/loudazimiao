#pragma once

// Pubg Mobile Battelgrounds (3.0.0 -- 64Bit) SDK Generate By @hhamk2
// Telegram Channel:- @SANSERO_MOD_1
// Generate on Mon Jan  8 10:14:13 2024
 
namespace SDK
{
//---------------------❣︎➪𝐒𝐀𝐍𝐒𝐄𝐑𝐎 𝐃𝐄𝐕𝐄𝐋𝐎𝐏𝐄𝐑༆✈︎🇪🇬---------------------------
//Classes
//---------------------❣︎➪𝐒𝐀𝐍𝐒𝐄𝐑𝐎 𝐃𝐄𝐕𝐄𝐋𝐎𝐏𝐄𝐑༆✈︎🇪🇬---------------------------

// Class SceneCaptureWidgetPlugin.WidgetCaptureComponent2D
// 0x0020 (0x09B0 - 0x0990)
class UWidgetCaptureComponent2D : public USceneCaptureComponent2D
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0990(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class SceneCaptureWidgetPlugin.WidgetCaptureComponent2D");
		return pStaticClass;
	}

};


// Class SceneCaptureWidgetPlugin.SceneCaptureCameraActor
// 0x0010 (0x0980 - 0x0970)
class ASceneCaptureCameraActor : public ACameraActor
{
public:
	class UWidgetCaptureComponent2D*                   SceneCaptureComponent;                                    // 0x0970(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0978(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class SceneCaptureWidgetPlugin.SceneCaptureCameraActor");
		return pStaticClass;
	}

};


// Class SceneCaptureWidgetPlugin.SceneCaptureWidget
// 0x00E0 (0x01E0 - 0x0100)
class USceneCaptureWidget : public UWidget
{
public:
	struct FSlateBrush                                 Brush;                                                    // 0x0100(0x00B8) (Edit, BlueprintVisible, BlueprintReadOnly)
	class ASceneCaptureCameraActor*                    SceneCaptureCameraActor;                                  // 0x01B8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x20];                                      // 0x01C0(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class SceneCaptureWidgetPlugin.SceneCaptureWidget");
		return pStaticClass;
	}


	void SetSceneCaptureCameraActor(class ASceneCaptureCameraActor* InSceneCaptureCameraActor);
};


}

