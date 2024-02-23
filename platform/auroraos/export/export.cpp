// SPDX-FileCopyrightText: Copyright 2024 Vitaliy Zarubin <keygenqt@gmail.com>
// SPDX-License-Identifier: MIT
#include "export.h"

#include "export_plugin.h"

#include "editor/export/editor_export.h"

void register_auroraos_exporter_types() {
	GDREGISTER_VIRTUAL_CLASS(EditorExportPlatformAuroraOS);
}

void register_auroraos_exporter() {
	Ref<EditorExportPlatformAuroraOS> platform;
	platform.instantiate();
	platform->set_name("Aurora OS");
	platform->set_os_name("Aurora OS");
	platform->set_chmod_flags(0755);
	EditorExport::get_singleton()->add_export_platform(platform);
}
