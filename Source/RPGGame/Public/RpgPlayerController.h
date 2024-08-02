#pragma once // 确保头文件只被包含一次

#include "CoreMinimal.h" // 引入最小核心头文件
#include "InputActionValue.h" // 引入输入动作值相关头文件
#include "GameFramework/PlayerController.h" // 引入玩家控制器基类头文件
#include "RpgPlayerController.generated.h" // 用于生成标准构造代码

class UInputMappingContext; // 前向声明，避免头文件包含
class UInputAction; // 前向声明输入动作类

UCLASS() // 定义一个新的UClass
class RPGGAME_API ARpgPlayerController : public APlayerController // 声明类继承自APlayerController
{
	GENERATED_BODY() // 宏，用于支持引擎内部的反射和序列化机制

protected:
	virtual void BeginPlay() override; // 重写基类的BeginPlay方法
	virtual void SetupInputComponent() override; // 重写基类的SetupInputComponent方法

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> RpgContext; // 可在编辑器中编辑的输入映射上下文

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction; // 可在编辑器中编辑的移动动作

	void Move(const FInputActionValue& InputActionValue); // 移动函数，处理输入动作值
};
