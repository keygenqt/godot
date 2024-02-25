// SPDX-FileCopyrightText: Copyright 2024 Vitaliy Zarubin <keygenqt@gmail.com>
// SPDX-License-Identifier: MIT
#include "export_plugin.h"

#include "logo_svg.gen.h"

#include "editor/editor_node.h"
#include "editor/editor_settings.h"
#include "editor/themes/editor_scale.h"

#include "modules/modules_enabled.gen.h"
#ifdef MODULE_SVG_ENABLED
#include "modules/svg/image_loader_svg.h"
#endif

namespace AuroraOptionsConfigration {
constexpr auto psdk_path = "aurora/platform_SDK/path";
constexpr auto architecture = "aurora/configure/architecture";
constexpr auto application_name = "aurora/configure/application_name";
constexpr auto package_organization = "aurora/configure/package_organization";
constexpr auto package_name = "aurora/configure/package_name";
constexpr auto icon = "aurora/configure/icon_512_x_512";
} //namespace AuroraOptionsConfigration

namespace AuroraPermission {
constexpr auto Bluetooth = "aurora/configure/permissions/Bluetooth";
constexpr auto Camera = "aurora/configure/permissions/Camera";
constexpr auto Compatibility = "aurora/configure/permissions/Compatibility";
constexpr auto DeviceInfo = "aurora/configure/permissions/DeviceInfo";
constexpr auto Internet = "aurora/configure/permissions/Internet";
constexpr auto Notifications = "aurora/configure/permissions/Notifications";
constexpr auto Sensors = "aurora/configure/permissions/Sensors";
constexpr auto UserDirs = "aurora/configure/permissions/UserDirs";

Vector<String> GetAuroraOSPermissions() {
	return Vector<String>{
		Bluetooth,
		Camera,
		Compatibility,
		DeviceInfo,
		Internet,
		Notifications,
		Sensors,
		UserDirs,
	};
}
} //namespace AuroraPermission

// @todo required
String EditorExportPlatformAuroraOS::get_template_file_name(const String &p_target, const String &p_arch) const {
	return "linux_" + p_target + "." + p_arch;
}

// @todo required
List<String> EditorExportPlatformAuroraOS::get_binary_extensions(const Ref<EditorExportPreset> &p_preset) const {
	List<String> list;
	list.push_back(p_preset->get("binary_format/architecture"));
	list.push_back("zip");
	return list;
}

// Icon menu generate
EditorExportPlatformAuroraOS::EditorExportPlatformAuroraOS() {
	if (EditorNode::get_singleton()) {
#ifdef MODULE_SVG_ENABLED
		Ref<Image> img = memnew(Image);
		const bool upsample = !Math::is_equal_approx(Math::round(EDSCALE), EDSCALE);
		ImageLoaderSVG::create_image_from_string(img, _auroraos_logo_svg, EDSCALE, upsample, false);
		set_logo(ImageTexture::create_from_image(img));
#endif
	}
}

// Configure menu export
void EditorExportPlatformAuroraOS::get_export_options(List<ExportOption> *r_options) const {
	// Path to Platform SDK
	auto option_psdk_path = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::psdk_path,
			PROPERTY_HINT_GLOBAL_DIR);
	r_options->push_back(ExportOption(option_psdk_path, OS::get_singleton()->get_environment("PSDK_DIR")));

	// Select architecture build
	auto option_architecture = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::architecture,
			PROPERTY_HINT_ENUM,
			"armv7hl,aarch64,x86_64");
	r_options->push_back(ExportOption(option_architecture, "armv7hl"));

	// Application public name
	auto option_application_name = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::application_name);
	r_options->push_back(ExportOption(option_application_name, ""));

	// Package organization name
	auto option_package_organization = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::package_organization);
	r_options->push_back(ExportOption(option_package_organization, ""));

	// Package application name
	auto option_package_name = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::package_name);
	r_options->push_back(ExportOption(option_package_name, ""));

	// Path icon 512x512 for auto crop sizes
	auto option_icon_path = PropertyInfo(
			Variant::STRING,
			AuroraOptionsConfigration::icon,
			PROPERTY_HINT_GLOBAL_DIR);
	r_options->push_back(ExportOption(option_icon_path, ""));

	// Permissions
	auto permissions = AuroraPermission::GetAuroraOSPermissions();
	for (int i = 0; i < permissions.size(); i++) {
		auto option_permission = PropertyInfo(
				Variant::BOOL,
				permissions[i]);
		r_options->push_back(ExportOption(option_permission, false));
	}

	EditorExportPlatformPC::get_export_options(r_options);
}