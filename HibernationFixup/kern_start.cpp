//
//  kern_start.cpp
//  HibernationFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#include "kern_config.hpp"
#include "kern_hbfx.hpp"

static HBFX hbfx;

const char *Configuration::bootargOff[] {
	"-hbfxoff"
};

const char *Configuration::bootargDebug[] {
	"-hbfxdbg"
};

const char *Configuration::bootargBeta[] {
	"-hbfxbeta"
};


Configuration config;


void Configuration::readArguments() {
    char tmp[20];
    if (PE_parse_boot_argn(bootargDumpNvram, tmp, sizeof(tmp)))
        dumpNvram = true;
    
    if (PE_parse_boot_argn(bootargPatchPCI, tmp, sizeof(tmp)))
    {
        patchPCIFamily = true;
        DBGLOG("HBFX @ boot-arg %s specified, turn on PCIFamily patching", bootargPatchPCI);
    }
    
    if (PE_parse_boot_argn(bootargPatchPCIWithList, ignored_device_list, sizeof(ignored_device_list)))
    {
        patchPCIFamily = true;
        DBGLOG("HBFX @ boot-arg %s specified, turn on PCIFamily patching", bootargPatchPCIWithList);
    }
    
    DBGLOG("HBFX @ ignored device list=%s", ignored_device_list);
}



PluginConfiguration ADDPR(config) {
	xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
	config.bootargOff,
	sizeof(config.bootargOff)/sizeof(config.bootargOff[0]),
	config.bootargDebug,
	sizeof(config.bootargDebug)/sizeof(config.bootargDebug[0]),
	config.bootargBeta,
	sizeof(config.bootargBeta)/sizeof(config.bootargBeta[0]),
	KernelVersion::MountainLion,
	KernelVersion::HighSierra,
	[]() {
        config.readArguments();
		hbfx.init();
	}
};





