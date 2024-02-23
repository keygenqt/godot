// SPDX-FileCopyrightText: Copyright 2024 Vitaliy Zarubin <keygenqt@gmail.com>
// SPDX-License-Identifier: MIT
#include "export_plugin.h"

#include "logo_svg.gen.h"

#include "editor/editor_node.h"
#include "editor/themes/editor_scale.h"

#include "modules/modules_enabled.gen.h"
#ifdef MODULE_SVG_ENABLED
#include "modules/svg/image_loader_svg.h"
#endif

String EditorExportPlatformAuroraOS::get_template_file_name(const String &p_target, const String &p_arch) const {
	return "linux_" + p_target + "." + p_arch;
}

List<String> EditorExportPlatformAuroraOS::get_binary_extensions(const Ref<EditorExportPreset> &p_preset) const {
	List<String> list;
	list.push_back(p_preset->get("binary_format/architecture"));
	list.push_back("zip");
	return list;
}

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
