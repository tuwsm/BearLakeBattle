#pragma once

#include "IPropertyTypeCustomization.h"

class UCustomizableObject;

class FMinigameParameterOverrideCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	void ReadCurrentValues();
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	UCustomizableObject* CO{};
	TSharedPtr<IPropertyHandle> ParameterNameHandle;
	TSharedPtr<IPropertyHandle> ParameterValueHandle;

	// Dropdown data
	TArray<TSharedPtr<FString>> AvailableParameters;
	TSharedPtr<FString> SelectedParameter;

	TArray<TSharedPtr<FString>> AvailableValues;
	TSharedPtr<FString> SelectedValue;

	void RefreshParameterOptions();
	void RefreshValueOptions(const FString& ParamName);

	void OnParameterChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	void OnValueChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
};
