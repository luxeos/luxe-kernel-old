#
# LuxeOS (c) 2023 by Jozef Nagy
#
# LuxeOS is licensed under a
# Creative Commons Attribution-NoDerivatives 4.0 International License.
#
# You should have received a copy of the license along with this
# work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
#
#

include .config
include Makefile.in

.PHONY: all
all: full_release

.PHONY: full_release
full_release: release_iso release_hdd

.PHONY: release_iso
release_iso: $(KERNEL) $(SYMFILE)
	@printf " GEN  $(notdir $(RELEASE_ISO))\n"
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p iso_tmp/EFI/BOOT
	@cp $(KERNEL) aux/limine.cfg ex/limine/limine-uefi-cd.bin iso_tmp/
	@cp ex/limine/$(EFI_BOOTFILE) iso_tmp/EFI/BOOT/
	@xorriso -as mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_tmp -o $(RELEASE_ISO) &>/dev/null
	@rm -rf iso_tmp

.PHONY: release_hdd
release_hdd: $(KERNEL) $(SYMFILE)
	@printf " GEN  $(notdir $(RELEASE_HDD))\n"
	@mkdir -p $(RELEASE_DIR)
	@dd if=/dev/zero of=$(RELEASE_HDD) bs=1M count=32 &>/dev/null
	@mformat -i $(RELEASE_HDD) -L 32 ::
	@mmd -i $(RELEASE_HDD) ::/EFI
	@mmd -i $(RELEASE_HDD) ::/EFI/BOOT
	@mcopy -i $(RELEASE_HDD) ex/limine/$(EFI_BOOTFILE) ::/EFI/BOOT
	@mcopy -i $(RELEASE_HDD) aux/limine.cfg ::
	@mcopy -i $(RELEASE_HDD) $(KERNEL) ::

.PHONY: run
run: full_release
	@$(QEMU) $(QEMUFLAGS)

.config:
	@ex/kconfiglib/alldefconfig.py
	@$(MAKE) krnl/config.h

krnl/config.h: Kconfig .config
	@ex/kconfiglib/genconfig.py --header-path krnl/config.h

.PHONY: menuconfig
menuconfig:
	@ex/kconfiglib/menuconfig.py
	@$(MAKE) krnl/config.h

.PHONY: guiconfig
guiconfig:
	@ex/kconfiglib/guiconfig.py
	@$(MAKE) krnl/config.h

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf " CC   $^\n"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@printf " AS   $^\n"
	@$(AS) $(ASFLAGS) $< -o $@

$(SYMFILE): $(OBJ)
	@printf " GEN $(notdir $@)\n"
	@utils/gensym.sh $@
	@$(CC) $(CFLAGS) $(CPPFLAGS) -x c -c $(SYMFILE) -o $(SYMOBJ)
	@$(LD) $(LDFLAGS) $(OBJ) $(SYMOBJ) -o $(KERNEL)
	@utils/gensym.sh $(KERNEL)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -x c -c $(SYMFILE) -o $(SYMOBJ)
	@$(LD) $(LDFLAGS) $(OBJ) $(SYMOBJ) -o $(KERNEL)
	@$(OBJCOPY) --strip-debug $(KERNEL)

$(KERNEL): $(OBJ)
	@mkdir -p $(dir $@)
	@printf " LD   $@\n"
	@$(LD) $(OBJ) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	@printf " CLEAN\n"
	@rm -rf $(BUILD_DIR) $(RELEASE_DIR) .config.old
	@rm -rf $(SYMFILE)

.PHONY: distclean
distclean:
	@printf " DISTCLEAN\n"
	@rm -rf $(BUILD_DIR) $(RELEASE_DIR)
	@rm -rf $(SYMFILE)
	@rm -rf Makefile.in .config .config.old krnl/config.h
