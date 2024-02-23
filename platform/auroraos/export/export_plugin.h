// SPDX-FileCopyrightText: Copyright 2024 Vitaliy Zarubin <keygenqt@gmail.com>
// SPDX-License-Identifier: MIT
#ifndef AURORAOS_EXPORT_PLUGIN_H
#define AURORAOS_EXPORT_PLUGIN_H

#include "editor/export/editor_export_platform_pc.h"

class EditorExportPlatformAuroraOS : public EditorExportPlatformPC {
	GDCLASS(EditorExportPlatformAuroraOS, EditorExportPlatformPC);
public:
	virtual List<String> get_binary_extensions(const Ref<EditorExportPreset> &p_preset) const override;
	virtual String get_template_file_name(const String &p_target, const String &p_arch) const override;
	EditorExportPlatformAuroraOS();
};

#endif // AURORAOS_EXPORT_PLUGIN_H
