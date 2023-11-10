// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_JackOLantern/JackOLantern.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeJackOLantern() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AJackOLantern();
	PROJECT_JACKOLANTERN_API UClass* Z_Construct_UClass_AJackOLantern_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Project_JackOLantern();
// End Cross Module References
	void AJackOLantern::StaticRegisterNativesAJackOLantern()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AJackOLantern);
	UClass* Z_Construct_UClass_AJackOLantern_NoRegister()
	{
		return AJackOLantern::StaticClass();
	}
	struct Z_Construct_UClass_AJackOLantern_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AJackOLantern_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_JackOLantern,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AJackOLantern_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AJackOLantern_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "JackOLantern.h" },
		{ "ModuleRelativePath", "JackOLantern.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AJackOLantern_Statics::NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "JackOLantern" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "JackOLantern.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AJackOLantern_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x0040000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AJackOLantern, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AJackOLantern_Statics::NewProp_Mesh_MetaData), Z_Construct_UClass_AJackOLantern_Statics::NewProp_Mesh_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AJackOLantern_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AJackOLantern_Statics::NewProp_Mesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AJackOLantern_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AJackOLantern>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AJackOLantern_Statics::ClassParams = {
		&AJackOLantern::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AJackOLantern_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AJackOLantern_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AJackOLantern_Statics::Class_MetaDataParams), Z_Construct_UClass_AJackOLantern_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AJackOLantern_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AJackOLantern()
	{
		if (!Z_Registration_Info_UClass_AJackOLantern.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AJackOLantern.OuterSingleton, Z_Construct_UClass_AJackOLantern_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AJackOLantern.OuterSingleton;
	}
	template<> PROJECT_JACKOLANTERN_API UClass* StaticClass<AJackOLantern>()
	{
		return AJackOLantern::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AJackOLantern);
	AJackOLantern::~AJackOLantern() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_JackOLantern_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_JackOLantern_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AJackOLantern, AJackOLantern::StaticClass, TEXT("AJackOLantern"), &Z_Registration_Info_UClass_AJackOLantern, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AJackOLantern), 3811420495U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_JackOLantern_h_1991738877(TEXT("/Script/Project_JackOLantern"),
		Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_JackOLantern_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_JackOLantern_Project_JackOLantern_Source_Project_JackOLantern_JackOLantern_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
