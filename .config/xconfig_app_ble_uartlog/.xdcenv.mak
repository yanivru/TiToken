#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/tidrivers_cc13xx_cc26xx_2_16_01_13/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/bios_6_45_02_31/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/uia_2_00_05_50/packages;C:/programs/ti/ccsv6/ccs_base;C:/Users/Yaniv/workspace_v6_2/TiToken/.config
override XDCROOT = C:/programs/ti/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/tidrivers_cc13xx_cc26xx_2_16_01_13/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/bios_6_45_02_31/packages;C:/programs/ti/tirtos_cc13xx_cc26xx_2_18_00_03/products/uia_2_00_05_50/packages;C:/programs/ti/ccsv6/ccs_base;C:/Users/Yaniv/workspace_v6_2/TiToken/.config;C:/programs/ti/xdctools_3_32_00_06_core/packages;..
HOSTOS = Windows
endif
