// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_JackOLantern/Pot.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePot() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_APot();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_APot_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Project_JackOLantern();
// End Cross Module References
	void APot::StaticRegisterNativesAPot()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APot);
	UClass* Z_Construct_UClass_APot_NoRegister()
	{
		return APot::StaticClass();
	}
	struct Z_Construct_UClass_APot_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APot_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_JackOLantern,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APot_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APot_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Pot.h" },
		{ "ModuleRelativePath", "Pot.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APot_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APot>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_APot_Statics::ClassParams = {
		&APot::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APot_Statics::Class_MetaDataParams), Z_Construct_UClass_APot_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_APot()
	{
		if (!Z_Registration_Info_UClass_APot.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APot.OuterSingleton, Z_Construct_UClass_APot_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_APot.OuterSingleton;
	}
	template<> PROJECT_JACKOLANTERN_API UClass* StaticClass<APot>()
	{
		return APot::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(APot);
	APot::~APot() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Pot_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Pot_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_APot, APot::StaticClass, TEXT("APot"), &Z_Registration_Info_UClass_APot, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APot), 436726750U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Pot_h_2762959304(TEXT("/Script/Project_JackOLantern"),
		Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Pot_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_Pot_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
