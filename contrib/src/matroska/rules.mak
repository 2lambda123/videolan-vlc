# matroska

MATROSKA_VERSION := 1.6.0
MATROSKA_URL := http://dl.matroska.org/downloads/libmatroska/libmatroska-$(MATROSKA_VERSION).tar.xz

PKGS += matroska

ifeq ($(call need_pkg,"libmatroska"),)
PKGS_FOUND += matroska
endif

DEPS_matroska = ebml $(DEPS_ebml)

$(TARBALLS)/libmatroska-$(MATROSKA_VERSION).tar.xz:
	$(call download_pkg,$(MATROSKA_URL),matroska)

.sum-matroska: libmatroska-$(MATROSKA_VERSION).tar.xz

matroska: libmatroska-$(MATROSKA_VERSION).tar.xz .sum-matroska
	$(UNPACK)
	$(call pkg_static,"libmatroska.pc.in")
	$(MOVE)

# O2 optimization due to iOS issue https://code.videolan.org/videolan/vlc-ios/issues/248
ifdef HAVE_IOS
MATROSKA_CXXFLAGS +=  -O2
endif

.matroska: matroska toolchain.cmake
	cd $< && $(HOSTVARS_PIC) CXXFLAGS="$(MATROSKA_CXXFLAGS)" $(CMAKE)
	cd $< && $(MAKE) install
	touch $@
