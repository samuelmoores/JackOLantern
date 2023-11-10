// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_JackOLantern/Project_JackOLanternCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProject_JackOLanternCharacter() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AProject_JackOLanternCharacter();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AProject_JackOLanternCharacter_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Project_JackOLantern();
// End Cross Module References
	DEFINE_FUNCTION(AProject_JackOLanternCharacter::execGetCandy)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetCandy();
		P_NATIVE_END;
	}
	void AProject_JackOLanternCharacter::StaticRegisterNativesAProject_JackOLanternCharacter()
	{
		UClass* Class = AProject_JackOLanternCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCandy", &AProject_JackOLanternCharacter::execGetCandy },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics
	{
		struct Project_JackOLanternCharacter_eventGetCandy_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Project_JackOLanternCharacter_eventGetCandy_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AProject_JackOLanternCharacter, nullptr, "GetCandy", nullptr, nullptr, Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::PropPointers), sizeof(Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::Project_JackOLanternCharacter_eventGetCandy_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::Function_MetaDataParams), Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::Project_JackOLanternCharacter_eventGetCandy_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProject_JackOLanternCharacter);
	UClass* Z_Construct_UClass_AProject_JackOLanternCharacter_NoRegister()
	{
		return AProject_JackOLanternCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AProject_JackOLanternCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ThrowAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ThrowAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InteractAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_health_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_health;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_numCandy_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_numCandy;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActorToSpawn_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_ActorToSpawn;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_JackOLantern,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AProject_JackOLanternCharacter_GetCandy, "GetCandy" }, // 3720948895
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Project_JackOLanternCharacter.h" },
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_CameraBoom_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_CameraBoom_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_FollowCamera_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_FollowCamera_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** MappingContext */" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MappingContext" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_DefaultMappingContext_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_DefaultMappingContext_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_JumpAction_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_JumpAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_MoveAction_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_MoveAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_LookAction_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_LookAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ThrowAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ThrowAction = { "ThrowAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, ThrowAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ThrowAction_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ThrowAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_InteractAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_InteractAction = { "InteractAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, InteractAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_InteractAction_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_InteractAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_health_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Project_JackOLanternCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------Health-----------\n" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-----------Health-----------" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_health = { "health", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, health), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_health_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_health_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_numCandy_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Project_JackOLanternCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//----------Pickups-------------\n" },
#endif
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "----------Pickups-------------" },
#endif
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_numCandy = { "numCandy", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, numCandy), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_numCandy_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_numCandy_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ActorToSpawn_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Project_JackOLanternCharacter" },
		{ "ModuleRelativePath", "Project_JackOLanternCharacter.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ActorToSpawn = { "ActorToSpawn", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProject_JackOLanternCharacter, ActorToSpawn), Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ActorToSpawn_MetaData), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ActorToSpawn_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_CameraBoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_FollowCamera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_DefaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_JumpAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_MoveAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_LookAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ThrowAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_InteractAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_health,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_numCandy,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::NewProp_ActorToSpawn,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProject_JackOLanternCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::ClassParams = {
		&AProject_JackOLanternCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AProject_JackOLanternCharacter()
	{
		if (!Z_Registration_Info_UClass_AProject_JackOLanternCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProject_JackOLanternCharacter.OuterSingleton, Z_Construct_UClass_AProject_JackOLanternCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AProject_JackOLanternCharacter.OuterSingleton;
	}
	template<> PROJECT_JACKOLANTERN_API UClass* StaticClass<AProject_JackOLanternCharacter>()
	{
		return AProject_JackOLanternCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProject_JackOLanternCharacter);
	AProject_JackOLanternCharacter::~AProject_JackOLanternCharacter() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AProject_JackOLanternCharacter, AProject_JackOLanternCharacter::StaticClass, TEXT("AProject_JackOLanternCharacter"), &Z_Registration_Info_UClass_AProject_JackOLanternCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProject_JackOLanternCharacter), 1411729251U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternCharacter_h_3358742301(TEXT("/Script/Project_JackOLantern"),
		Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
