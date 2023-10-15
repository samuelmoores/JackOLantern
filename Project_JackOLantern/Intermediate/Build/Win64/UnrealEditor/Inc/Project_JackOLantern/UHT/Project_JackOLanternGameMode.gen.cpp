// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_JackOLantern/Project_JackOLanternGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProject_JackOLanternGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AProject_JackOLanternGameMode();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AProject_JackOLanternGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Project_JackOLantern();
// End Cross Module References
	void AProject_JackOLanternGameMode::StaticRegisterNativesAProject_JackOLanternGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProject_JackOLanternGameMode);
	UClass* Z_Construct_UClass_AProject_JackOLanternGameMode_NoRegister()
	{
		return AProject_JackOLanternGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AProject_JackOLanternGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_JackOLantern,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Project_JackOLanternGameMode.h" },
		{ "ModuleRelativePath", "Project_JackOLanternGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProject_JackOLanternGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::ClassParams = {
		&AProject_JackOLanternGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AProject_JackOLanternGameMode()
	{
		if (!Z_Registration_Info_UClass_AProject_JackOLanternGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProject_JackOLanternGameMode.OuterSingleton, Z_Construct_UClass_AProject_JackOLanternGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AProject_JackOLanternGameMode.OuterSingleton;
	}
	template<> PROJECT_JACKOLANTERN_API UClass* StaticClass<AProject_JackOLanternGameMode>()
	{
		return AProject_JackOLanternGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProject_JackOLanternGameMode);
	AProject_JackOLanternGameMode::~AProject_JackOLanternGameMode() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AProject_JackOLanternGameMode, AProject_JackOLanternGameMode::StaticClass, TEXT("AProject_JackOLanternGameMode"), &Z_Registration_Info_UClass_AProject_JackOLanternGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProject_JackOLanternGameMode), 348490294U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternGameMode_h_3289790699(TEXT("/Script/Project_JackOLantern"),
		Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Project_JackOLanternGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
