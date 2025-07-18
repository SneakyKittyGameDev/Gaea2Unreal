// Fill out your copyright notice in the Description page of Project Settings.
#include "GaeaEditorStyle.h"
#include "GaeaUEToolsEditor.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyleRegistry.h"
 
TUniquePtr<FSlateStyleSet> FGaeaEditorStyle::StyleSet;
 
void FGaeaEditorStyle::Initialize()
{
	if (StyleSet.IsValid())
	{
		// Only set up once
		return;
	}
 
	// Create the style sheet
	StyleSet = MakeUnique<FSlateStyleSet>(GetStyleSetName());

	//const FString ContentDir = "All/Plugins/GaeaUnrealTools/Icons/";

	/*static const FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("GaeaUnrealTools"))->GetContentDir();
	UE_LOG(LogTemp, Warning, TEXT("Content Directory is: %s"), *ContentDir);

	// Construct the relative path to the image file
	const FString IconPath = ContentDir + "/Icons/ImporterIcon.png";*/
	
	FString PluginPath = FPaths::Combine(FPaths::ProjectPluginsDir(), GaeaPluginFolderName);
	if (!FPaths::DirectoryExists(PluginPath))
	{	// Check if the plugin is in the Engines Plugins root directory
		PluginPath = FPaths::Combine(FPaths::EnginePluginsDir(), GaeaPluginFolderName);
		if (!FPaths::DirectoryExists(PluginPath))
		{	// Check if the plugin is in the Engines Plugins Marketplace root directory
			const FString MarketplacePath = FPaths::Combine(FPaths::EnginePluginsDir(), MarketplaceFolderName);
			PluginPath = FPaths::Combine(MarketplacePath, GaeaPluginFolderName);
		}
	}

	if (FPaths::DirectoryExists(PluginPath))
	{
		// Plugin found, construct the resources path
		const FString ResourcesPath = FPaths::Combine(PluginPath, TEXT("Resources"));
		UE_LOG(LogTemp, Warning, TEXT("Resources Directory is: %s"), *ResourcesPath);

		// Construct the relative path to the image file
		const FString IconPath = ResourcesPath + "/ImporterIcon.png";
		StyleSet->Set("ImporterIcon", new FSlateImageBrush(IconPath, FVector2D(40.0f, 40.0f)));
	}
	else
	{
		// Plugin not found
		UE_LOG(LogTemp, Error, TEXT("%s icon path not found. This is likely caused by the plugin being installed in an incorrect location or folder name. Please see https://gaea.app/uedocs for exact instructions for the file path."), *GaeaPluginFolderName);
	}	
	
 
	// Register the style set
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}
 
void FGaeaEditorStyle::Shutdown()
{
	// Unregister the style set
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		StyleSet.Reset();
	}
}
 
FName FGaeaEditorStyle::GetStyleSetName()
{
	static const FName StyleSetName(TEXT("GaeaEditorStyle"));
	return StyleSetName;
}

FString FGaeaEditorStyle::RootToPluginContentDir(const FString& RelativePath, const TCHAR* Extension)
{
	static const FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("GaeaUnrealTools"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}
