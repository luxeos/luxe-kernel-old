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
all: release_iso

.PHONY: release
release: release_iso release_hdd

.PHONY: release_iso
release_iso: $(RELEASE_ISO)

.PHONY: release_hdd
release_hdd: $(RELEASE_HDD)

.PHONY: run
run: release_iso
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

$(RELEASE_ISO): $(KERNEL)
	@printf " GEN  $(notdir $(RELEASE_ISO))\n"
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p iso_tmp/EFI/BOOT
	@cp $(KERNEL) aux/limine.cfg ex/limine/limine-uefi-cd.bin iso_tmp/
	@cp ex/limine/$(EFI_BOOTFILE) iso_tmp/EFI/BOOT/
	@xorriso -as mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_tmp -o $(RELEASE_ISO) &>/dev/null
	@rm -rf iso_tmp

# This will probably move to a shell script to enable macOS users to
# generate .img files as well
# NOTE: This has not been tested, use at your own
$(RELEASE_HDD): $(KERNEL)
	@printf " GEN  $(notdir $(RELEASE_HDD))\n"
	@mkdir -p $(RELEASE_DIR)
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(RELEASE_HDD)
	@parted -s $(RELEASE_HDD) mklabel gpt
	@parted -s $(RELEASE_HDD) mkpart ESP fat32 2048s 100%
	@parted -s $(RELEASE_HDD) set 1 esp on
	@ex/limine/limine bios-install $(RELEASE_HDD) &>/dev/null
	LOOPBACK := $(shell sudo losetup -Pf --show $(RELEASE_HDD))
	@sudo mkfs.fat32 $(LOOPBACK)p1
	@mkdir -p hdd_tmp
	@sudo mount $(LOOPBACK)p1 hdd_tmp
	@sudo mkdir -p hdd_tmp/EFI/BOOT
	@sudo cp $(KERNEL) aux/limine.cfg ex/limine/limine-bios.sys hdd_tmp
	@sudo cp ex/limine/BOOTX64.EFI hdd_tmp/EFI/BOOT/
	@sync
	@sudo umount hdd_tmp
	@sudo losetup -d $(LOOPBACK)
	@sudo rm -rf hdd_tmp

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf " CC   $^\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@printf " AS   $^\n"
	@$(AS) $(ASFLAGS) $< -o $@

$(KERNEL): $(OBJ)
	@mkdir -p $(dir $@)
	@printf " LD   $@\n"
	$(LD) $(OBJ) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	@printf " CLEAN\n"
	@rm -rf $(BUILD_DIR) $(RELEASE_DIR) .config.old

.PHONY: distclean
distclean:
	@printf " DISTCLEAN\n"
	@rm -rf $(BUILD_DIR) $(RELEASE_DIR)
	@rm -rf Makefile.in .config krnl/config.h
